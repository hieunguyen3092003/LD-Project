/*
 * main.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "global.h"

#include "moistureSens.h"
#include "lightSens.h"
#include "rainSens.h"
#include "dht11Sens.h"
#include "pump.h"
#include "esp_nowClient.h"
#include "button.h"
#include "fsm.h"

#define READ_INTERVAL 3 * 60 * 60               // 3 hours
#define INACTIVE_READ_INTERVAL 3 * 24 * 60 * 60 // 3 days
#define PUMP_ON_INTERVAL 5                      // 5 seconds
#define ACTIVATE_LIMIT 40

void initSystem(void);

unsigned long current_time = 0;
unsigned long last_pump_on_time = 0;

void setup()
{
  Serial.begin(9600);
  initSystem();
  delay(1000);
}

void loop()
{
  current_time = millis();

  if (isButtonDown())
  {
    pumpTurnOn();
    last_pump_on_time = current_time;
  }
  if (isPumpOn())
  {
    if (current_time - last_pump_on_time >= PUMP_ON_INTERVAL * 1000 || current_time < last_pump_on_time)
    {
      pumpTurnOff();
    }
  }

  switch (current_mode)
  {
  case mode_init:
  {
    current_mode = mode_auto;
    break;
  }
  case mode_auto:
  {
    if (moisturePercent() == 0)
    {
      current_mode = mode_manual;
    }
    else
    {
      if (!isPumpOn())
      {
        if (moisturePercent() <= ACTIVATE_LIMIT)
        {
          pumpTurnOn();
          last_pump_on_time = current_time;
        }
      }
    }

    break;
  }
  case mode_timer:
  {
    if (current_time - last_pump_on_time >= READ_INTERVAL * 1000 || current_time < last_pump_on_time)
    {
      pumpTurnOn();
      last_pump_on_time = current_time;
    }
    break;
  }
  case mode_manual:
  {
    if (isButtonDown())
    {
      pumpTurnOn();
      last_pump_on_time = current_time;
    }
    break;
  }
  }

  if (isPacketReceived())
  {
    if (getRequestData())
    {
      esp_nowSendPacket(dhtTempValue(), dhtHumidValue(), moistureValue(), moisturePercent(), isPumpOn(), isDry(), isNight());
    }
    else if (getPumpOrder())
    {
      pumpTurnOn();
      last_pump_on_time = current_time;
    }
    else
    {
      switch (getPumpMode())
      {
      case 0:
      {
        current_mode = mode_auto;
        break;
      }
      case 1:
      {
        current_mode = mode_timer;
        break;
      }
      case 2:
      {
        current_mode = mode_manual;
        break;
      }
      }
    }
  }
}

void initSystem()
{
  initMoistureSens();
  initLightSens();
  initRainSens();
  initDHT11Sens();
  initPump();
  initEsp_now();
  initButton();
}
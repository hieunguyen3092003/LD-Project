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

void initSystem(void);

unsigned long last_read_time = 0;
unsigned long mode_timer_interval = 6 * 60 * 60;

void setup()
{
  Serial.begin(9600);
  initSystem();
  delay(1000);

  pumpAuto(moisturePercent(), activate_limit);
}

void loop()
{
  unsigned long current_time = millis();

  if (isPumpOn())
  {
    if (current_time - last_read_time >= pump_on_interval * 1000)
    {
      last_read_time = current_time;
      pumpTurnOff();
    }
    else if (current_time < last_read_time)
    {
      last_read_time = current_time;
    }
  }

  if (isButtonDown())
  {
    pumpTurnOn();
    last_read_time = current_time;
  }

  switch (current_mode)
  {
  case mode_auto:
  {
    pumpAuto(moisturePercent(), activate_limit);
    break;
  }
  case mode_timer:
  {
    if (current_time - last_read_time >= mode_timer_interval * 1000)
    {
      pumpTurnOn();
      last_read_time = current_time;
    }
    break;
  }
  default:
    break;
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
      last_read_time = current_time;
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
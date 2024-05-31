/*
                /\/\
               /'^.^)
        .-^^^-/  /
     _/         /7
    <__.|_|--|_|
*/

#include "global.h"

#include "button.h"
#include "dht11Sens.h"
#include "esp_nowClient.h"
#include "lightSens.h"
#include "moistureSens.h"
#include "pump.h"
#include "rainSens.h"

#define TIMER_PUMP_INTERVAL 6 * 60 * 60 // read data every 6 hours
#define SEND_INTERVAL 3 * 60 * 60       // send data every 3 hours

void initSystem(void);

// global variables
unsigned long current_time = 0;
unsigned long last_send_time = 0;

Message_Send packet_send = {moisturePercent(), dhtTempValue(), dhtHumidValue(), isNight(), isPumpOn(), false};
Message_Receive packet_receive{false, 1, 50, 5};

Mode current_mode = mode_init;

void setup()
{
  Serial.begin(9600);
  initSystem();

  delay(1000);
}

void loop()
{
  current_time = millis();
  is_button_down = isButtonDown() || packet_receive.is_button_down;

  if (packet_receive.is_button_down) // reset button variable send through esp_now
  {
    packet_receive.is_button_down = false;
  }

  if (isPacketReceived())
  {
    current_mode = static_cast<Mode>(packet_receive.pump_mode);
    pump_on_interval = packet_receive.pump_interval;
    pump_on_limit = packet_receive.pump_limit;

    esp_nowSync();
  }

  if (current_time - last_send_time >= SEND_INTERVAL * 1000)
  {
    esp_nowSync();
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
    if (moisturePercent() <= pump_on_limit)
    {
      pumpTurnOn();
    }
    else
    {
      pumpTurnOff();
    }

    break;
  }
  case mode_timer:
  {
    if (is_button_down)
    {
      pumpTurnOn();
    }

    if (!packet_send.warning)
    {
      if (isDry() && !isNight() && (moisturePercent() < pump_on_limit))
      {
        if (current_time - last_pump_on_time >= TIMER_PUMP_INTERVAL * 1000 || current_time < last_pump_on_time)
        {
          pumpTurnOn();
        }
      }
    }
    else
    {
      if (current_time - last_pump_on_time >= TIMER_PUMP_INTERVAL * 1000 || current_time < last_pump_on_time)
      {
        pumpTurnOn();
      }
    }

    pumpTimerOff(pump_on_interval);

    break;
  }
  case mode_manual:
  {
    if (is_button_down)
    {
      if (isPumpOn())
      {
        pumpTurnOff();
      }
      else
      {
        pumpTurnOn();
      }
    }

    pumpTimerOff(pump_on_interval * 10);
    break;
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
  return;
}
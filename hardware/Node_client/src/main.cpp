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

void initSystem(void);

void setup()
{
  delay(1000);

  initSystem();
}

void loop()
{
  if (isPacketReceived())
  {
    if (getRequestData())
    {
      esp_nowSendPacket(dhtTempValue(), dhtHumidValue(), moistureValue(), moisturePercent(), isPumpOn(), isDry(), isNight());
    }
    else if (getPumpOrder())
    {
      pumpTurnOn();
    }
    else
    {
      pumpTurnOff();
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

  Serial.begin(9600);
}
/*
 * main.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "global.h"

#include "lcd.h"
#include "esp_nowServer.h"
#include "button.h"
#include "numpad.h"
#include "mqtt.h"
#include "fsm.h"

void initSystem(void);

unsigned long read_interval = 6 * 60 * 60; // 6 hours
unsigned long last_read_time = 0;
unsigned long current_time = 0;

void setup()
{
  Serial.begin(9600);
  initSystem();
  delay(1000);
  esp_nowRequestData();
}

void loop()
{
  key = numpadGetKey();
  fsmManager();

  if (key)
  {
    Serial.println(key);
  }

  switch (current_mode)
  {
  case mode_init:
  {
    break;
  }
  case mode_security:
  {
    if (key)
    {
      lcdTurnOnBacklight();
      lcdDisplay(0, 0, "Enter Password: ", 0, "");
    }
    break;
  }
  case mode_running:
  {
    current_time = millis();

    // request data
    if (current_time - last_read_time >= read_interval * 1000)
    {
      esp_nowRequestData();
    }
    else if (current_time < last_read_time) // tràn bit current_time
    {
      esp_nowRequestData();
    }

    if (isButtonDown())
    {
      esp_nowTurnOnPump();
      esp_nowRequestData();
    }

    if (isPacketReceived())
    {
      lcdClear();
      lcdDisplay(0, 0, "Moisture:", getMoisturePercentage(), "%");
      lcdDisplay(0, 1, "Temp:", getTemperature(), "C");
      lcdDisplay(8, 1, "Humid:", getHumidity(), "%");
      last_read_time = current_time; // nếu đặt ở đây mà packet không received được thì nó sẽ call hoài...
    }
    if (!isPacketSent())
    {
      lcdClear();
      lcdDisplay(1, 0, "Not Connected   ", 0, "");
      lcdDisplay(0, 1, "Press Any Key...", 0, "");
      if (key) // pressed any key to reconnect
      {
        Serial.println(key);
        esp_nowRequestData();
      }
    }
    break;
  }
  default:
  {
    break;
  }
  }
}

void initSystem()
{
  initLCD();
  initEsp_now();
  initButton();
  initNumpad();
}
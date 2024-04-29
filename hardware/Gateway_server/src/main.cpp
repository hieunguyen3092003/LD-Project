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

void initSystem(void);

enum mode
{
  mode_running,
  mode_modify_pump
};
mode current_mode = mode_running;

unsigned long read_interval = 6 * 60 * 60;
unsigned long last_read_time = 0;

char key = 0;

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

  switch (current_mode)
  {
  case mode_running:
  {
    unsigned long current_time = millis();

    // request data
    if (current_time - last_read_time >= read_interval * 1000)
    {
      last_read_time = current_time;
      esp_nowRequestData();
    }
    else if (current_time < last_read_time)
    {
      last_read_time = current_time;
      esp_nowRequestData();
    }

    if (isButtonDown())
    {
      esp_nowTurnOnPump();
      esp_nowRequestData();
    }

    if (isPacketReceived())
    {
      clearLCD();
      lcdDisplay(0, 0, "Moisture:", getMoisturePercentage(), "%");
      lcdDisplay(0, 1, "Temp:", getTemperature(), "C");
      lcdDisplay(8, 1, "Humid:", getHumidity(), "%");
    }
    if (!isPacketSent())
    {
      clearLCD();
      lcdDisplay(1, 0, "Not Connected   ", 0, "%");
    }
    break;
  }

  default:
    break;
  }
}

void initSystem()
{
  initLCD();
  clearLCD();
  initEsp_now();
  initButton();
  initNumpad();
}
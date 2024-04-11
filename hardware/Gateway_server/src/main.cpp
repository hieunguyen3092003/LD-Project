/*
 * main.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "global.h"

#include "lcd.h"
#include "esp_nowServer.h"
#include "rtc.h"
#include "button.h"

void initSystem(void);
void debug(void);

unsigned long read_interval = 6 * 60 * 60 * 1000;
unsigned long last_read_time = 0;
unsigned int pump_interval = 3 * 1000;
unsigned long last_pump_on_time = 0;
bool is_pump_on = false;

void setup()
{
  delay(1000);

  initSystem();

  esp_nowRequestData();
}

void loop()
{
  unsigned long current_time = millis();

  if (current_time - last_read_time >= read_interval)
  {
    last_read_time = current_time;
    esp_nowRequestData();
  }
  else if (current_time < last_read_time)
  {
    last_read_time = current_time;
    esp_nowRequestData();
  }

  if (is_pump_on == true)
  {
    if (current_time - last_pump_on_time >= pump_interval)
    {
      last_pump_on_time = current_time;
      esp_nowTurnOffPump();
      is_pump_on = false;
    }
    else if (current_time < last_pump_on_time)
    {
      last_pump_on_time = current_time;
    }
  }

  if (current_time % 500 == 0)
  {
    if (isButtonDown())
    {
      esp_nowRequestData();
    }
  }

  if (isPacketReceived())
  {
    debug();

    clearLCD();
    lcdDisplay(0, 0, "Moisture:", getMoisturePercentage(), "%");
    lcdDisplay(0, 1, "Temp:", getTemperature(), "C");
    lcdDisplay(8, 1, "Humid:", getHumidity(), "%");

    if (getMoisturePercentage() < 30)
    {
      esp_nowTurnOnPump();
      is_pump_on = true;
      last_pump_on_time = current_time;
    }
  }
}

void initSystem()
{
  initLCD();
  clearLCD();
  initEsp_now();
  initButton();

  Serial.begin(9600);
}

void debug()
{
  Serial.print("moisture percent: ");
  Serial.print(getMoisturePercentage());
  Serial.print(" night: ");
  Serial.print(getNightStatus());
  Serial.print(" temp: ");
  Serial.print(getTemperature());
  Serial.print(" humidity: ");
  Serial.print(getHumidity());
  Serial.print(" dry: ");
  Serial.println(getDryStatus());
}
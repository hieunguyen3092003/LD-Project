/*
 * main.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "global.h"

#include "fsm.h"
#include "lcd.h"
#include "esp_nowServer.h"
#include "button.h"
#include "numpad.h"
#include "mqtt.h"

#define ACTIVE_READ_INTERVAL 10            // 10 secconds
#define INACTIVE_READ_INTERVAL 3 * 60 * 60 // 3 hours

void initSystem(void);
void debugSystem(void);

unsigned long current_time = 0;
unsigned long last_read_time = 0;

void setup()
{
  Serial.begin(9600);
  initSystem();
  delay(1000);
}
void loop()
{
  current_time = millis();
  key = numpadGetKey();

  switch (current_mode)
  {
  case mode_init:
  {
    esp_nowRequestData();
    break;
  }
  case mode_modify_password:
  {
    if (key)
    {
      if (key == 'A')
      {
        if (!Password.isEmpty())
        {
          Password.remove(Password.length() - 1);
        }
        lcdClear();
        lcdDisplay(0, 0, "Set New Password", 0, "");
      }
      else if (key == 'D')
      {
        Password = "";
        lcdClear();
        lcdDisplay(0, 0, "Set New Password", 0, "");
      }
      else if (key >= '0' && key <= '9')
      {
        if (Password.length() < 4)
        {
          Password += key;
        }
      }
      lcdDisplay(16 - Password.length(), 1, Password, 0, "");
    }
    break;
  }
  case mode_modify_pump:
  {
    switch (key)
    {
    case '0':
    {
      current_pump_mode = mode_auto;
      lcdDisplay(0, 0, "Mode: ", current_pump_mode, "");
      break;
    }
    case '1':
    {
      current_pump_mode = mode_timer;
      lcdDisplay(0, 0, "Mode: ", current_pump_mode, "");
      break;
    }
    case '2':
    {
      current_pump_mode = mode_manual;
      lcdDisplay(0, 0, "Mode: ", current_pump_mode, "");
      break;
    }
    }
    break;
  }
  case mode_security:
  {
    if (current_time - last_read_time >= INACTIVE_READ_INTERVAL * 1000 || current_time < last_read_time) // after INACTIVE_READ_INTERVAL request to read 1 time and handle bit overflow
    {
      esp_nowRequestData();
      last_read_time = current_time;
    }

    if (isPacketReceived())
    {
      // last_read_time = current_time;
    }

    if (key)
    {
      if (key == 'A')
      {
        if (!passwordInput.isEmpty())
        {
          passwordInput.remove(passwordInput.length() - 1);
        }
        lcdClear();
        lcdDisplay(0, 0, "Enter Password: ", 0, "");
      }
      else if (key == 'D')
      {
        passwordInput = "";
        lcdClear();
        lcdDisplay(0, 0, "Enter Password: ", 0, "");
      }
      else if (key >= '0' && key <= '9')
      {
        if (passwordInput.length() < 4)
        {
          passwordInput += key;
        }
      }
      lcdDisplay(16 - passwordInput.length(), 1, passwordInput, 0, "");
    }
    break;
  }
  case mode_running:
  {
    if (isButtonDown())
    {
      esp_nowTurnOnPump();
    }

    if (current_time - last_read_time >= ACTIVE_READ_INTERVAL * 1000 || current_time < last_read_time) // after ACTIVE_READ_INTERVAL request to read 1 time and handle bit overflow
    {
      esp_nowRequestData();
      last_read_time = current_time;
    }

    if (isPacketReceived())
    {
      lcdClear();
      lcdDisplay(0, 0, "Moisture:", getMoisturePercentage(), "%");
      lcdDisplay(0, 1, "Temp:", getTemperature(), "C");
      lcdDisplay(8, 1, "Humid:", getHumidity(), "%");
    }
    if (!isPacketSent())
    {
      lcdClear();
      lcdDisplay(1, 0, "Not Connected   ", 0, "");
      lcdDisplay(0, 1, "Press Any Key...", 0, "");
      if (key) // pressed any key to reconnect
      {
        esp_nowRequestData();
      }
    }
    break;
  }
  }
  fsmManager();

  debugSystem();
}

void initSystem()
{
  initLCD();
  initEsp_now();
  initButton();
  initNumpad();
}
void debugSystem()
{
  if (key)
  {
    Serial.println(key);
  }
}
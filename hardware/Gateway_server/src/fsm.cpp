/*
 * fsm.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "global.h"
#include "fsm.h"
#include "numpad.h"
#include "lcd.h"
#include "button.h"
#include "esp_nowServer.h"

#define ACTIVE_TIME 15

void fsmManager(void);

Mode current_mode = mode_init;
Pump_Mode current_pump_mode = mode_auto;

String Password = "";
String passwordInput = "";

unsigned long last_action_time = 0; // used to switch to mode security

/**
 * @brief: this function manage turn on and off back light and switch mode
 */
void fsmManager()
{
    if (key || isButtonDown() || current_time < last_action_time)
    {
        last_action_time = current_time;
        lcdTurnOnBacklight();
    }

    switch (current_mode)
    {
    case mode_init:
    {
        current_mode = mode_modify_password;
        lcdClear();
        lcdDisplay(0, 0, "Set New Password", 0, "");
        break;
    }
    case mode_modify_password:
    {
        if (Password.length() == 4)
        {
            if (key == '#')
            {
                current_mode = mode_running;
                lcdClear();
                esp_nowRequestData();
            }
            else if (key == '*')
            {
                current_mode = mode_modify_pump;
                lcdClear();
                lcdDisplay(0, 0, "Mode: ", current_pump_mode, "");
                lcdDisplay(8, 0, "Auto:", 0, "");
                lcdDisplay(0, 1, "Timer:", 1, "");
                lcdDisplay(8, 1, "Manual:", 2, "");
            }
        }
        break;
    }
    case mode_modify_pump:
    {
        if (key == '#')
        {
            esp_nowSendPumpMode();

            current_mode = mode_running;
            lcdClear();
            esp_nowRequestData();
        }
        else if (key == '*')
        {
            current_mode = mode_modify_password;
            lcdClear();
            lcdDisplay(0, 0, "Set New Password", 0, "");
            lcdDisplay(16 - Password.length(), 1, Password, 0, "");
        }
        break;
    }
    case mode_security:
    {
        if (key == '#')
        {
            if (passwordInput == Password)
            {
                current_mode = mode_running;
                lcdClear();
                esp_nowRequestData();
            }
        }
        if (current_time - last_action_time >= ACTIVE_TIME * 1000)
        {
            lcdTurnOffBacklight();
            passwordInput = "";
            lcdClear();
            lcdDisplay(0, 0, "Enter Password: ", 0, "");
        }
        break;
    }
    case mode_running:
    {
        if (key == '*')
        {
            current_mode = mode_modify_password;
            lcdClear();
            lcdDisplay(0, 0, "Set New Password", 0, "");
            lcdDisplay(16 - Password.length(), 1, Password, 0, "");
        }
        if (current_time - last_action_time >= ACTIVE_TIME * 1000) // turn off after ACTIVE_TIME second
        {
            lcdTurnOffBacklight();
            current_mode = mode_security;

            lcdClear();
            lcdDisplay(0, 0, "Enter Password: ", 0, "");
        }
        break;
    }
    }
}
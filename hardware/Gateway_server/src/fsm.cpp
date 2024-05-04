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

void fsmManager(void);

mode current_mode = mode_init;

unsigned long last_action_time = 0; // used to switch to mode security

void fsmManager()
{
    if (key || isButtonDown())
    {
        last_action_time = current_time;
    }

    switch (current_mode)
    {
    case mode_init:
    {
        current_mode = mode_running;
        break;
    }
    case mode_security:
    {
        if (key == '*')
        {
            lcdTurnOnBacklight();
            current_mode = mode_running;
            last_action_time = current_time;
        }
        break;
    }
    case mode_running:
    {
        // if (current_time - last_action_time >= 30 * 1000) // turn off after 15 second
        // {
        //     lcdTurnOffBacklight();
        //     current_mode = mode_security;
        // }
        break;
    }
    }
}
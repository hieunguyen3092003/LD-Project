/*
 * pump.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "global.h"
#include "pump.h"

#ifdef PUMP

#include "moistureSens.h"
#include "lightSens.h"
#include "rainSens.h"
#include "dht11Sens.h"
#include "esp_nowClient.h"

void initPump(void);
void pumpTurnOn(void);
void pumpTurnOff(void);
bool isPumpOn(void);
void pumpTimerOff(const int pump_on_interval);

unsigned long last_pump_on_time = 0;
int pump_on_limit = 50;
int pump_on_interval = 5;

void initPump()
{
    pinMode(PUMP_PIN, OUTPUT);
    digitalWrite(PUMP_PIN, HIGH);
}

void pumpTurnOn()
{
    if (!isPumpOn())
    {
        digitalWrite(PUMP_PIN, LOW);
        
        last_pump_on_time = current_time;

        esp_nowSync();
    }
}

void pumpTurnOff()
{
    if (isPumpOn())
    {
        digitalWrite(PUMP_PIN, HIGH);

        esp_nowSync();
    }
}

bool isPumpOn()
{
    return (digitalRead(PUMP_PIN) == LOW);
}

void pumpTimerOff(const int pump_on_interval)
{
    if (isPumpOn())
    {
        if (current_time - last_pump_on_time >= pump_on_interval * 1000 || current_time < last_pump_on_time)
        {
            pumpTurnOff();
        }
    }
    return;
}

#endif /* PUMP */
/*
 * pump.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "global.h"
#include "pump.h"

void initPump(void);
void pumpAuto(const int &moisture_percent, const int &activate_limit);
void pumpTurnOn(void);
void pumpTurnOff(void);
int isPumpOn(void);

unsigned long pump_on_interval = 3;
bool activate_limit = 30;

void initPump()
{
    pinMode(Pump_Pin, OUTPUT);
    digitalWrite(Pump_Pin, LOW);
}

void pumpAuto(const int &moisture_percent, const int &activate_limit)
{
    if (moisture_percent <= activate_limit)
    {
        digitalWrite(Pump_Pin, HIGH);
    }
    else
    {
        digitalWrite(Pump_Pin, LOW);
    }
}

void pumpTurnOn()
{
    digitalWrite(Pump_Pin, HIGH);
}

void pumpTurnOff()
{
    digitalWrite(Pump_Pin, LOW);
}

int isPumpOn()
{
    return digitalRead(Pump_Pin);
}

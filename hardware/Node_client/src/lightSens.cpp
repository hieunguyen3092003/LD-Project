/*
 * lightSens.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "global.h"
#include "lightSens.h"

void initLightSens(void);
int isNight(void);

void initLightSens()
{
    pinMode(Light_Sensor_Pin, INPUT_PULLDOWN);
}

int isNight()
{
    return digitalRead(Light_Sensor_Pin);
}
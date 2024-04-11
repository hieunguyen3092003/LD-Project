/*
 * rainSens.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "global.h"
#include "rainSens.h"

void initRainSens(void);
int isDry(void);

void initRainSens()
{
    pinMode(Rain_Sensor_Pin, INPUT_PULLDOWN);
}

int isDry()
{
    return digitalRead(Rain_Sensor_Pin);
}
/*
 * lightSensor.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "lightSensor.h"

int isNight()
{
    return digitalRead(Light_Sensor_Pin);
}
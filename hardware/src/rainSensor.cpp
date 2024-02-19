/*
 * rainSensor.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "rainSensor.h"

int isDry()
{
    return digitalRead(Rain_Sensor_Pin);
}
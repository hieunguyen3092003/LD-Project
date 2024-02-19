/*
 * lightSensor.h
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#ifndef src_lightSensor_h
#define src_lightSensor_h

#include "global.h"

#define Light_Sensor_Pin GPIO_NUM_16

int isNight(void);

#endif /* src_lightSensor_h */
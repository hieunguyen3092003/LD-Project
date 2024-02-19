/*
 * moistureSensor.h
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#ifndef src_moistureSensor_h
#define src_moistureSensor_h

#include "global.h"

#define Moisture_Sensor_Pin GPIO_NUM_0
#define Moisture_Sensor_Pin_2 GPIO_NUM_4

void initializeBaudrate(void);

int soilMoistureValue1(void);
int soilMoisturePercent1(void);

int soilMoistureValue2(void);
int soilMoisturePercent2(void);

int mediumValue(int data_1, int data_2);

#endif /* src_moistureSensor_h */
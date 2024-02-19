/*
 * DHT11.h
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#ifndef src_DHT11_h
#define src_DHT11_h

#include <DHT_U.h>
#include <SPI.h>
#include <Wire.h>
#include "global.h"

#define DHT11_Sensor_Pin GPIO_NUM_32

void initializeDHT(void);

float temperatureValue(void);
float humidityValue(void);

#endif /* src_DHT11_h */
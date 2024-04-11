/*
 * dht11Sens.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "global.h"
#include "dht11Sens.h"

#include <DHT_U.h>
#include <SPI.h>
#include <Wire.h>

void initDHT11Sens(void);
float dhtTempValue(void);
float dhtHumidValue(void);

DHT dht(DHT11_Sensor_Pin, DHT11);

float temperature = 0;
float humidity = 0;

void initDHT11Sens()
{
    pinMode(DHT11_Sensor_Pin, INPUT_PULLDOWN);
    dht.begin();
}

float dhtTempValue()
{
    temperature = dht.readTemperature();
    return temperature;
}

float dhtHumidValue()
{
    humidity = dht.readHumidity();
    return humidity;
}

/*
 * DHT11.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "DHT11.h"

DHT dht(DHT11_Sensor_Pin, DHT11);

void initializeDHT()
{
    dht.begin();
}

float temperature = 0;
float humidity = 0;

float temperatureValue()
{
    temperature = dht.readTemperature();
    return temperature;
}

float humidityValue()
{
    humidity = dht.readHumidity();
    return humidity;
}

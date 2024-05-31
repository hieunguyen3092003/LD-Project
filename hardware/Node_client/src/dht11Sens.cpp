#include "global.h"
#include "dht11Sens.h"

#ifdef DHT11SENS

#include <DHT_U.h>
#include <SPI.h>
#include <Wire.h>

void initDHT11Sens(void);
float dhtTempValue(void);
float dhtHumidValue(void);

DHT dht(DHT11_SENSOR_PIN, DHT11);

float temperature = 0;
float humidity = 0;

void initDHT11Sens()
{
    pinMode(DHT11_SENSOR_PIN, INPUT_PULLDOWN);
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

#endif /* DHT11SENS */
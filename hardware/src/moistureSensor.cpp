/*
 * moistureSensor.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "moistureSensor.h"

void initializeBaudrate()
{
    Serial.begin(9600);
}

const int Air_Value_1 = 4095;
const int Water_Value_1 = 2500;
int moisture_value_1 = 0;
int moisture_percent_1 = 0;

int soilMoistureValue1()
{
    moisture_value_1 = analogRead(Moisture_Sensor_Pin);
    return moisture_value_1;
}
int soilMoisturePercent1()
{
    moisture_percent_1 = map(soilMoistureValue1(), Air_Value_1, Water_Value_1, 0, 100);
    if (moisture_percent_1 >= 100)
    {
        return 100;
    }
    else if (moisture_percent_1 <= 0)
    {
        return 0;
    }
    return moisture_percent_1;
}

const int Air_Value_2 = 2700;
const int Water_Value_2 = 2300;
int moisture_value_2 = 0;
int moisture_percent_2 = 0;

int soilMoistureValue2()
{
    moisture_value_2 = analogRead(Moisture_Sensor_Pin_2);
    return moisture_value_2;
}
int soilMoisturePercent2()
{
    moisture_percent_2 = map(soilMoistureValue2(), Air_Value_2, Water_Value_2, 0, 100);
    if (moisture_percent_2 >= 100)
    {
        return 100;
    }
    else if (moisture_percent_2 <= 0)
    {
        return 0;
    }
    return moisture_percent_2;
}

int mediumValue(int data_1, int data_2)
{

    return ((data_1 + data_2) / 2);
}
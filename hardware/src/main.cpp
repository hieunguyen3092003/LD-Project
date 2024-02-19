/*
 * main.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "global.h"
#include "moistureSensor.h"
#include "LCD.h"
#include "DHT11.h"
#include "rainSensor.h"
#include "lightSensor.h"

void setup()
{
  initializeBaudrate();
  initializeLCD();
  initializeDHT();
}

void loop()
{
  clearLCD();
  displayPercentData("Moisture:", mediumValue(soilMoisturePercent1(), soilMoisturePercent2()), 0, 0);
  displayTemperature(temperatureValue(), 0, 1);
  displayPercentData("-HUMI:", humidityValue(), 7, 1);

  Serial.print("light sensor:");
  Serial.println(isNight());

  Serial.print("rain sensor: ");
  Serial.println(isDry());

  delay(1000);
}
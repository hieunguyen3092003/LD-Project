/*
 * LCD.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "LCD.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

void initializeLCD()
{
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

void clearLCD()
{
    lcd.clear();
}

void displayPercentData(const String &msg, const int &moisture_percent, const int &x_coor, const int &y_coor)
{
    lcd.setCursor(x_coor, y_coor);
    lcd.print(msg);
    lcd.print(moisture_percent);
    lcd.print("%");
}

void displayTemperature(const int &temperature, const int &x_coor, const int &y_coor)
{
    lcd.setCursor(x_coor, y_coor);
    lcd.print("TMP:");
    lcd.print(temperature);
    lcd.print("C");
}

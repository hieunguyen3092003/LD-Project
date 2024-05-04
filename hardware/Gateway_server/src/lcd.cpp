// /*
//  * lcd.cpp
//  *
//  *  Created on: feb 5, 2023
//  *      Author: hieun
//  */

#include "lcd.h"

#include <LiquidCrystal_I2C.h>

void initLCD(void);
void lcdTurnOnBacklight(void);
void lcdTurnOffBacklight(void);
void lcdClear(void);
void lcdDisplay(const int &x_coor, const int &y_coor, const String &msg, const int &number, const String &units);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void initLCD()
{
    lcd.init();
    lcdTurnOnBacklight();
    lcd.clear();
}

void lcdTurnOnBacklight()
{
    lcd.backlight();
}

void lcdTurnOffBacklight()
{
    lcd.noBacklight();
}

void lcdClear()
{
    lcd.clear();
}

void lcdDisplay(const int &x_coor, const int &y_coor, const String &msg, const int &number, const String &units)
{
    lcd.setCursor(x_coor, y_coor);
    lcd.print(msg);
    lcd.print(number);
    lcd.print(units);
}

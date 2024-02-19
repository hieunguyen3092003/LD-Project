/*
 * LCD.h
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#ifndef src_LCD_h
#define src_LCD_h

#include <LiquidCrystal_I2C.h>
#include "global.h"

void initializeLCD(void);

void clearLCD(void);

void displayPercentData(const String &msg, const int &moisture_percent, const int &x_coor, const int &y_coor);

void displayTemperature(const int &temperature, const int &x_coor, const int &y_coor);

#endif /* src_LCD_h */
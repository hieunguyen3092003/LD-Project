/*
 * lcd.h
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#ifndef SRC_LCD_H
#define SRC_LCD_H

#include "global.h"

void initLCD(void);
void clearLCD(void);
void lcdDisplay(const int &x_coor, const int &y_coor, const String &msg, const int &number, const String &units);

#endif /* SRC_LCD_H */
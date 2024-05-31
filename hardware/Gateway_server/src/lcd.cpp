#include "global.h"
#include "lcd.h"

#ifdef LCD

#include <LiquidCrystal_I2C.h>

void initLCD(void);
void lcdTurnOnBacklight(void);
void lcdTurnOffBacklight(void);
void lcdClear(void);
void lcdDisplay(const int &x_coor, const int &y_coor, const String &msg, const int &number, const String &units, bool fill_num);

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

void lcdDisplay(const int &x_coor, const int &y_coor, const String &msg, const int &number, const String &units, bool fill_num)
{
    lcd.setCursor(x_coor, y_coor);
    lcd.print(msg);
    if (fill_num)
    {
        lcd.print(number);
    }
    lcd.print(units);
}

#endif /* LCD */
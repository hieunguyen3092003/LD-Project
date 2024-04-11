/*
 * button.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "global.h"
#include "button.h"

void initButton(void);
bool isButtonDown(void);

void initButton()
{
    pinMode(Button_Pin, INPUT_PULLUP);
}

bool isButtonDown()
{
    if (digitalRead(Button_Pin) == LOW)
    {
        return 1;
    }
    return 0;
}
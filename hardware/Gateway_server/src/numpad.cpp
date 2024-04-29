/*
 * numpad.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "global.h"
#include "numpad.h"

#include <keypad.h>

void initNumpad(void);
char numpadGetKey(void);

const uint8_t ROWS = 4;
const uint8_t COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
uint8_t colPins[COLS] = {Col_0_Pin, Col_1_Pin, Col_2_Pin, Col_3_Pin};
uint8_t rowPins[ROWS] = {Row_0_Pin, Row_1_Pin, Row_2_Pin, Row_3_Pin};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void initNumpad()
{
    keypad.setDebounceTime(50); // setDebounceTime(mS)
}

char numpadGetKey()
{
    return keypad.getKey();
}
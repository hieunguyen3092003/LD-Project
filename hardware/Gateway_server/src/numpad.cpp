#include "global.h"
#include "numpad.h"

#ifdef NUMPAD

#include <keypad.h>

void initNumpad(void);
char numpadGetKey(void);

char key = 0;

const uint8_t ROWS = 4;
const uint8_t COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
uint8_t colPins[COLS] = {COL_0_PIN, COL_1_PIN, COL_2_PIN, COL_3_PIN};
uint8_t rowPins[ROWS] = {ROW_0_PIN, ROW_1_PIN, ROW_2_PIN, ROW_3_PIN};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void initNumpad()
{
    keypad.setDebounceTime(50); // setDebounceTime(mS)
}

char numpadGetKey()
{
    return keypad.getKey();
}

#endif /* NUMPAD */
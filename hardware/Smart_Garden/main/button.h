#ifndef main_button_h
#define main_button_h

#include "./driver/gpio.h"

#define NORMAL_STATE 1
#define PRESSED_STATE 0

int isButton1Pressed();

void getKeyInput();

#endif /* main_button_h */
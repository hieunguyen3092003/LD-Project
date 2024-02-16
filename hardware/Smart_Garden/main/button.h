#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "./driver/gpio.h"

#define NORMAL_STATE 1  // macro nay thay the normal state thanh tin hieu muc 1
#define PRESSED_STATE 0 // macro thay tin hieu muc 0 luc nhan

int isButton1Pressed();

void getKeyInput();

#endif /* INC_BUTTON_H_ */
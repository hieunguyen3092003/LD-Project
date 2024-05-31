#include "cfg.h"

#ifdef BUTTON

#define BUTTON_PIN GPIO_NUM_23
void initButton(void);
bool isButtonDown(void);

#endif /* BUTTON */
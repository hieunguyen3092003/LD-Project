#include "cfg.h"

#ifdef BUTTON

#define BUTTON_PIN GPIO_NUM_23
extern bool is_button_down;
void initButton(void);
bool isButtonDown(void);

#endif /* BUTTON */

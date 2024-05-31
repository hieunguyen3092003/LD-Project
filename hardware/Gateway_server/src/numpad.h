#include "cfg.h"

#ifdef NUMPAD

#define ROW_0_PIN GPIO_NUM_12
#define ROW_1_PIN GPIO_NUM_14
#define ROW_2_PIN GPIO_NUM_27
#define ROW_3_PIN GPIO_NUM_26

#define COL_0_PIN GPIO_NUM_25
#define COL_1_PIN GPIO_NUM_33
#define COL_2_PIN GPIO_NUM_32
#define COL_3_PIN GPIO_NUM_13

extern char key;

void initNumpad(void);
char numpadGetKey(void);

#endif /* NUMPAD */
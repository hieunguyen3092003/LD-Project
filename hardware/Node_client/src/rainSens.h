#include "cfg.h"

#ifdef RAINSENS

#define RAIN_SENSOR_PIN GPIO_NUM_32
void initRainSens(void);
bool isDry(void);

#endif /* RAINSENS */
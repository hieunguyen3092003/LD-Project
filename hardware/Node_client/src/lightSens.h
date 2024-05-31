#include "cfg.h"

#ifdef LIGHTSENS

#define LIGHT_SENSOR_PIN GPIO_NUM_34
void initLightSens(void);
bool isNight(void);

#endif /* LIGHTSENS */
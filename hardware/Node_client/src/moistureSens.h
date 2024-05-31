#include "cfg.h"

#ifdef MOISTURESENS

#define MOISTURE_SENSOR_PIN GPIO_NUM_35
void initMoistureSens(void);
int moistureValue(void);
int moisturePercent(void);

#endif /* MOISTURESENS */
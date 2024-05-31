#include "global.h"
#include "rainSens.h"

#ifdef RAINSENS

void initRainSens(void);
bool isDry(void);

void initRainSens()
{
    pinMode(RAIN_SENSOR_PIN, INPUT_PULLDOWN);
}

bool isDry()
{
    return (digitalRead(RAIN_SENSOR_PIN) == HIGH);
}

#endif /* RAINSENS */
#include "global.h"
#include "lightSens.h"

#ifdef LIGHTSENS

void initLightSens(void);
bool isNight(void);

void initLightSens()
{
    pinMode(LIGHT_SENSOR_PIN, INPUT_PULLDOWN);
}

bool isNight()
{
    return (digitalRead(LIGHT_SENSOR_PIN) == HIGH);
}

#endif /* LIGHTSENS */
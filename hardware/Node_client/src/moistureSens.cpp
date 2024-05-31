#include "global.h"
#include "moistureSens.h"

#ifdef MOISTURESENS

void initMoistureSens(void);
int moistureValue(void);
int moisturePercent(void);

const int AIR_VALUE = 4095;
const int WATER_VALUE = 1900;
int moisture_value = 0;
int moisture_percent = 0;

void initMoistureSens()
{
    pinMode(MOISTURE_SENSOR_PIN, INPUT_PULLDOWN);
}

int moistureValue()
{
    moisture_value = analogRead(MOISTURE_SENSOR_PIN);
    return moisture_value;
}

int moisturePercent()
{
    moisture_percent = map(moistureValue(), AIR_VALUE, WATER_VALUE, 0, 100);
    if (moisture_percent >= 100)
    {
        return 100;
    }
    else if (moisture_percent <= 0)
    {
        return 0;
    }
    return moisture_percent;
}

#endif /* MOISTURESENS */
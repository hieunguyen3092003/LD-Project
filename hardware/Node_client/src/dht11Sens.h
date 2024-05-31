#include "cfg.h"

#ifdef DHT11SENS

#define DHT11_SENSOR_PIN GPIO_NUM_33
void initDHT11Sens(void);
float dhtTempValue(void);
float dhtHumidValue(void);

#endif /* DHT11SENS */
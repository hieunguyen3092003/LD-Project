/*
 * dht11Sens.h
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#ifndef SRC_DHT11SENS_H
#define SRC_DHT11SENS_H

#define DHT11_Sensor_Pin GPIO_NUM_33

void initDHT11Sens(void);
float dhtTempValue(void);
float dhtHumidValue(void);

#endif /* SRC_DHT11SENS_H */
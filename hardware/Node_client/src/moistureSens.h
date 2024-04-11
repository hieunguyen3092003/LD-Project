/*
 * moistureSens.h
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#ifndef SRC_MOISTURESENS_H
#define SRC_MOISTURESENS_H

#define Moisture_Sensor_Pin GPIO_NUM_35

void initMoistureSens(void);
int moistureValue(void);
int moisturePercent(void);

#endif /* SRC_MOISTURESENS_H */
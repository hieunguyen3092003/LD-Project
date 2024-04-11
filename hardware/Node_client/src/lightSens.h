/*
 * lightSens.h
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#ifndef SRC_LIGHTSENS_H
#define SRC_LIGHTSENS_H

#define Light_Sensor_Pin GPIO_NUM_34

void initLightSens(void);
int isNight(void);

#endif /* SRC_LIGHTSENS_H */
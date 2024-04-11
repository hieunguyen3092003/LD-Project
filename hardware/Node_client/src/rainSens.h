/*
 * rainSens.h
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#ifndef SRC_RAINSENS_H
#define SRC_RAINSENS_H

#define Rain_Sensor_Pin GPIO_NUM_32

void initRainSens(void);
int isDry(void);

#endif /* SRC_RAINSENS_H */
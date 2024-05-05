/*
 * pump.h
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#ifndef SRC_PUMP_H
#define SRC_PUMP_H

#define Pump_Pin GPIO_NUM_5

void initPump(void);
void pumpTurnOn(void);
void pumpTurnOff(void);
int isPumpOn(void);

#endif /* SRC_PUMP_H */
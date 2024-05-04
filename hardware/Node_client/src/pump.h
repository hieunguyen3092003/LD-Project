/*
 * pump.h
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#ifndef SRC_PUMP_H
#define SRC_PUMP_H

#define Pump_Pin GPIO_NUM_5

extern bool activate_limit;
extern unsigned long pump_on_interval;

void initPump(void);
void pumpAuto(const int &moisture_percent, const int &activate_limit);
void pumpTurnOn(void);
void pumpTurnOff(void);
int isPumpOn(void);

#endif /* SRC_PUMP_H */
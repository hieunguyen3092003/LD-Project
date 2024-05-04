/*
 * numpad.h
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#ifndef SRC_NUMPAD_H
#define SRC_NUMPAD_H

#define Row_0_Pin GPIO_NUM_12
#define Row_1_Pin GPIO_NUM_14
#define Row_2_Pin GPIO_NUM_27
#define Row_3_Pin GPIO_NUM_26

#define Col_0_Pin GPIO_NUM_25
#define Col_1_Pin GPIO_NUM_33
#define Col_2_Pin GPIO_NUM_32
#define Col_3_Pin GPIO_NUM_13

extern char key;

void initNumpad(void);
char numpadGetKey(void);

#endif /* SRC_NUMPAD_H */
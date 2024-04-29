/*
 * button.h
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#ifndef SRC_BUTTON_H
#define SRC_BUTTON_H

#define Button_Pin GPIO_NUM_23

void initButton(void);
bool isButtonDown(void);

#endif /* SRC_BUTTON_H */

/*
 * fsm.h
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#ifndef SRC_FSM_H
#define SRC_FSM_H

enum Mode
{
    mode_init,
    mode_auto,
    mode_timer,
    mode_manual
};
extern Mode current_mode;

#endif /* SRC_FSM_H */
/*
 * fsm.h
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#ifndef SRC_FSM_H
#define SRC_FSM_H

enum mode
{
    mode_auto,
    mode_timer,
    mode_manual
};
extern mode current_mode;

#endif /* SRC_FSM_H */
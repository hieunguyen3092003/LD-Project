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
    mode_init,
    mode_security,
    mode_running,
    mode_modify_pump
};
extern mode current_mode;

void fsmManager(void);

#endif /* SRC_FSM_H */
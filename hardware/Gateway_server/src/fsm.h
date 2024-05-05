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
    mode_modify_password,
    mode_modify_pump,
    mode_security,
    mode_running
};
extern Mode current_mode;

enum Pump_Mode
{
    mode_auto,
    mode_timer,
    mode_manual
};
extern Pump_Mode current_pump_mode;

extern String Password;
extern String passwordInput;

void fsmManager(void);

#endif /* SRC_FSM_H */
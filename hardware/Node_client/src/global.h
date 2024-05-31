#ifndef SRC_GLOBAL_H
#define SRC_GLOBAL_H

#include <Arduino.h>

enum Mode
{
    mode_init,
    mode_auto,
    mode_timer,
    mode_manual
};
extern Mode current_mode;

extern unsigned long current_time;
extern unsigned long last_send_time;

#endif /* SRC_GLOBAL_H */
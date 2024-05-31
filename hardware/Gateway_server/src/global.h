#ifndef SRC_GLOBAL_H
#define SRC_GLOBAL_H

#include <Arduino.h>

enum Pump_Mode
{
    mode_init_node,
    mode_auto,
    mode_timer,
    mode_manual
};
extern Pump_Mode current_pump_mode;

extern unsigned long current_time;
extern unsigned long last_request_time;

typedef struct Message_Send
{
    bool is_button_down;

    int pump_mode;
    int pump_limit;
    int pump_interval;
} Message_Send;
extern Message_Send packet_send;

typedef struct Message_Receive
{
    int moisture_pct;
    float temp;
    float humid;
    bool is_dry;
    bool is_night;

    bool is_pump_on;

    bool warning;
} Message_Receive;
extern Message_Receive packet_receive;

#endif /* SRC_GLOBAL_H */
#include "cfg.h"

#ifdef PUMP

#define PUMP_PIN GPIO_NUM_5
extern int pump_on_limit;
extern int pump_on_interval;
extern unsigned long last_pump_on_time;
void initPump(void);
void pumpTurnOn(void);
void pumpTurnOff(void);
bool isPumpOn(void);
void pumpTimerOff(const int pump_on_interval);

#endif /* PUMP */
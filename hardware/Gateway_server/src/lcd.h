#include "cfg.h"

#ifdef LCD

void initLCD(void);
void lcdTurnOnBacklight(void);
void lcdTurnOffBacklight(void);
void lcdClear(void);
void lcdDisplay(const int &x_coor, const int &y_coor, const String &msg, const int &number, const String &units, bool fill_num);

#endif /* LCD */
#include "cfg.h"

#ifdef ESP_NOWSERVER

void initEsp_now(void);
bool isPacketCannotSent(void);
bool isPacketReceived(void);
void esp_nowSync(void);

#endif /* ESP_NOWSERVER */
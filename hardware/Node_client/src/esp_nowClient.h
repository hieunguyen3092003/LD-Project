#include "cfg.h"

#ifdef ESP_NOWCLIENT

void initEsp_now(void);
bool isPacketReceived(void);
void esp_nowSync(void);

typedef struct Message_Receive
{
    bool is_button_down;

    int pump_mode;
    int pump_limit;
    int pump_interval;
} Message_Receive;
extern Message_Receive packet_receive;

typedef struct Message_Send
{
    int moisture_pct;
    float temp;
    float humid;
    bool is_dry;
    bool is_night;

    bool is_pump_on;

    bool warning;
} Message_Send;
extern Message_Send packet_send;

#endif /* ESP_NOWCLIENT */
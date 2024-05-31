#include "global.h"
#include "esp_nowClient.h"

#ifdef ESP_NOWCLIENT

#include "dht11Sens.h"
#include "lightSens.h"
#include "moistureSens.h"
#include "pump.h"
#include "rainSens.h"
#include <esp_now.h>
#include <WiFi.h>

void initEsp_now(void);
void onDataSent(const uint8_t *macAddr, esp_now_send_status_t status);
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
bool isPacketReceived(void);
void esp_nowSync(void);

// private variables
// Responder MAC Address (Replace with your responders MAC Address)
uint8_t broadcastAddress[] = {0xCC, 0x7B, 0x5C, 0x27, 0xAD, 0x44};

// Register peer
esp_now_peer_info_t peerInfo;

volatile bool is_packet_received = false;

void initEsp_now()
{
    // Set ESP32 WiFi mode to Station temporarly
    WiFi.mode(WIFI_STA);

    // Initialize ESP-NOW
    if (esp_now_init() == ESP_OK)
    {
        Serial.println("ESP-NOW Init Success");
        // Define callback
        esp_now_register_send_cb(onDataSent);
        esp_now_register_recv_cb(OnDataRecv);
    }
    else
    {
        Serial.println("ESP-NOW Init Failed");
        delay(3000);
        ESP.restart();
    }

    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }
}

// Callback function
void onDataSent(const uint8_t *macAddr, esp_now_send_status_t status)
{
    Serial.print("Last Packet Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    // Get incoming data
    memcpy(&packet_receive, incomingData, sizeof(packet_receive));

    Serial.print("Data received: ");
    Serial.println(len);
    Serial.println("Received Success");
    Serial.print("Button: ");
    Serial.println(packet_receive.is_button_down);
    Serial.print("Pump Mode: ");
    Serial.println(packet_receive.pump_mode);
    Serial.print("Limit: ");
    Serial.println(packet_receive.pump_limit);
    Serial.print("Interval: ");
    Serial.println(packet_receive.pump_interval);
    Serial.println();

    is_packet_received = true;
}

bool isPacketReceived()
{
    if (is_packet_received)
    {
        is_packet_received = false;
        return true;
    }
    return false;
}

void esp_nowSync()
{
    packet_send.moisture_pct = moisturePercent();
    packet_send.temp = dhtTempValue();
    packet_send.humid = dhtHumidValue();
    packet_send.is_dry = isDry();
    packet_send.is_night = isNight();
    packet_send.is_pump_on = isPumpOn();
    packet_send.warning = false;

    esp_now_send(broadcastAddress, (uint8_t *)&packet_send, sizeof(packet_send));

    last_send_time = current_time;

    return;
}

#endif /* ESP_NOWCLIENT */
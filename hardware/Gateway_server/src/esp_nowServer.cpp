#include "global.h"
#include "esp_nowServer.h"

#ifdef ESP_NOWSERVER

#include <esp_now.h>
#include <WiFi.h>
#include "espFirebase.h"

void initEsp_now(void);
void onDataSent(const uint8_t *macAddr, esp_now_send_status_t status);
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
bool isPacketCannotSent(void);
bool isPacketReceived(void);
void esp_nowSync(void);

uint8_t broadcastAddress[] = {0xE4, 0x65, 0xB8, 0x1C, 0xF5, 0x54};

esp_now_peer_info_t peerInfo;

volatile bool is_packet_received = false;
volatile bool cannot_sent = false;

void initEsp_now()
{
    // Start ESP32 in Station mode
    WiFi.mode(WIFI_STA);

    // Initalize ESP-NOW
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
    cannot_sent = !(status == ESP_NOW_SEND_SUCCESS);

    Serial.print("Last Packet Send Status: ");
    if (status == ESP_NOW_SEND_SUCCESS)
    {
        Serial.println("Delivery Success");
        Serial.print("Button: ");
        Serial.println(packet_send.is_button_down);
        Serial.print("Pump Mode: ");
        Serial.println(packet_send.pump_mode);
        Serial.print("Limit: ");
        Serial.println(packet_send.pump_limit);
        Serial.print("Interval: ");
        Serial.println(packet_send.pump_interval);
        Serial.println();
    }
    else
    {
        Serial.println("Delivery Fail");
    }
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    // Get incoming data
    memcpy(&packet_receive, incomingData, sizeof(packet_receive));

    is_packet_received = true;
}

bool isPacketCannotSent()
{
    // if (cannot_sent)
    // {
    //     cannot_sent = false;
    //     return true;
    // }
    return false;
}

bool isPacketReceived()
{
    if (is_packet_received)
    {
        is_packet_received = false;

        espFirebaseSync();

        return true;
    }
    return false;
}

void esp_nowSync()
{
    packet_send.pump_mode = current_pump_mode;

    esp_now_send(broadcastAddress, (uint8_t *)&packet_send, sizeof(packet_send));

    last_request_time = current_time;
    return;
}

#endif /* ESP_NOWSERVER */
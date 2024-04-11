/*
 * esp_nowServer.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "global.h"
#include "esp_nowServer.h"

#include <esp_now.h>
#include <WiFi.h>

void initEsp_now(void);
void onDataSent(const uint8_t *macAddr, esp_now_send_status_t status);
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
uint8_t isPacketReceived(void);
void esp_nowRequestData(void);
void esp_nowTurnOnPump(void);
void esp_nowTurnOffPump(void);

float getTemperature(void);
float getHumidity(void);
int getMoistureValue(void);
int getMoisturePercentage(void);
int getPumpStatus(void);
int getDryStatus(void);
int getNightStatus(void);

uint8_t broadcastAddress[] = {0xE4, 0x65, 0xB8, 0x1C, 0xF5, 0x54};

// Define data structure
typedef struct Message_Receive
{
    float temp;
    float humid;
    int moisture_val;
    int moisture_pct;
    int is_pump_on;
    int is_dry;
    int is_night;
} Message_Receive;
Message_Receive packet_receive;

typedef struct Message_Send
{
    bool turn_on_pump;
    bool request_data;
} Message_Send;
Message_Send packet_send;

esp_now_peer_info_t peerInfo;

volatile bool is_packet_received = false;

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
    Serial.print("Last Packet Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    // Get incoming data
    memcpy(&packet_receive, incomingData, sizeof(packet_receive));

    is_packet_received = true;
}

uint8_t isPacketReceived(void)
{
    if (is_packet_received)
    {
        is_packet_received = false;
        return 1;
    }
    return 0;
}

void esp_nowRequestData()
{
    packet_send.request_data = 1;
    packet_send.turn_on_pump = 0;

    esp_now_send(broadcastAddress, (uint8_t *)&packet_send, sizeof(packet_send));
}
void esp_nowTurnOnPump()
{
    packet_send.request_data = 0;
    packet_send.turn_on_pump = 1;

    esp_now_send(broadcastAddress, (uint8_t *)&packet_send, sizeof(packet_send));
}
void esp_nowTurnOffPump()
{
    packet_send.request_data = 0;
    packet_send.turn_on_pump = 0;

    esp_now_send(broadcastAddress, (uint8_t *)&packet_send, sizeof(packet_send));
}

float getTemperature()
{
    return packet_receive.temp;
}
float getHumidity()
{
    return packet_receive.humid;
}
int getMoistureValue()
{
    return packet_receive.moisture_val;
}
int getMoisturePercentage()
{
    return packet_receive.moisture_pct;
}
int getPumpStatus()
{
    return packet_receive.is_pump_on;
}
int getDryStatus()
{
    return packet_receive.is_dry;
}
int getNightStatus()
{
    return packet_receive.is_night;
}
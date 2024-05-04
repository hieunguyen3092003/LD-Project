/*
 * esp_nowClient.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "global.h"
#include "esp_nowClient.h"

#include <esp_now.h>
#include <WiFi.h>

void initEsp_now(void);
void onDataSent(const uint8_t *macAddr, esp_now_send_status_t status);
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
bool isPacketReceived(void);
void esp_nowSendPacket(float temperature, float humidity, int moisture_value, int moisture_percentage, int pump_status, int dry_status, int night_status);
bool getRequestData(void);
bool getPumpOrder(void);

// Responder MAC Address (Replace with your responders MAC Address)
uint8_t broadcastAddress[] = {0xCC, 0x7B, 0x5C, 0x27, 0xAD, 0x44};

typedef struct message_Send
{
    float temp;
    float humid;
    int moisture_val;
    int moisture_pct;
    int is_pump_on;
    int is_dry;
    int is_night;
} message_Send;
message_Send packet_send;

typedef struct Message_Receive
{
    bool turn_on_pump;
    bool request_data;
} Message_Receive;
Message_Receive packet_receive;

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
    Serial.print("Turn On Pump: ");
    Serial.println(packet_receive.turn_on_pump);
    Serial.print("Request Data: ");
    Serial.println(packet_receive.request_data);
    Serial.println();

    is_packet_received = true;
}

bool isPacketReceived(void)
{
    if (is_packet_received)
    {
        is_packet_received = false;
        return true;
    }
    return false;
}

void esp_nowSendPacket(float temperature, float humidity, int moisture_value, int moisture_percentage, int pump_status, int dry_status, int night_status)
{
    packet_send.temp = temperature;
    packet_send.humid = humidity;
    packet_send.moisture_val = moisture_value;
    packet_send.moisture_pct = moisture_percentage;
    packet_send.is_pump_on = pump_status;
    packet_send.is_dry = dry_status;
    packet_send.is_night = night_status;

    esp_now_send(broadcastAddress, (uint8_t *)&packet_send, sizeof(packet_send));
}

bool getRequestData()
{
    return packet_receive.request_data;
}
bool getPumpOrder()
{
    return packet_receive.turn_on_pump;
}
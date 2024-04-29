/*
 * mqtt.cpp
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#include "global.h"
#include "mqtt.h"

#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClient.h>
#include "esp_nowServer.h"

void initMQTT(void);
void callback(char *topic, byte *payload, unsigned int length);
void mqttloop(void);

WiFiClient client;
PubSubClient mqtt_client(client);

// kết nối mqtt
const char *SSID = "MIlo";
const char *PASSWORD = "24682468";
const char *SERVER_MQTT = "192.168.0.105"; // IPv4 Address
const int PORT_MQTT = 1883;
const char *MQTT_ID = "gateway";

// khai báo biến
uint16_t count = 0;
String payload; // gửi JSON
float tmp = 32;
float humi = 69;
uint16_t lux = 0;
uint16_t soil = 0;

const char *TOPIC_SUBSCRIBE = "to-esp32";
const char *TOPIC_PUBLISH = "form-esp32";
const char *PUMP_SUBCRIBE = "pumpControl";

void initMQTT()
{
    Serial.println("Connecting to Wifi....");
    WiFi.begin(SSID, PASSWORD);
    WiFi.reconnect();
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Connected to Wifi: ");
    Serial.println(SSID);
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    delay(1000);

    mqtt_client.setServer(SERVER_MQTT, PORT_MQTT);
    Serial.println("Connecting to mqtt");
    while (!mqtt_client.connect(MQTT_ID))
    {
        delay(500);
    }
    Serial.println("Connected to mqtt");

    mqtt_client.publish(TOPIC_PUBLISH, "hello server");
    mqtt_client.subscribe(TOPIC_SUBSCRIBE);
    mqtt_client.subscribe(PUMP_SUBCRIBE);

    mqtt_client.setCallback(callback); // return data thats this function received
}

void callback(char *topic, byte *payload, unsigned int length)
{
    String message = "";
    for (int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }

    Serial.print("Receive from: ");
    Serial.println(topic);
    Serial.print("Message: ");
    Serial.println(message);

    // Control pump
    if (String(topic) == PUMP_SUBCRIBE)
    {
        if (message == "on")
        {
            esp_nowTurnOnPump();
        }
        else if (message == "off")
        {
            esp_nowTurnOffPump();
        }
    }
}

void mqttloop()
{
    mqtt_client.loop();
}

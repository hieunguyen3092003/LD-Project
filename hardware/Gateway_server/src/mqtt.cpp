// #include "global.h"
// #include "mqtt.h"

// #ifdef MQTT

// #include <WiFi.h>
// #include <PubSubClient.h>
// #include <WiFiClient.h>
// #include "esp_nowServer.h"

// #define WIFI_CONNECT_TIMEOUT 10
// #define MQTT_CONNECT_TIMEOUT 10

// void initMQTT(void);
// void callback(char *topic, byte *payload, unsigned int length);
// void mqttData(void);
// void mqttStoreData(void);
// void mqttSendData(void);
// void mqttLoop(void);

// WiFiClient client;
// PubSubClient mqtt_client(client);

// String payload; // gửi JSON

// // kết nối mqtt
// const char *SSID = "BKIT_LUGIA_CS2";
// const char *PASSWORD = "cselabc5c6";
// const char *SERVER_MQTT = "192.168.0.105"; // IPv4 Address
// const int PORT_MQTT = 1883;
// const char *MQTT_ID = "gateway";

// // Các kênh gửi thông tin(publish)
// const char *dataStore_publish = "dataStore";
// const char *dataSend_publish = "dataSend";
// const char *warning_publish = "warning_publish";
// const char *pumpControl_publish = "pumpControl_publish";

// // Các kênh đăng kí(subcribe)
// const char *pumpControl_subcribe = "pumpControl";
// const char *warning_subcribe = "warning_subcribe";

// void initMQTT()
// {
//     Serial.println("Connecting to WiFi...");
//     WiFi.begin(SSID, PASSWORD);

//     unsigned long startTime = millis();
//     while (WiFi.status() != WL_CONNECTED && millis() - startTime < WIFI_CONNECT_TIMEOUT * 1000)
//     {
//         delay(500);
//         Serial.print(".");
//     }

//     if (WiFi.status() == WL_CONNECTED)
//     {
//         Serial.println("\nConnected to WiFi");
//         Serial.print("IP Address: ");
//         Serial.println(WiFi.localIP());

//         mqtt_client.setServer(SERVER_MQTT, PORT_MQTT);
//         Serial.println("Connecting to MQTT...");

//         startTime = millis();
//         while (!mqtt_client.connected() && millis() - startTime < MQTT_CONNECT_TIMEOUT * 1000)
//         {
//             if (mqtt_client.connect(MQTT_ID))
//             {
//                 Serial.println("Connected to MQTT");
//                 mqtt_client.subscribe(pumpControl_subcribe);
//                 mqtt_client.subscribe(warning_subcribe);
//                 mqtt_client.setCallback(callback);
//             }
//             else
//             {
//                 Serial.print(".");
//                 delay(500);
//             }
//         }

//         if (!mqtt_client.connected())
//         {
//             Serial.println("\nFailed to connect to MQTT");
//         }
//     }
//     else
//     {
//         Serial.println("\nFailed to connect to WiFi");
//     }
// }

// void callback(char *topic, byte *payload, unsigned int length)
// {
//     String message = "";
//     for (int i = 0; i < length; i++)
//     {
//         message += (char)payload[i];
//     }

//     Serial.print("Receive from: ");
//     Serial.println(topic);
//     Serial.print("Message: ");
//     Serial.println(message);

//     // Control pump
//     if (String(topic) == pumpControl_subcribe)
//     { // bật tắt máy bơm từ website
//         if (message == "true")
//         {
//             // esp_nowTurnOnPump();
//             // esp_nowRequestData();
//         }
//     }

//     // xác nhận có thiết bị bị hư hỏng
//     if (String(topic) == warning_subcribe)
//     {
//         // Handle warnings if needed
//     }
// }

// void mqttData()
// {
//     // payload = "{\"temperature\": " + String(packet_receive.temp) + ", \"humidity\": " + String(packet_receive.humid) + ", \"soil\": " + String(packet_receive.moisture_pct) + ", \"brightness_level\": " + String(packet_receive.is_night) + ", \"__v\": 0}";
// }

// void mqttStoreData()
// {
//     mqtt_client.publish(dataStore_publish, payload.c_str());
// }

// void mqttSendData()
// {
//     mqtt_client.publish(dataSend_publish, payload.c_str());
// }

// void mqttLoop()
// {
//     mqtt_client.loop();
// }

// #endif /* MQTT */
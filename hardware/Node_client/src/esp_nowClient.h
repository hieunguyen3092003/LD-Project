/*
 * esp_nowClient.h
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#ifndef SRC_ESP_NOWCLIENT_H
#define SRC_ESP_NOWCLIENT_H

void initEsp_now(void);
void esp_nowSendPacket(float temperature, float humidity, int moisture_value, int moisture_percentage, int pump_status, int dry_status, int night_status);
bool isPacketSent(void);
bool isPacketReceived(void);
bool getRequestData(void);
bool getPumpOrder(void);
int getPumpMode(void);

#endif /* SRC_ESP_NOWCLIENT_H */
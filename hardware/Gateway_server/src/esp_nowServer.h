/*
 * esp_nowServer.h
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#ifndef SRC_ESP_NOWSERVER_H
#define SRC_ESP_NOWSERVER_H

void initEsp_now(void);
bool isPacketSent(void);
bool isPacketReceived(void);
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

#endif /* SRC_ESP_NOWSERVER_H */
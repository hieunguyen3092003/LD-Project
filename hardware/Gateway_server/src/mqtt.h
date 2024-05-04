/*
 * mqtt.h
 *
 *  Created on: feb 5, 2023
 *      Author: hieun
 */

#ifndef SRC_MQTT_H
#define SRC_MQTT_H

void initMQTT(void);
void mqttData(void);
void mqttStoreData(void);
void mqttSendData(void);
void mqttLoop(void);

#endif /* SRC_MQTT_H */
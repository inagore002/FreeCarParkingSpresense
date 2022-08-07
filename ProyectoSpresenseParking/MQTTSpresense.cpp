#include <stdio.h> 
#include <stdlib.h>
#include <Arduino.h>  //For Serial
#include "BSP/spresense.h"   /* Include board defines */
#include <ArduinoMqttClient.h>
#include "LIB/SDCARD/inc/SDCardSpresense.h"
#include "LIB/LTE/inc/LTESpresense.h"
#include <LTE.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>

#ifdef RTC_PRESENT
#include "LIB/RTC/inc/RTCSpresense.h"
#endif /* RTC_PRESENT */

#ifdef MQTT_PRESENT
LTETLSClient client;
MqttClient mqttClient(client);

char broker[] = BROKER_NAME;
int port      = BROKER_PORT;
char topic[]  = MQTT_TOPIC;

static bool flagMQTTRequest = false;

void messageHandler(char *topic, byte *payload, unsigned int length);

void MQTT_fnSendMessage_vo(String vF_sMessage, char *vF_cTopic)
{
    // send message, the Print interface can be used to set the message contents
    mqttClient.beginMessage(vF_cTopic);
    mqttClient.print(vF_sMessage);
    mqttClient.endMessage();
}

void MQTT_fnSetCACertificate_vo(void)
{
  File rootCertsFile = SDCARD_fnOpen_vo(ROOTCA_FILE);
  client.setCACert(rootCertsFile, rootCertsFile.available());
  rootCertsFile.close();
}
void MQTT_fnSetCertificate_vo(void)
{
  File certsFile = SDCARD_fnOpen_vo(CERT_FILE);
  client.setCertificate(certsFile, certsFile.available());
  certsFile.close();
  
}
void MQTT_fnSetPrivateKey_vo(void)
{
  File priKeyFile = SDCARD_fnOpen_vo(KEY_FILE);
  client.setPrivateKey(priKeyFile, priKeyFile.available());
  priKeyFile.close();
}

bool MQTT_fnConnect_b(char *vF_cBroker, int vF_iPort)
{
  bool bRet = false;

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(vF_cBroker);

  if (!mqttClient.connect(vF_cBroker, vF_iPort)) 
  {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    // do nothing forevermore:
  }
  else
  {
    Serial.println("You're connected to the MQTT broker!");
    bRet = true;
  }

  return(bRet);
}

void MQTT_fnInitialize_vo(void)
{
  //Set certifications via a file on the SD card before connecting to the MQTT broker
  MQTT_fnSetCACertificate_vo();
  MQTT_fnSetCertificate_vo();
  MQTT_fnSetPrivateKey_vo();
  MQTT_fnConnect_b(broker, port);
}

void MQTT_fnReceiveInit_vo(void)
{
  // Subscribe to MQTT and register a callback
  mqttClient.onMessage(messageHandler);
  mqttClient.subscribe(MQTT_TOPIC);
}


void MQTT_fnPoll_vo(void)
{
  mqttClient.poll();
}

void messageHandler(char *topic, byte *payload, unsigned int length) 
{
  unsigned long RTCAlarm;
  bool CarParkCheckRequest;

#ifdef SERIAL_PRINT_DEBUG
  // we received a message, print out the topic and contents
  Serial.print("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.println("'");
#endif /* SERIAL_PRINT_DEBUG */

  /* Check JSON received data. */
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, mqttClient);
  
  /* Get RTCAlarm value. */
  RTCAlarm = doc["alarm"];
  Serial.print("Alarm Time:");
  Serial.println(RTCAlarm);
  RTC_fnSetAlarm_vo(RTCAlarm);    /* Set RTC alarm for a periodic interruption */

  /* Get if there is a request to check the parking spaces. */
  CarParkCheckRequest = doc["request"];
  if(true == CarParkCheckRequest)
  {
    Serial.print("Request:");
    Serial.println(CarParkCheckRequest);
    flagMQTTRequest = true;
  }
}

bool MQTT_fnIsMQTTRequestActivated_b(void)
{
  return(flagMQTTRequest);
}

void MQTT_fnClearMQTTRequestFlag_vo(void)
{
  flagMQTTRequest = false;
}

#endif /* MQTT_PRESENT */

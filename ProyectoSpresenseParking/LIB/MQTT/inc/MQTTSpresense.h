#ifndef _MQTT_SPRESENSE_H_
#define _MQTT_SPRESENSE_H_
/********************************************************************************
-----> FUNCTIONS
********************************************************************************/
void MQTT_fnSendMessage_vo(String vF_sMessage, char *vF_cTopic);
void MQTT_fnSetCACertificate_vo(void);
void MQTT_fnSetCertificate_vo(void);
void MQTT_fnSetPrivateKey_vo(void);
bool MQTT_fnConnect_b(char *vF_cBroker, int vF_iPort);
void MQTT_fnInitialize_vo(void);
void MQTT_fnReceiveInit_vo(void);
void MQTT_fnPoll_vo(void);
bool MQTT_fnIsMQTTRequestActivated_b(void);
void MQTT_fnClearMQTTRequestFlag_vo(void);

#endif /* _MQTT_SPRESENSE_H_ */
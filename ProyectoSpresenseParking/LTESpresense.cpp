/********************************************************************************
-----> INCLUDES
********************************************************************************/
#include <stdio.h> 
#include <stdlib.h>
#include <Arduino.h>  //For Serial
#include "BSP/spresense.h"   /* Include board defines */

/********************************************************************************
-----> DEFINITIONS
********************************************************************************/

/********************************************************************************
-----> VARIABLES
********************************************************************************/
// initialize the library instance
LTEModem modem;
// initialize the library instance
LTE        lteAccess;
LTEScanner scannerNetworks;
unsigned long LocalTime;
// IMEI variable
String IMEI             =     "";
String VERSION          =     "";
LTENetworkRatType RAT   =     LTE_NET_RAT_UNKNOWN; /* LTE_NET_RAT_NBIOT, LTE_NET_RAT_CATM */
/********************************************************************************
-----> FUNCTIONS
********************************************************************************/
bool LTE_fnInitialize_b(void)
{
  bool bRet = false;
  char apn[LTE_NET_APN_MAXLEN] = APP_LTE_APN;
  LTENetworkAuthType authtype = APP_LTE_AUTH_TYPE;
  char user_name[LTE_NET_USER_MAXLEN] = APP_LTE_USER_NAME;
  char password[LTE_NET_PASSWORD_MAXLEN] = APP_LTE_PASSWORD;

  if(lteAccess.begin() != LTE_SEARCHING)
  {
#ifdef SERIAL_PRINT_DEBUG
    Serial.println("Could not transition to LTE_SEARCHING.");
#endif /* SERIAL_PRINT */
  }
  else
  {
    /* The connection process to the APN will start.
     * If the synchronous parameter is false,
     * the return value will be returned when the connection process is started.
     */
    if (lteAccess.attach(APP_LTE_RAT,
                         apn,
                         user_name,
                         password,
                         authtype,
                         APP_LTE_IP_TYPE) == LTE_READY) 
    {
#ifdef SERIAL_PRINT_DEBUG
      Serial.println("attach succeeded.");
#endif /* SERIAL_PRINT */
    }
  }

  return(bRet);
}

uint32_t LTE_fnGetTime_u32(void)
{
  uint32_t u32Ret = 0;
  u32Ret = lteAccess.getTime();
  /* Convertir segundos a calendario */
#ifdef SERIAL_PRINT_DEBUG
  Serial.println(u32Ret);
#endif /* SERIAL_PRINT */
  return(u32Ret);
}

void LTE_fnDoAttach_vo(void)
{
  char apn[LTE_NET_APN_MAXLEN] = APP_LTE_APN;
  LTENetworkAuthType authtype = APP_LTE_AUTH_TYPE;
  char user_name[LTE_NET_USER_MAXLEN] = APP_LTE_USER_NAME;
  char password[LTE_NET_PASSWORD_MAXLEN] = APP_LTE_PASSWORD;

  /* Set if Access Point Name is empty */
  if (strlen(APP_LTE_APN) == 0) {
    Serial.println("This sketch doesn't have a APN information.");
    //readApnInformation(apn, &authtype, user_name, password);
  }
  Serial.println("=========== APN information ===========");
  Serial.print("Access Point Name  : ");
  Serial.println(apn);
  Serial.print("Authentication Type: ");
  Serial.println(authtype == LTE_NET_AUTHTYPE_CHAP ? "CHAP" :
                 authtype == LTE_NET_AUTHTYPE_NONE ? "NONE" : "PAP");
  if (authtype != LTE_NET_AUTHTYPE_NONE) {
    Serial.print("User Name          : ");
    Serial.println(user_name);
    Serial.print("Password           : ");
    Serial.println(password);
  }

  while (true) {

    /* Power on the modem and Enable the radio function. */

    if (lteAccess.begin() != LTE_SEARCHING) {
      Serial.println("Could not transition to LTE_SEARCHING.");
      Serial.println("Please check the status of the LTE board.");
      for (;;) {
        sleep(1);
      }
    }

    /* The connection process to the APN will start.
     * If the synchronous parameter is false,
     * the return value will be returned when the connection process is started.
     */
    if (lteAccess.attach(APP_LTE_RAT,
                         apn,
                         user_name,
                         password,
                         authtype,
                         APP_LTE_IP_TYPE,
                         false) == LTE_CONNECTING) {
      Serial.println("Attempting to connect to network.");
      break;
    }
    /* If the following logs occur frequently, one of the following might be a cause:
     * - APN settings are incorrect
     * - SIM is not inserted correctly
     * - If you have specified LTE_NET_RAT_NBIOT for APP_LTE_RAT,
     *   your LTE board may not support it.
     */
    Serial.println("An error has occurred. Shutdown and retry the network attach preparation process after 1 second.");
    lteAccess.shutdown();
    sleep(1);
  }
}

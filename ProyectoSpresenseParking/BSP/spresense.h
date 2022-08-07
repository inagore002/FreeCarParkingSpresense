/*
 *  spresense.h - Board definition file
 *  
 *
 */
#ifndef _SPRESENSE_H_
#define _SPRESENSE_H_

/********************************************************************************
-----> PROJECT SELECTOR (Select the project you want to compile and flash)
********************************************************************************/
//#define PROJECT_TAKE_PHOTOS                 /* This project takes photos and save them in a SD Card */
#define PROJECT_CAR_PARKING_SPACES            /* This project takes photos and checks if there is free car parking space. 
                                              /* Sends/Receives data through MQTT to AWS IoT */

/********************************************************************************
-----> PROJECT FEATURES
********************************************************************************/
/***** PROJECT_TAKE_PHOTOS *****/
#ifdef PROJECT_TAKE_PHOTOS
#define SERIAL_PRINT_DEBUG                      /* Used to check through the Serial Terminal what's happening */
#define CAMERA_PRESENT                          /* Used to activate camera functions to take photos */
#define SDCARD_PRESENT                          /* Used to save the taken photos to the SD Card */    
#define LTE_PRESENT                             /* Used to check current time and to load the RTC timer */
#define RTC_PRESENT                             /* Used to configure the RTC alarm to take photos periodically */
#define SERVO_PRESENT                           /* Used to move a servo motor and check different street angles */                
//#define MQTT_PRESENT                          /* Used for MQTT protocol with AWS IoT */
//#define EDGE_IMPULSE_OBJECT_DETECTION_PRESENT   /* Used to check free car parking space thank's to Edge Impulse library */ 
#define BRD_DEBUG 
#endif /* PROJECT_TAKE_PHOTOS */

/***** PROJECT_CAR_PARKING_SPACES *****/
#ifdef PROJECT_CAR_PARKING_SPACES
#define SERIAL_PRINT_DEBUG                      /* Used to check through the Serial Terminal what's happening */   
#define CAMERA_PRESENT                          /* Used to activate camera functions to take photos */
#define SDCARD_PRESENT                          /* Used to get the AWS Certificates for AWS IoT connection */ 
#define LTE_PRESENT                             /* Used for wireless communication and get current time */
#define RTC_PRESENT                             /* Used for periodical events for free space checking */
#define SERVO_PRESENT                           /* Used to move a servo motor and check different street angles */
#define MQTT_PRESENT                            /* Used for MQTT protocol with AWS IoT */
#define EDGE_IMPULSE_OBJECT_DETECTION_PRESENT /* Used to check free car parking space thank's to Edge Impulse library */ 
#define BRD_DEBUG
#endif /* PROJECT_CAR_PARKING_SPACES */



/********************************************************************************
-----> MQTT
********************************************************************************/
#ifdef MQTT_PRESENT

#define BROKER_NAME                 "" // replace with your broker
#define BROKER_PORT                 8883                                // port 8883 is the default for MQTT over TLS.
#define ROOTCA_FILE                 "CERTS/AmazonRootCA1_MyBoard.pem"   // Define the path to a file containing CA
                                                                        // certificates that are trusted. Define with the file saved in your SDCard.
#define CERT_FILE                   "CERTS/MyBoard-certificate.pem.crt" // Define the path to a file containing certificate
                                                                        // for this client, if required by the server. Define with the file saved in your SDCard.
#define KEY_FILE                    "CERTS/MyBoard-private.pem.key"     // Define the path to a file containing private key
                                                                        // for this client, if required by the server. Define with the file saved in your SDCard.

// MQTT topic
#define MQTT_TOPIC                  "spresense/freeParking"             /* Topic used to request the Car park check, */
                                                                        /* and to answer if there is free car park space */

#endif /* MQTT_PRESENT */
/********************************************************************************
-----> LTE
********************************************************************************/
#ifdef LTE_PRESENT
#include <LTE.h>                    /* Include for LTE */
#define APP_LTE_APN                 "iot.truphone.com"
#define APP_LTE_USER_NAME           ""
#define APP_LTE_PASSWORD            ""
// APN IP type
#define APP_LTE_IP_TYPE             (LTE_NET_IPTYPE_V4V6) // IP : IPv4v6
//#define APP_LTE_IP_TYPE           (LTE_NET_IPTYPE_V4) // IP : IPv4
// #define APP_LTE_IP_TYPE          (LTE_NET_IPTYPE_V6) // IP : IPv6
// APN authentication type
#define APP_LTE_AUTH_TYPE           (LTE_NET_AUTHTYPE_CHAP) // Authentication : CHAP
//#define APP_LTE_AUTH_TYPE         (LTE_NET_AUTHTYPE_PAP) // Authentication : PAP
//#define APP_LTE_AUTH_TYPE         (LTE_NET_AUTHTYPE_NONE) // Authentication : NONE

/* RAT to use
 * Refer to the cellular carriers information
 * to find out which RAT your SIM supports.
 * The RAT set on the modem can be checked with LTEModemVerification::getRAT().
 */
#define APP_LTE_RAT                 (LTE_NET_RAT_CATM) // RAT : LTE-M (LTE Cat-M1)
// #define APP_LTE_RAT              (LTE_NET_RAT_NBIOT) // RAT : NB-IoT
#endif /* LTE_PRESENT */

/********************************************************************************
-----> CAMERA
********************************************************************************/
#ifdef CAMERA_PRESENT
//Includes
#include <Camera.h>           /* Include for Camera */
#define CAMERA_IMAGE_HEIGHT         160                     /* Photo height */
#define CAMERA_IMAGE_WIDTH          160                     /* Photo width */
#define CAMERA_FPS_VALUE            CAM_VIDEO_FPS_6         /* Frames per seconds */
#endif /* CAMERA_PRESENT */

/********************************************************************************
-----> SDCARD
********************************************************************************/
#ifdef SDCARD_PRESENT
#include <SDHCI.h>            /* Include for SD card */  
#endif /* SDCARD_PRESENT */

/********************************************************************************
-----> RTC
********************************************************************************/
#ifdef RTC_PRESENT
#include <RTC.h>
#define DEFAULT_ALARM_TIME_SEC_U    30                      /* 30 seconds for default alarm time */
#endif /* RTC_PRESENT */

/********************************************************************************
-----> SERVO MOTOR
********************************************************************************/
#ifdef SERVO_PRESENT
#include <Servo.h>
#define SERVO_PIN                   PIN_D03                 /* Servomotor connected to this pin */
#endif /* SERVO_PRESENT */

#endif /* _SPRESENSE_H_ */
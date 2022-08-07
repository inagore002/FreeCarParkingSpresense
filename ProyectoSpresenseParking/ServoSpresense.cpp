#include <stdio.h> 
#include <stdlib.h>
#include <Arduino.h>  //For Serial
#include "BSP/spresense.h"   /* Include board defines */
#include "LIB/MOT/inc/ServoSpresense.h"

static Servo s_servo; /**< Servo object */

void SERVO_fnInitialize_vo(void)
{
  s_servo.attach(SERVO_PIN);
}

void SERVO_fnMoveToAngle_vo(uint8_t vF_u8Angle)
{
  uint8_t u8Angle;
  u8Angle = s_servo.read();
  if(u8Angle < vF_u8Angle)
  {
    for (u8Angle; u8Angle <= vF_u8Angle; u8Angle += 1) 
    { // in steps of 1 degree
      s_servo.write(u8Angle);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15 ms for the servo to reach the position
    }
  }
  else
  {
    for (u8Angle; u8Angle > vF_u8Angle; u8Angle -= 1) 
    { // in steps of 1 degree
      s_servo.write(u8Angle);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15 ms for the servo to reach the position
    }
  }

  
}
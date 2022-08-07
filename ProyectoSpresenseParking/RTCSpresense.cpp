#include <stdio.h> 
#include <stdlib.h>
#include <Arduino.h>  //For Serial
#include "BSP/spresense.h"   /* Include board defines */
#include "LIB/RTC/inc/RTCSpresense.h"

static bool flagRTCAlarm = false;
uint32_t rtcAlarmTime = 0;
void rtc_fnCallBackAlarmExpired_vo();
void RTC_fnInitialize_vo(void)
{
  RTC.begin();
  RTC_fnAddAlarm_vo();
}

void RTC_fnAddAlarm_vo(void)
{
  // Set the RTC alarm handler
  RTC.attachAlarm(rtc_fnCallBackAlarmExpired_vo);
}

void RTC_fnSetAlarm_vo(uint32_t vF_u32Seconds)
{
  if(0 != vF_u32Seconds)
  {/* When alarm time is 0, alarm is disabled */
      rtcAlarmTime = vF_u32Seconds;
      RtcTime now = RTC.getTime();
      now += vF_u32Seconds;
      RTC.setAlarm(now);
  }
}

void RTC_fnSetTime_vo(RtcTime vF_u32Seconds)
{
  RTC.setTime(vF_u32Seconds);
}

bool RTC_fnIsAlarmActivated_b(void)
{
  return(flagRTCAlarm);
}

void RTC_fnClearAlarmFlag_vo(void)
{
  flagRTCAlarm = false;
}

RtcTime RTC_fnGetTime_vo(void)
{
  return(RTC.getTime());
}


void rtc_fnCallBackAlarmExpired_vo(void)
{
  RtcTime now = RTC.getTime();

  // Set the RTC alarm every rtcAlarmTime seconds
  RtcTime alm = now + rtcAlarmTime;
  RTC.setAlarm(alm);

  if(false == flagRTCAlarm)
  {
    flagRTCAlarm = true;
  }
}
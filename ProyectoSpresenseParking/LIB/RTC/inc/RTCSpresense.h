#ifndef _RTC_SPRESENSE_H_
#define _RTC_SPRESENSE_H_
 

/********************************************************************************
-----> FUNCTIONS
********************************************************************************/
void RTC_fnSetTime_vo(RtcTime vF_u32Seconds);
void RTC_fnSetAlarm_vo(uint32_t vF_u32Seconds);
void RTC_fnAddAlarm_vo(void);
void RTC_fnInitialize_vo(void);
bool RTC_fnIsAlarmActivated_b(void);
void RTC_fnClearAlarmFlag_vo(void);
RtcTime RTC_fnGetTime_vo(void);

#endif /* _RTC_SPRESENSE_H_ */
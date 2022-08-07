#ifndef _SDCARD_SPRESENSE_H_
#define _SDCARD_SPRESENSE_H_
/********************************************************************************
-----> FUNCTIONS
********************************************************************************/
bool SDCARD_fnInitialize_b(void);
void SDCARD_fnSaveFile_vo(char *vF_Filename, const char *vF_Buffer, size_t vF_Size);
File SDCARD_fnOpen_vo(char *vF_Filename);

#endif /* _SDCARD_SPRESENSE_H_ */
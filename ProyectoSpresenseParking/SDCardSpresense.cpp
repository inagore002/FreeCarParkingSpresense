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
SDClass  theSD;
/********************************************************************************
-----> FUNCTIONS
********************************************************************************/
bool SDCARD_fnInitialize_b(void)
{
  bool bRet = false;

  while (!theSD.begin()) 
  {
#ifdef SERIAL_PRINT_DEBUG
    Serial.println("Insert SD card.");  /* wait until SD card is mounted. */
#endif /* SERIAL_PRINT */
  }
  bRet = true;
  return(bRet);
}

void SDCARD_fnSaveFile_vo(char *vF_Filename, const char *vF_Buffer, size_t vF_Size)
{
  theSD.remove(vF_Filename);
  File myFile = theSD.open(vF_Filename, FILE_WRITE);
  myFile.write(vF_Buffer, vF_Size);
  myFile.close();
}

File SDCARD_fnOpen_vo(char *vF_Filename) 
{
  File rootCertsFile = theSD.open(vF_Filename, FILE_READ);
  return(rootCertsFile);
}
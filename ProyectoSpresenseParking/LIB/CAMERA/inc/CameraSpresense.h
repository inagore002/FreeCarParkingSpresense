#ifndef _CAMERA_SPRESENSE_H_
#define _CAMERA_SPRESENSE_H_
/********************************************************************************
-----> FUNCTIONS
********************************************************************************/
bool CAMERA_fnInitialize_b(void);
CamImage CAMERA_fnTakePicture_CamImage(void);
bool CAMERA_fnIsImageAvailable_b(CamImage vF_Image);
bool CAMERA_fnSetAutoWhiteBalanceMode_b(void);
bool CAMERA_fnSetStillPictureImageFormat_b(void);
void CAMERA_fnStop_vo(void);
bool CAMERA_fnStart_b(void);

#endif /* _CAMERA_SPRESENSE_H_ */
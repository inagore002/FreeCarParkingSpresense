/********************************************************************************
-----> INCLUDES
********************************************************************************/
#include <stdio.h> 
#include <stdlib.h>
#include <Arduino.h>  //For Serial
#include "BSP/spresense.h"   /* Include board defines */
#include "LIB/CAMERA/inc/CameraSpresense.h"

/********************************************************************************
-----> DEFINITIONS
********************************************************************************/

/********************************************************************************
-----> VARIABLES
********************************************************************************/
/********************************************************************************
-----> FUNCTIONS
********************************************************************************/
static void camera_fnCallBack_vo(CamImage vF_Image);

bool CAMERA_fnInitialize_b(void)
{
  bool bRet = true;
  CamErr err = CAM_ERR_SUCCESS;

#ifdef SERIAL_PRINT_DEBUG
  Serial.println("Prepare camera");
#endif /* SERIAL_PRINT_DEBUG */

  err = theCamera.begin(1, 
                        CAMERA_FPS_VALUE, 
                        CAMERA_IMAGE_HEIGHT, 
                        CAMERA_IMAGE_WIDTH, 
                        CAM_IMAGE_PIX_FMT_YUV422, 
                        1); /* begin() without parameters means that number of buffers = 1, 30FPS, QVGA, YUV 4:2:2 format */
  if (err != CAM_ERR_SUCCESS)
  {
    bRet = false;
  }

  return(bRet);
}

bool CAMERA_fnStart_b(void)
{
  bool bRet = true;
  CamErr err = CAM_ERR_SUCCESS;
  /* Start video stream.
   * If received video stream data from camera device,
   *  camera library call CamCB.
   */
#ifdef SERIAL_PRINT_DEBUG
  Serial.println("Start streaming");
#endif /* SERIAL_PRINT_DEBUG */
  err = theCamera.startStreaming(true, camera_fnCallBack_vo);
  if (err != CAM_ERR_SUCCESS)
  {
      bRet = false;
  }
  else
  {
    if(true == CAMERA_fnSetAutoWhiteBalanceMode_b())
    {
      if(false == CAMERA_fnSetStillPictureImageFormat_b())
      {
        bRet = false;
      }
    }
    else
    {
      bRet = false;
    }
  }

  return(bRet);
}

void CAMERA_fnStop_vo(void)
{
  Serial.println("Stop");
  theCamera.startStreaming(false, camera_fnCallBack_vo);
  //theCamera.end();
}

bool CAMERA_fnSetStillPictureImageFormat_b(void)
{
  bool bRet = true;
  CamErr err = CAM_ERR_SUCCESS;
  /* Set parameters about still picture.
   * In the following case, QUADVGA and JPEG.
   */
#ifdef SERIAL_PRINT_DEBUG
  Serial.println("Set still picture format");
#endif /* SERIAL_PRINT_DEBUG */
   
  err = theCamera.setStillPictureImageFormat(CAMERA_IMAGE_HEIGHT,
                                            CAMERA_IMAGE_WIDTH,
#ifdef PROJECT_TAKE_PHOTOS
                                            CAM_IMAGE_PIX_FMT_RGB565,
#else
                                            CAM_IMAGE_PIX_FMT_RGB565,
#endif /* PROJECT_TAKE_PHOTOS */ 
                                            1);
  if (err != CAM_ERR_SUCCESS)
  {
      bRet = false;
      Serial.println(err);
  }

  return(bRet); 
}

CamImage CAMERA_fnTakePicture_CamImage(void)
{
  CamImage Image;
#ifdef SERIAL_PRINT_DEBUG
  Serial.println("Picture taken");
#endif /* SERIAL_PRINT_DEBUG */
  Image = theCamera.takePicture();
  return(Image);
}

bool CAMERA_fnIsImageAvailable_b(CamImage vF_Image)
{
  return(vF_Image.isAvailable());
}

bool CAMERA_fnSetAutoWhiteBalanceMode_b(void)
{
  bool bRet = true;
  CamErr err = CAM_ERR_SUCCESS;
  /* Auto white balance configuration */
#ifdef SERIAL_PRINT_DEBUG
  Serial.println("Set Auto white balance parameter");
#endif /* SERIAL_PRINT_DEBUG */
  err = theCamera.setAutoWhiteBalanceMode(CAM_WHITE_BALANCE_AUTO);
  if (err != CAM_ERR_SUCCESS)
  {
      bRet = false;
  }

  return(bRet);
}

/****************************************************************************
 * Callback from Camera library when video frame is captured.
 ****************************************************************************/
static void camera_fnCallBack_vo(CamImage vF_Image)
{
  /* Check the img instance is available or not. */
  CamErr Error =  CAM_ERR_SUCCESS;
  if (vF_Image.isAvailable())
  {
    /* You can use image data directly by using getImgSize() and getImgBuff().
    * for displaying image to a display, etc. */
#ifdef SERIAL_PRINT_DEBUG
     Serial.print("Image data size = ");
     Serial.print(vF_Image.getImgSize(), DEC);
     Serial.print(" , ");

     Serial.print("buff addr = ");
     Serial.print((unsigned long)vF_Image.getImgBuff(), HEX);
     Serial.println("");
#endif /* SERIAL_PRINT_DEBUG */
  }
  else
  {
#ifdef SERIAL_PRINT_DEBUG
    Serial.println("Failed to get video stream image");
#endif /* SERIAL_PRINT_DEBUG */
  }
}


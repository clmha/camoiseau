#ifndef _CAMOISEAU_DC_
#define _CAMOISEAU_DC_

#include <ArduCAM.h>
#include <SD.h>
#include <SPI.h>

#include "memorysaver.h"

#define CAMOISEAU_CAMERA_CS 9
#define CAMOISEAU_CAMERA_CAPTURESIZESTR_LENGTH 10

extern ArduCAM camera;
const int camoiseauDcAvailableCaptureSizes[] = {
  OV2640_160x120,
  OV2640_176x144,
  OV2640_320x240,
  OV2640_352x288,
  OV2640_800x600,
  OV2640_1024x768,
  OV2640_1280x1024,
  OV2640_1600x1200,
};

void convertCaptureSizeToString(char *captureSizeStr);
int initializeCamera();
void savePicture(const char* str);
int getCaptureSize();
void setCaptureSize(int size);
const int* getCaptureSizes();
int findCaptureSize(int size);
void enterCameraLowPowerMode();
void exitCameraLowPowerMode();

#endif

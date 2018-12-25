/*CAMOISEAU_DC Camoiseau Digital Camera Module
 * 
 */

#include "camoiseau_dc.h"

#define AVIOFFSET 240
#define rate 0x05

ArduCAM camera(OV2640, CAMOISEAU_CAMERA_CS);

const char zero_buf[4] = {0x00, 0x00, 0x00, 0x00};

int captureSize = OV2640_1600x1200;

unsigned long jpeg_size = 0;

void convertCaptureSizeToString(char *captureSizeStr) {
  //CONVERTCAPTURESIZETOSTRING Gives an array of character describing the current capture size

  switch(captureSize) {
    case OV2640_160x120:
      strcpy(captureSizeStr, "160x120");
      break;
    case OV2640_176x144:
      strcpy(captureSizeStr, "176x144");
      break;
    case OV2640_320x240:
      strcpy(captureSizeStr, "320x240");
      break;
    case OV2640_352x288:
      strcpy(captureSizeStr, "352x288");
      break;
    case OV2640_800x600:
      strcpy(captureSizeStr, "800x600");
      break;
    case OV2640_1024x768:
      strcpy(captureSizeStr, "1024x768");
      break;
    case OV2640_1280x1024:
      strcpy(captureSizeStr, "1280x1024");
      break;
    case OV2640_1600x1200:
      strcpy(captureSizeStr, "1600x1200");
      break;
  }
}

int initializeCamera() {
  //INITIALIZECAMERA Prepare the camera for use

  const int pause_ms = 1000;
  uint8_t pid, tmp, vid;

  // Set the SPI component select pin as an ouput
  pinMode(CAMOISEAU_CAMERA_CS, OUTPUT);

  // Check SPI Connection
  do {
    camera.write_reg(ARDUCHIP_TEST1, 0x55);
    tmp = camera.read_reg(ARDUCHIP_TEST1);

    if (tmp != 0x55) {
      delay(pause_ms);
    }
  } while (tmp != 0x55);
  exitCameraLowPowerMode(); // In case it was sleeping before initialization

  // Check camera module type
  while (1) {
    camera.wrSensorReg8_8(0xff, 0x01);
    camera.rdSensorReg8_8(OV2640_CHIPID_HIGH, &vid);
    camera.rdSensorReg8_8(OV2640_CHIPID_LOW, &pid);

    if ((vid != 0x26) && ((pid != 0x41) || (pid != 0x42))) {
      delay(pause_ms);
    }
    else {
      break;
    }
  }

  camera.set_format(JPEG);
  camera.InitCAM();
  camera.OV2640_set_JPEG_size(captureSize);

  return 0;
}

void setCaptureSize(int in_captureSize) {
  //SETCAPTURESIZE Set the capture size of the camera

  captureSize = in_captureSize;
  camera.OV2640_set_JPEG_size(captureSize);
}

int getCaptureSize() {
  //GETCAPTURESIZE Return the current capture size of the camera

  return captureSize;
}

const int* getCaptureSizes() {
  //GETCAPTURESIZE Return the array of available capture sizes
  //
  // The returned pointer is to static data which is overwritten with each call.
  
  return camoiseauDcAvailableCaptureSizes;
}

void savePicture(const char* str) {
  //SAVEPICTURE Take a picture and save it on the SD card

  byte buf[256];
  static int i = 0;
  uint8_t temp = 0, temp_last = 0;
  uint32_t length = 0;
  bool is_header = false;
  File outFile;
  //Flush the FIFO
  camera.flush_fifo();
  //Clear the capture done flag
  camera.clear_fifo_flag();
  //Start capture
  camera.start_capture();
  while (!camera.get_bit(ARDUCHIP_TRIG , CAP_DONE_MASK));
  length = camera.read_fifo_length();
  if (length >= MAX_FIFO_SIZE) //384K
  {
    return ;
  }
  if (length == 0 ) //0 kb
  {
    return ;
  }
  //Open the new file
  outFile = SD.open(str, O_WRITE | O_CREAT | O_TRUNC);
  if (!outFile) {
    return;
  }
  camera.CS_LOW();
  camera.set_fifo_burst();
  while ( length-- )
  {
    temp_last = temp;
    temp =  SPI.transfer(0x00);
    //Read JPEG data from FIFO
    if ( (temp == 0xD9) && (temp_last == 0xFF) ) //If find the end ,break while,
    {
      buf[i++] = temp;  //save the last  0XD9
      //Write the remain bytes in the buffer
      camera.CS_HIGH();
      outFile.write(buf, i);
      //Close the file
      outFile.close();
      is_header = false;
      i = 0;
    }
    if (is_header == true)
    {
      //Write image data to buffer if not full
      if (i < 256)
        buf[i++] = temp;
      else
      {
        //Write 256 bytes image data to file
        camera.CS_HIGH();
        outFile.write(buf, 256);
        i = 0;
        buf[i++] = temp;
        camera.CS_LOW();
        camera.set_fifo_burst();
      }
    }
    else if ((temp == 0xD8) & (temp_last == 0xFF))
    {
      is_header = true;
      buf[i++] = temp_last;
      buf[i++] = temp;
    }
  }
}

int findCaptureSize(int size) {
  //FINDCAPTURESIZE Seach a capture size in the available capture sizes
  //
  // "findCaptureSize()" lookups up for the value of "size" in "camoiseauDcAvailableCaptureSizes" 
  // and returns the index of its first occurence. If no occurence is found, "findCaptureSize()" 
  // returns -1.

  int n = (sizeof(camoiseauDcAvailableCaptureSizes)/sizeof(*(camoiseauDcAvailableCaptureSizes)));
  
  for(int i = 0; i < n; i++) {
    if(camoiseauDcAvailableCaptureSizes[i] == size) {
      return i;
    }
  }

  return -1;
}

void enterCameraLowPowerMode() {
  //ENTERCAMERALOWPOWERMODE Enter Camera's Low-Power Mode
  
  camera.set_bit(ARDUCHIP_GPIO,GPIO_PWDN_MASK);
}

void exitCameraLowPowerMode() {
  //EXITCAMERALOWPOWERMODE Exit Camera's Low-Power Mode
  
  camera.clear_bit(ARDUCHIP_GPIO,GPIO_PWDN_MASK);
}

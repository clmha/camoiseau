/*CAMOISEAU A bird camera
 *
 */

/*
 * TODO Store Capture Count in Non-volatile Memory
 */

#include <Arduino.h>
#include <RTClib.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>

#include "camoiseau_dc.h"
#include "camoiseau_modeSwitcher.h"
#include "camoiseau_pir.h"
#include "dcf.h"
#include "memorysaver.h"

#define CAMOISEAU_LED_DPIN 8
#define CAMOISEAU_SD_CS 10

RTC_DS1307 RTC;

camoiseauMode currentMode = monitor;

unsigned long iCapture = 0;

/*
 * Function Prototypes
 */
void getDateTime(uint16_t *date, uint16_t *time);

/*
 * Function Definitions
 */

void setup() {
  //SETUP Code to run once

  // Serial output
  Serial.begin(9600);

  // Signal the Start of Initialization
  pinMode(CAMOISEAU_LED_DPIN, OUTPUT);
  digitalWrite(CAMOISEAU_LED_DPIN, HIGH);

  /*
   *  I2C Bus
   */
  Serial.print("I2C CONF... ");
  Wire.begin();
  Serial.print("DONE.\n");

  /*
   *   SPI Bus
   */
  Serial.print("SPI CONF... ");
  pinMode(10, OUTPUT); // Make sure that AVR behaves as an SPI master
  SPI.begin();
  Serial.print("DONE.\n");

  /*
   * RTC
   */
  Serial.print("RTC CONF... ");
  if (!RTC.begin()) {
    // Something went wrong, do not do anything more.
    while (1); // We cannot continue without this feature.
  }
  if (!RTC.isrunning()) {
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  Serial.print("DONE.\n");

  /*
   *  SD Card
   */
  Serial.print("SD CONF... ");
  if (!SD.begin(CAMOISEAU_SD_CS)) {
    // Something went wrong, do not do anything more.
    while (1); // We cannot continue without this feature.
  }
  SdFile::dateTimeCallback(getDateTime);
  Serial.print("DONE.\n");

  /*
   * Camera
   */
  Serial.print("DCIM CONF... ");
  initializeCamera();
  Serial.print("DONE.\n");

  /*
   *  PIR Sensor
   */
  Serial.print("PIR CONF... ");
  initializePirSensor();
  Serial.print("DONE.\n");
}

void loop() {
  //LOOP Code to run repeatedly

  boolean motionIsDetected;
  const int burstSize = 7;
  int i;

  /*
   * Controller
   */
  switch(currentMode = getNextMode(currentMode, readPirSensor())) {
    case capture:
      // Switch to CAPTURE mode
  
      char dcfFilePath[DCF_FILEPATH_LENGTH];

      digitalWrite(CAMOISEAU_LED_DPIN, HIGH);
  
      // File name construction
      getDcfDirectoryPath(iCapture, dcfFilePath);
      SD.mkdir(dcfFilePath);
  
      // Capture
      for (int iBurst = burstSize; iBurst > 0; iBurst--) {
        getDcfFilePath(iCapture, ".jpg", dcfFilePath);
        savePicture(dcfFilePath);
        iCapture++;
      }
      break;
      
    case monitor:
      // Switch to MONITOR mode
      digitalWrite(CAMOISEAU_LED_DPIN, LOW);
      break;
    }

    /*
     * Update
     */
    // Nothing to do.
}

void getDateTime(uint16_t *date, uint16_t *time) {
  //GETDATETIME Return current date and time

  *date = FAT_DATE(RTC.now().year(), RTC.now().month(), RTC.now().day());
  *time = FAT_TIME(RTC.now().hour(), RTC.now().minute(), RTC.now().second());
}

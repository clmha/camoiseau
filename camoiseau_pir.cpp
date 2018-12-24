/*CAMOISEAU_PIR Camoiseau PIR Module
 * 
 */

 /*
  * $Id: camoiseau_pir.cpp 24 2017-11-19 21:03:40Z clement $
  */

#include "camoiseau_pir.h"

void initializePirSensor() {
  //INITIALIZEPIRSENSOR Prepare the passive infra-red sensor for use

  pinMode(CAMOISEAU_PIR_DPIN, INPUT);
  delay(30 * 1000); // Time for the component to calibrate (10-60 s according to the datasheet)
}

boolean readPirSensor() {
  //READPIRSENSOR Returns if motion is detected by the PIR (or not)

  return digitalRead(CAMOISEAU_PIR_DPIN) == HIGH;
}

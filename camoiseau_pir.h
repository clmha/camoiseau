/*CAMOISEAU_PIR Camoiseau PIR Module
 * 
 */

#ifndef _CAMOISEAU_PIR_
#define _CAMOISEAU_PIR_

#include <Arduino.h>

#define CAMOISEAU_PIR_DPIN 3

void initializePirSensor();
boolean readPirSensor();

#endif

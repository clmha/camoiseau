/*CAMOISEAU_PIR Camoiseau PIR Module
 * 
 */

/*
 * $Id: camoiseau_pir.h 24 2017-11-19 21:03:40Z clement $
 */

#ifndef _CAMOISEAU_PIR_
#define _CAMOISEAU_PIR_

#include <Arduino.h>

#define CAMOISEAU_PIR_DPIN 3

void initializePirSensor();
boolean readPirSensor();

#endif

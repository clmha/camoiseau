/*CAMOISEAU_MODESWITCHER Mode switching logic for Camoiseau
 * 
 */

/*
 * $Id: camoiseau_modeSwitcher.h 22 2017-11-12 02:39:24Z clement $
 */

#ifndef _CAMOISEAU_MODESWITCHER_
#define _CAMOISEAU_MODESWITCHER_

#include <Arduino.h>

enum camoiseauMode {monitor, capture};

camoiseauMode getNextMode(camoiseauMode currentMode, boolean motionDetected);

#endif

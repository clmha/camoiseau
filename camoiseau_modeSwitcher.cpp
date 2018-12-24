/*CAMOISEAU_MODESWITCHER Mode switching logic for Camoiseau
 * 
 */

/*
 * $Id: camoiseau_modeSwitcher.cpp 21 2017-10-30 01:54:47Z clement $
 */

#include "camoiseau_modeSwitcher.h"

camoiseauMode getNextMode(camoiseauMode currentMode, boolean motionDetected) {
  //GETNEXTMODE Returns the next mode Camoiseau must run

  switch(currentMode) {
    case monitor:
      if(motionDetected) {
        return capture;
      }
      return monitor;
      break;

    case capture:
      return monitor;
      break;

    default:
      return monitor;
  }
}

/*CAMOISEAU_MODESWITCHER Mode switching logic for Camoiseau
 * 
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

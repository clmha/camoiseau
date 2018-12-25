/*CAMOISEAU_MODESWITCHER Mode switching logic for Camoiseau
 * 
 */

#ifndef _CAMOISEAU_MODESWITCHER_
#define _CAMOISEAU_MODESWITCHER_

#include <Arduino.h>

enum camoiseauMode {monitor, capture};

camoiseauMode getNextMode(camoiseauMode currentMode, boolean motionDetected);

#endif

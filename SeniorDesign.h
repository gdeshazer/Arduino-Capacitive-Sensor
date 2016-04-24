// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - external variable definitions
// In the appropriate section

#ifndef _SeniorDesign_H_
#define _SeniorDesign_H_

#include "Arduino.h"
#include <Wire.h>

class IRsensor;
void dataRequest();
int getSensor();
void timeSet(int bytes);
void setup();
void loop();






#endif /* _SeniorDesign_H_ */

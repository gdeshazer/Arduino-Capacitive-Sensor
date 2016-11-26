/*
 * Created on: March 6, 2016
 * 	   Author: Grant DeShazer
 *
 *	See the class file for notes on implementation.
 */

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

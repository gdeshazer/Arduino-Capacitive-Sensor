/*
 * It is very likely that we can include both the flex sensor and
 * the capacitive sensors on a single board.  Especially if using
 * the mega
 *
 * The same can likely be said for the accelerometer, though we
 * will have to see if include the accelerometer with this board
 * will slow down the sampling rate too much.
 *
 */

#include "SeniorDesign.h"

#define sensor 0

void setup(){
	Serial.begin(9600);
}

void loop(){
	int reading = analogRead(sensor);
	float percent = (float) reading*100/1023.0;

	Serial.print("reading: ");
	Serial.print(reading);
	Serial.print("\tPercent: ");
	Serial.println(percent);

}

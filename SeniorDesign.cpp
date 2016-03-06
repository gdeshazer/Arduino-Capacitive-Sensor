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

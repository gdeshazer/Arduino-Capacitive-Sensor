/*
 * I2C Development
 * 		This represents the module that will eventually
 * 		turn into a class for the final implementation
 * 		This particular module is set up as an I2C slave
 * 		registered on ADDRESS 0x10;
 *
 * 	This also implements testing for the clock.  Note that
 * 	I2C is very particular about the number of total bytes
 * 	being transfered between devices.
 */

#include <Wire.h>
#include <stdlib.h>
#include "SeniorDesign.h"
#include "Timer.h"

#define sensor 4
#define LED 13

Timer ti;

void setup(){
	pinMode(LED, OUTPUT);

	Wire.begin(0x10);
	Serial.begin(9600);
	Wire.onRequest(dataRequest);
	Wire.onReceive(timeSet);

}


int getSensor() {
	//For now just generate random number

	return random();

//	int reading = analogRead(sensor);
//	float percent = (float) (reading) * 100 / 1023.0;
//	Serial.print("reading: ");
//	Serial.print(reading);
//	Serial.print("\tPercent: ");
//	Serial.println(percent);
}


void dataRequest(){
	String out = String(ti.getTime() + " " + getSensor());
	Wire.print(out);
}

void timeSet(int bytes){
	int index = 0;
	char data[20];
	while(!Wire.available()){
		char c = Wire.read();
		data[index++] = c;

	}

	ti.setOffset(atol(data));
}


void loop(){
	digitalWrite(LED, HIGH);
	delay(500);
	digitalWrite(LED, LOW);

}

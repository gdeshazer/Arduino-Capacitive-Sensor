/*
 * I2C Development
 *     This represents the module that will eventually
 *    turn into a class for the final implementation
 *    This particular module is set up as an I2C slave
 *    registered on ADDRESS 0x10;
 *
 *  This also implements testing for the clock.  Note that
 *  I2C is very particular about the number of total bytes
 *  being transfered between devices.
 */

#include <Arduino.h>
#include <Wire.h>
#include <stdlib.h>

const int SensorCount = 2;

#define sensor 0
#define flex 1
#define LED 13

class IRsensor{
public:
	IRsensor(){
		_reading = 0;
		_index = 0;
	}
	void readSensor(){
		_reading = (float) analogRead(sensor);

	}

	float getVal(){
		return _reading;
	}

private:
	float _reading;
	int _index;

}ir;


void dataRequest(){
	//char array -> byte array
	//with more sensor readings this array
	//should go up in size
	char a[sizeof(float)*SensorCount];
	float results[SensorCount];

//	currently only sending the IR value twice in a row
	results[0]= ir.getVal();
	results[1]= ir.getVal();

//	compress separate float readings into single byte array
	for(int i = 0; i < SensorCount; i++){
		int start = i * sizeof(float);
		memcpy(&(a[start]), &(results[i]), sizeof(float));
	}

//	flip bytes  [ Changing "endianess" of the bytes ]
	  for(int i = 0, j = (SensorCount*sizeof(float))-1; i < j; i++,j--){
	    char temp = a[i];
	    a[i] = a[j];
	    a[j] = temp;
	  }

	Wire.write(a,4*SensorCount);

}


void timeSet(int bytes){
	//does nothing
}



void setup(){
	pinMode(LED, OUTPUT);

	Wire.begin(0x10);

	Wire.onRequest(dataRequest);

	Serial.begin(115200);

}

void loop(){

	//Flex sensor reading
//	int avg = 0;
//	double sum = 0;
//	for(int i = 0; i < 100; i++){
//		sum += analogRead(flex);
//	}
//	avg = sum/ 100;
//
//	//read sensor values
//	Serial.println(avg);
	ir.readSensor();
}

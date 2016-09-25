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

const int SensorCount = 4;

#define irsensor 0
#define flex 1
#define LED 13

/*#####################################################################*/
/*############################# Classes ###############################*/
/*#####################################################################*/

class IRsensor{
public:
	IRsensor(){
		_reading = 0;
		_index = 0;
	}
	void readSensor(){
		_reading = (float) analogRead(irsensor);

	}

	float getVal(){
		return _reading;
	}

private:
	float _reading;
	int _index;

}ir;


class Inductive{
public:
	Inductive(){
		_pinNumber = 0;
		_reading = 0;
	}

	Inductive(int pin){
		_pinNumber = pin;
		_reading = 0;

		pinMode(_pinNumber, INPUT);
	}

	void readSensor(){
		_reading = (float) analogRead(_pinNumber);
	}

	float getVal(){
		return _reading;
	}

private:
	float _reading;
	int _pinNumber;
}id1(1), id2(2), id3(3);


/*#####################################################################*/
/*############################# Functions #############################*/
/*#####################################################################*/

void dataRequest(){
	//char array -> byte array
	//with more sensor readings this array
	//should go up in size
	char a[sizeof(float)*SensorCount];
	float results[SensorCount];

	//  currently only sending the IR value twice in a row
	results[0]= ir.getVal();
	results[1]= id1.getVal();
	results[2]= id2.getVal();
	results[3]= id3.getVal();

	//  compress separate float readings into single byte array
	for(int i = 0; i < SensorCount; i++){
		int start = i * sizeof(float);
		memcpy(&(a[start]), &(results[i]), sizeof(float));
	}

	//  char a[4];
	//
	//  float out = ir.getVal();
	//
	//  memcpy(&a, &out, sizeof(float));
//	//
//	Serial.print("Sending: ");
//	Serial.println(results[0]);
//	Serial.println(results[1]);

	//  Serial.print(a[0]);
	//  Serial.print("\t");
	//  Serial.print(a[1]);
	//  Serial.print("\t");
	//  Serial.print(a[2]);
	//  Serial.print("\t");
	//  Serial.print(a[3]);
	//  Serial.println("\n");

	//  flip bytes
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
	//  int avg = 0;
	//  double sum = 0;
	//  for(int i = 0; i < 100; i++){
	//    sum += analogRead(flex);
	//  }
	//  avg = sum/ 100;
	//  Serial.println(avg);
	ir.readSensor();
	id1.readSensor();
	id2.readSensor();
	id3.readSensor();
}

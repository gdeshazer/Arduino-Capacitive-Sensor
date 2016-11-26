/*
 * Created on: March 6, 2016
 * 	   Author: Grant DeShazer
 *
 * I2C Development
 *    This particular module is set up as an I2C slave
 *    registered on ADDRESS 0x10.
 *
 *    The Arduino is only being used only as an ADC converter
 *    for the Raspberry Pi.  Future implementations will not
 *    include an Arduino.
 *
 *	  The Arduino is constantly taking measurements with nothing
 *	  being saved localy.  When the Pi requests data, the Arduino
 *	  will send a byte array with whatever the most recent reading
 *	  is.  Because I2C requests opperate on the Interupt channel for
 *	  the Arduino's processor, when a request for data comes in,
 *	  there's no guarentee where the Arduino will be in terms of data
 *	  collection.  As a result it is difficult, at best, to quantify
 *	  how old a particular reading is.  It is assumened, then, that
 *	  the data readings were taken at exactly the same time and have
 *	  not aged significantly.
 *
 *	  Ideally the code is written to be expandable so that more
 *	  sensors could be implemented without the need to re-write the code.
 *	  All that would be necessary would be to change the SensorCount constant
 *	  and add more Inductive objects to account for additional sensors.
 *	  		Future implementations might need to use an object array whose
 *	  		size would corespond with the variable SensorCount.
 */

#include <Arduino.h>
#include <Wire.h>
#include <stdlib.h>

//This variable is defined in Arduino's standard library.
//It controls the baud rate expected on the I2C bus.  The
//maximum speed the Arduino is capable of handling without
//risking any sort of data loss of errors, is 400kbs
//(kilobytes per second).
#define TWI_FREQ 400000L

//Number of expected sensors to be read from
const int SensorCount = 4;

//Pin number definitions
#define irsensor 0
#define flex 1
#define LED 13

/*#####################################################################*/
/*############################# Classes ###############################*/
/*#####################################################################*/

/*IRsensor
 *	This class is responcible for reading the value of
 *	and IR Sensor connected to the Arduino.  It expects
 *	that the IR sensor has already been assigned a pin number
 *	either in the setup loop, or in the definitions above.
 */
class IRsensor{
public:
	IRsensor(){
		_reading = 0;
		_index = 0;
	}
	void readSensor(){
		_reading = analogRead(irsensor);

	}

	int getVal(){
		return _reading;
	}

private:
	int _reading;
	int _index;

}ir;

/*Inductive
 *	The Inductive class handles each inductive sensor connected to
 *	the Arduino.  It's default state is to assume the sensor has
 *	been connected to analog pin 0.  However, it also accepts a pin
 *	number as an input to its constructor.  It then will initialize
 *	that pin as an input.
 *
 *	Since only three sensors were available for testing, three objects
 *	are generated for use.
 *
 */
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
		_reading = analogRead(_pinNumber);
	}

	int getVal(){
		return _reading;
	}

private:
	int _reading;
	int _pinNumber;
}id1(1), id2(2), id3(3);


/*#####################################################################*/
/*############################# Functions #############################*/
/*#####################################################################*/

/*
 * Data request is bound to the interupt for the I2C bus.
 * This function is the only function responsible for handling any I2C
 * communication.
 *
 * Since the Arduino is setup as a Slave, it will not initiate
 * communcation with the Pi and will perform other tasks until it
 * recieves a start bit from the Pi.
 */
void dataRequest(){
	//C++ type char is equivalent to byte type.
	char a[sizeof(int)*SensorCount];
	int results[SensorCount];

	results[0]= ir.getVal();
	results[1]= id1.getVal();
	results[2]= id2.getVal();
	results[3]= id3.getVal();

	//Convert int array into char array via a memory copy.
	//Memory copy takes a reference to start int array and
	//copies each value in the addresses following that (in
	//accoradance with the size of an int) into the coresponding
	//memory slots associated with the char array.
	for(int i = 0; i < SensorCount; i++){
		int start = i * sizeof(int);
		memcpy(&(a[start]), &(results[i]), sizeof(int));
	}

	//Changing endianness of the array to match what Pi expects.
	for(int i = 0, j = (SensorCount*sizeof(int))-1; i < j; i++,j--){
		char temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}

	//Write array to I2C lines with an expected number of values.
	Wire.write(a,2*SensorCount);

}


void setup(){
	pinMode(LED, OUTPUT);

	//Initialize I2C bus as slave with Address 0x10.
	Wire.begin(0x10);

	//Binds interupt to I2C line and points to
	//to dataRequest function.
	Wire.onRequest(dataRequest);

	Serial.begin(115200);

}


//Constantly samples value on Analog lines while the Arduino
//is powered.
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

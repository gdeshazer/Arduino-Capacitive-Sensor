/*
 * Timer.cpp
 *	Created on: Mar 15, 2016
 *
 *  Timer class designed to handle time sync between the Beaglebone
 *  and the Arduino.
 *
 * Currently testing both this class and general data transfer
 */

#include "Timer.h"

Timer::Timer() {
	// TODO Auto-generated constructor stub
	_time = millis();
	_offset = 0;
}



unsigned long Timer::getTime(){
	return _time;

}

void Timer::setTime(){
	_time = millis() - _offset;

}

void Timer::setOffset(unsigned long off){
	_offset = off;
	this->setTime();
}

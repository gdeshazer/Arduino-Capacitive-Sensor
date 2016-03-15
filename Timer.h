/*
 * Timer.h
 *
 *  Created on: Mar 15, 2016
 *
 *  Refer to the CPP file
 */

#ifndef TIMER_H_
#define TIMER_H_

class Timer {
public:
	Timer();
	unsigned long getTime();
	void setOffset(unsigned long off);

private:
	unsigned long _time;
	unsigned long _offset;

	void setTime();

};

#endif /* TIMER_H_ */

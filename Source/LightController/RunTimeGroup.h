// RunTimeGroup.h

#ifndef RunTimeGroup_h
#define RunTimeGroup_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class RunTimeGroup
{
	const int sec = 1000;
public:
	void init(unsigned long timeInterval, void(*f)());
	void update(void(*f)());

private:
	unsigned long _timeInterval;
	unsigned long _prevMillis;
	void(*funct)();
};
#endif

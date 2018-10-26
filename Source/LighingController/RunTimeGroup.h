// RunTimeGroup.h

#ifndef _RunTimeGroup_h
#define _ RunTimeGroup_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class RunTimeGroup
{
public:
	void init(unsigned long timeInterval);
	static void update(void (*f)());

private:
	static unsigned long _timeInterval;
	static unsigned long _prevMillis;
};
#endif

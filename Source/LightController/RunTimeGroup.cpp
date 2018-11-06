#include "RunTimeGroup.h"
#include <Console.h>

void RunTimeGroup::init(unsigned long timeInterval, void(*foo)())
{
	_timeInterval = timeInterval * sec;
	funct= *foo;
}

void RunTimeGroup::update(void(*f)())
{
	unsigned long currentMillis = millis();
	if (currentMillis - _prevMillis >= _timeInterval) {
		_prevMillis = currentMillis;
		f();
	}
}

#include "RunTimeGroup.h"

void RunTimeGroup::init(unsigned long timeInterval)
{
	_timeInterval = timeInterval;
}

void RunTimeGroup::update(void(*f)())
{
	unsigned long currentMillis = millis();
	if (currentMillis - _prevMillis >= _timeInterval) {
		_prevMillis = currentMillis;
		(*f);
	}
}

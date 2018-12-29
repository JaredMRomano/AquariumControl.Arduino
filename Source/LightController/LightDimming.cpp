// 
// 
// 

#include "LightDimming.h"
#include "TimeService_Yun.h"
#include <Console.h>

void LightDimming::init(int pin, int interval, int maxPercent)
{
	_pin = pin;
	_interval = interval;
	_currentOutput = 0;
	_maxVal = (int)((long)((long)maxPercent * 4095) / 100);

	// Start the PWM board
	pwm.begin();
	pwm.setPWMFreq(1600);  // This is the maximum PWM frequency
}
void LightDimming::SetSunriseTime(unsigned int hr, unsigned int min, double duration)
{
	time_t t =  now();

	_sunrise.duration = duration;

	tmElements_t myElements = { 0, min, hr, weekday(t), day(t), month(t), year(t) - 1970 };
	_sunrise.startTime = makeTime(myElements);

	myElements = { 0, (int((double)min + 60.0 * ((double)hr + duration)) % 60), (min + int(60 * ((double)hr + duration))) / 60 , weekday(t), day(t), month(t), year(t) - 1970 };
	_sunrise.endTime = makeTime(myElements);
}

void LightDimming::SetSunsetTime(unsigned int hr, unsigned int min, double duration)
{
	time_t t = now();
	_sunset.duration = duration;	
	tmElements_t myElements = { 0, (int((double)min + 60.0 * ((double)hr - duration)) % 60), (min + int(60 * ((double)hr - duration)))/60, weekday(t), day(t), month(t), year(t) -1970};
	_sunset.startTime = makeTime(myElements);

	myElements = { 0, min, hr ,weekday(t), day(t), month(t), year(t) - 1970 };
	_sunset.endTime= makeTime(myElements);
}

void LightDimming::UpdateLight()
{
	time_t t = now();

	// Update sunrise time
	tmElements_t myElements = { 0, minute(_sunrise.startTime), hour(_sunrise.startTime), weekday(t), day(t), month(t), year(t) - 1970 };
	_sunrise.startTime= makeTime(myElements);

	// Update sunrise end time
	myElements = { 0, minute(_sunrise.endTime), hour(_sunrise.endTime) , weekday(t), day(t), month(t), year(t) - 1970 };
	_sunrise.endTime = makeTime(myElements);

	// Update sunset time
	myElements = { 0, minute(_sunset.endTime), hour(_sunset.endTime), weekday(t), day(t), month(t), year(t) - 1970 };
	_sunset.endTime = makeTime(myElements);
	// Updade sunset start time
	myElements = { 0, minute(_sunset.startTime), hour(_sunset.startTime), weekday(t), day(t), month(t), year(t) - 1970 };
	_sunset.startTime= makeTime(myElements);

	if (_sunrise.startTime <= t && t <= _sunrise.endTime) // Sunrise interval
	{
		long sunriseDurationInt = (long)(_sunrise.duration * 60 * 60);
		long max_Interval = _maxVal * (long)_interval;
		int riseDelta = (int)(max_Interval / sunriseDurationInt);

		_currentOutput = ((t - _sunrise.startTime) / _interval) * riseDelta;
		//_currentOutput = _currentOutput + riseDelta;
	}
	else if (_sunrise.endTime <= t && t <= _sunset.startTime) // Full Sun interval
	{
		_currentOutput = _maxVal;
	}

	else if (_sunset.startTime <= t && t <= _sunset.endTime) // Sunset interval
	{
		long sunsetDurationInt = (long)(_sunset.duration * 60 * 60);
		long max_Interval = _maxVal * (long)_interval;
		int setDelta = (int)(max_Interval / sunsetDurationInt);

		_currentOutput = _maxVal - (((t - _sunset.startTime) / _interval) * setDelta);
		//_currentOutput = _currentOutput - setDelta;
	}
	else
	{
		_currentOutput = 0;
	}

	if (_currentOutput > _maxVal) {
		_currentOutput = _maxVal;
	}
	if (_currentOutput < 0) {
		_currentOutput = 0;
	}

	pwm.setPWM(_pin, 0, _currentOutput);
}



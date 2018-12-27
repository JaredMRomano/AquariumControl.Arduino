// 
// 
// 

#include "LightDimming.h"
#include "TimeService_Yun.h"
#include <Console.h>

void LightDimming::init(int pin, int interval)
{
	_pin = pin;
	_interval = interval;
	_currentOutput = 0;
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

	// update sunrise time
	tmElements_t myElements = { 0, minute(_sunrise.startTime), hour(_sunrise.startTime), weekday(t), day(t), month(t), year(t) - 1970 };
	_sunrise.startTime= makeTime(myElements);

	//Update sunrise end time
	myElements = { 0, minute(_sunrise.endTime), hour(_sunrise.endTime) , weekday(t), day(t), month(t), year(t) - 1970 };
	_sunrise.endTime = makeTime(myElements);

	// Update sunset time
	myElements = { 0, minute(_sunset.endTime), hour(_sunset.endTime), weekday(t), day(t), month(t), year(t) - 1970 };
	_sunset.endTime = makeTime(myElements);
	// Updade sunset start time
	myElements = { 0, minute(_sunset.startTime), hour(_sunset.startTime), weekday(t), day(t), month(t), year(t) - 1970 };
	_sunset.startTime= makeTime(myElements);


	if (_sunrise.startTime <= t && t <= _sunrise.endTime) {
		pwm.setPWM(_pin, 0, _currentOutput);

		if (_currentOutput + ((4096 * 10) / (int)(_sunrise.duration * 60 * 60)) >= 4096) {
			_currentOutput = 4096;
		}
		else {
			_currentOutput = _currentOutput + ((4096 * 10) / (int)(_sunrise.duration * 60 * 60));
		}
	}
	else if (_sunset.startTime <= t && t <= _sunset.endTime) {
		pwm.setPWM(_pin, 0, _currentOutput);

		if (_currentOutput - ((4096 * 10) / (int)(_sunset.duration * 60 * 60)) <= 0) {
			_currentOutput = 0;
		}
		else {
			_currentOutput = _currentOutput - ((4096 * 10) / (int)(_sunset.duration * 60 * 60));
		}
	}
}



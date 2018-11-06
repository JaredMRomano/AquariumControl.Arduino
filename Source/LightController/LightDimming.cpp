// 
// 
// 

#include "LightDimming.h"
#include <Console.h>

void LightDimming::init(int pin, int interval)
{
	_pin = pin;
	_interval = interval;
	_sunrise.currentOutput = 0;
	_sunset.currentOutput = 4096;
	// Start the PWM board
	pwm.begin();
	pwm.setPWMFreq(1600);  // This is the maximum PWM frequency
}
void LightDimming::SetSunriseTime(unsigned int hr, unsigned int min, unsigned int duration)
{
	time_t t =  now();

	_sunrise.duration = duration;

	tmElements_t myElements = { 0, min, hr, day(t), month(t), year(t) };
	_sunrise.startTime = makeTime(myElements);

	myElements = { 0, min + duration, (hr) , day(t), month(t), year(t) };
	_sunrise.endTime = makeTime(myElements);
}

void LightDimming::SetSunsetTime(unsigned int hr, unsigned int min, unsigned int duration)
{
	time_t t = now();
	_sunset.duration = duration;

	tmElements_t myElements = { 0, min, hr, day(t), month(t), year(t) };
	_sunset.endTime = makeTime(myElements);

	myElements = { 0, min - duration, hr , day(t), month(t), year(t) };
	_sunset.startTime= makeTime(myElements);
}

void LightDimming::UpdateLight()
{
	time_t t = now();

	// update sunrise time
	tmElements_t myElements = { 0, minute(_sunrise.startTime), hour(_sunrise.startTime), day(t), month(t), year(t) };
	_sunrise.startTime= makeTime(myElements);

	//Update sunrise end time
	myElements = { 0, minute(_sunrise.endTime), hour(_sunrise.endTime) , day(t), month(t), year(t) };
	_sunrise.endTime = makeTime(myElements);

	// Update sunset time
	myElements = { 0, minute(_sunset.endTime), hour(_sunset.endTime), day(t), month(t), year(t) };
	_sunset.endTime = makeTime(myElements);
	// Updade sunset start time
	myElements = { 0, minute(_sunset.startTime), hour(_sunset.startTime), day(t), month(t), year(t) };
	_sunset.startTime= makeTime(myElements);


	if (_sunrise.currentOutput + ((4096 * 10) / (_sunrise.duration * 60)) >= 4096) {
		_sunrise.currentOutput = 4096;
	}
	else {
		_sunrise.currentOutput = _sunrise.currentOutput + ((4096 * 10) / (_sunrise.duration * 60 * 60));
	}	
	if (_sunrise.startTime <= t <= _sunrise.endTime) {
		pwm.setPWM(_pin, 0, _sunrise.currentOutput);
	}


	if (_sunset.currentOutput + ((4096 * 10) / (_sunset.duration * 60)) <= 0) {
		_sunset.currentOutput = 0;
	}
	else {
		_sunset.currentOutput = _sunset.currentOutput - ((4096 * 10) / (_sunset.duration * 60 * 60));
	}
	if (_sunset.startTime <= t <= _sunset.endTime) {
		pwm.setPWM(_pin, 0, _sunset.currentOutput);
	}
	Console.println();
	Console.println();
	Console.println(t);
	Console.println("updated");
	Console.println(_sunrise.currentOutput);	
	Console.println();
	Console.println(_sunset.currentOutput);
	
}



// LightDimming.h
#ifndef _LIGHTDIMMING_h
#define _LIGHTDIMMING_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <time.h>
#include <Adafruit_PWMServoDriver.h>
#include <EEPROM.h>

class LightDimming {
public:
	void UpdateLight();
	void init(int pin, int interval);
	void SetSunriseTime(unsigned int hr, unsigned int min, unsigned int duration);
	void SetSunsetTime(unsigned int hr, unsigned int min, unsigned int duration);
	int _pin;
	int _interval;

private: 
	struct sequence{
		time_t startTime;
		time_t endTime;
		unsigned int duration;
		unsigned int currentOutput;
	};
	sequence _sunrise;
	sequence _sunset;
	Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
};

#endif


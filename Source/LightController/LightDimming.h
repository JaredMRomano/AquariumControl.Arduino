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
	struct sequence {
		time_t startTime;
		time_t endTime;
		double duration;
	};
	void UpdateLight();
	void init(int pin, int interval);
	void SetSunriseTime(unsigned int hr, unsigned int min, double durationHr);
	void SetSunsetTime(unsigned int hr, unsigned int min, double durationHr);
	int _pin;
	int _interval;
	sequence Sunrise() const { return _sunrise; }
	sequence Sunset() const { return _sunset; }
	unsigned int CurrentOutput() const {return _currentOutput; }


private: 

	unsigned int _currentOutput;
	sequence _sunrise;
	sequence _sunset;
	Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
};

#endif


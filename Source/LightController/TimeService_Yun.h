// TimeService_Yun.h

#ifndef _TIMESERVICE_Yun_h
#define _TIMESERVICE_Yun_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class TimeService_Yun
{
 public:
	void init();
	static void syncTime();
	static void displayTime();

private:
	static void printDigits(int digits);
};
#endif


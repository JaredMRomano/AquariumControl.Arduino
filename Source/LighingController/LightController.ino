#include "TimeService_Yun.h"
#include <TimeLib.h>

const long secInterval = 1000;

TimeService_Yun timeService;

unsigned long twelveHr_prevMillis;

//Setup
void setup() 
{
  timeService.init();
  timeService.syncTime();
}
void loop() 
{
	twelveHrs();
}

void twelveHrs(){
	unsigned long currentMillis = millis();
	if (currentMillis - twelveHr_prevMillis >= 60 * 60 * secInterval)
	{
		twelveHr_prevMillis = currentMillis;

		// Sync Time
		timeService.syncTime();
		Console.println("Time Synced");
		timeService.displayTime();
	}
}


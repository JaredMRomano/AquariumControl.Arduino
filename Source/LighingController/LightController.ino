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

  // Timer0 used for millis() inturrupt to run "Compare A" function below
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
}

// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect)
{
	unsigned long currentMillis = millis();
	sweeper1.Update(currentMillis);
}
void loop() 
{
	twelveHrs();
}

void twelveHrs(){
	unsigned long currentMillis = millis();
	if (currentMillis - twelveHr_prevMillis >= 12 * 60 * 60 * secInterval)
	{
		twelveHr_prevMillis = currentMillis;

		// Sync Time
		timeService.syncTime();
		Console.println("Time Synced");
		timeService.displayTime();
	}
}


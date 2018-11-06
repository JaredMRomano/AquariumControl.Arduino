#include "LightDimming.h"
#include "TimeService_Yun.h"
#include "RunTimeGroup.h"
#include <TimeLib.h>
#include <Console.h>
#include <Wire.h>

TimeService_Yun timeService;
RunTimeGroup twelveHrsRG;
RunTimeGroup tenSecRG;
LightDimming blue1;
LightDimming blue2;
LightDimming blue3;
LightDimming white1;
LightDimming white2;
LightDimming white3;
LightDimming test;


//Setup
void setup() 
{
// Set Initial Time
  timeService.init();
  timeService.syncTime();

  // Initialize the Runtime groups
  twelveHrsRG.init(12 * 60 * 60, twelveHrs);
  tenSecRG.init(10, tenSec);

  // Initialize lights
  blue1.init(0, 10);
  blue2.init(1, 10);
  blue3.init(2, 10);
  white1.init(3, 10);
  white2.init(4, 10);
  white3.init(5, 10);

  test.init(0, 10);

  // Set Start Times
  blue1.SetSunriseTime(7, 00, 60 * 4);
  blue2.SetSunriseTime(7, 30, 60 * 3.5);
  blue3.SetSunriseTime(8, 00, 60 * 3);
  white1.SetSunriseTime(7, 00, 60 * 4);
  white2.SetSunriseTime(7, 30, 60 * 3.5);
  white3.SetSunriseTime(8, 00, 60 * 3);

  test.SetSunriseTime(21, 35, 10);

  blue1.SetSunsetTime(20, 00, 60 * 3);
  blue2.SetSunsetTime(19, 30, 60 * 3.5);
  blue3.SetSunsetTime(19, 00, 60 * 4);
  white1.SetSunsetTime(20, 00, 60 * 3);
  white2.SetSunsetTime(19, 30, 60 * 3.5);
  white3.SetSunsetTime(19, 00, 60 * 4);

  test.SetSunsetTime(22,00, 10);
}

void loop() 
{
	tenSecRG.update(tenSec);
	twelveHrsRG.update(twelveHrs);
}

void twelveHrs()
{
	//Sync Time
	timeService.syncTime();
	Console.println("Time Synced");
	timeService.displayTime();
}
void tenSec() 
{
	//blue1.UpdateLight();
	//blue2.UpdateLight();
	//blue3.UpdateLight();
	//white1.UpdateLight();
	//white2.UpdateLight();
	//white3.UpdateLight();
	test.UpdateLight();
}



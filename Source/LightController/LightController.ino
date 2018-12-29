#include "LightDimming.h"
#include "TimeService_Yun.h"
#include "RunTimeGroup.h"
#include <TimeLib.h>
#include <Console.h>
#include <Wire.h>

TimeService_Yun timeService;
RunTimeGroup oneHrsRG;
RunTimeGroup tenSecRG;
LightDimming blue1;
LightDimming blue2;
LightDimming blue3;
LightDimming white1;
LightDimming white2;

//Setup
void setup() 
{
// Set Initial Time
  timeService.init();
  timeService.syncTime();

  // Initialize the Runtime groups
  oneHrsRG.init(60 * 60, oneHrs);
  tenSecRG.init(10, tenSec);

  // Initialize lights
  blue1.init(0, 10, 100);
  blue2.init(1, 10, 100);
  blue3.init(2, 10, 100);
  white1.init(6, 10, 95);
  white2.init(7, 10, 90);

  // Set Start Times
  blue1.SetSunriseTime(7, 00, 4);
  blue2.SetSunriseTime(7, 30, 4);
  blue3.SetSunriseTime(8, 00, 4);
  white1.SetSunriseTime(8, 00, 4);
  white2.SetSunriseTime(8, 30, 4);

  blue1.SetSunsetTime(20, 00, 4);
  blue2.SetSunsetTime(20, 30, 4);
  blue3.SetSunsetTime(21, 00, 4);
  white1.SetSunsetTime(20, 00, 4);
  white2.SetSunsetTime(20, 30, 4);

  //blue1.SetSunriseTime(7, 13, .1);
  //blue2.SetSunriseTime(7, 24, .1);
  //blue3.SetSunriseTime(7, 38, .1);
  //white1.SetSunriseTime(7, 43, .1);
  //white2.SetSunriseTime(19, 14, 1);

  //blue1.SetSunsetTime(24, 00, .1);
  //blue2.SetSunsetTime(24, 30, .1);
  //blue3.SetSunsetTime(24, 00, .1);
  //white1.SetSunsetTime(24, 00, .1);
  //white2.SetSunsetTime(24, 30, .1);
}

void loop() 
{
	tenSecRG.update(tenSec);
	oneHrsRG.update(oneHrs);
}

void oneHrs()
{
	//Sync Time
	timeService.syncTime();
	Console.println("Time Synced");
	timeService.displayTime(now());
}
void tenSec() 
{
	blue1.UpdateLight();
	blue2.UpdateLight();
	blue3.UpdateLight();
	white1.UpdateLight();
	white2.UpdateLight();

	time_t t = now();

	Console.println();
	Console.println();
	Console.println("updated");
	Console.print("current time:");
	TimeService_Yun::displayTime(t);
	
	Console.println();
	Console.print("Sunrise start time:");
	TimeService_Yun::displayTime(blue1.Sunrise().startTime);
	Console.print("Sunrise end time:");
	TimeService_Yun::displayTime(blue1.Sunrise().endTime);

	Console.println();
	Console.print("Sunset start time:");
	TimeService_Yun::displayTime(white2.Sunset().startTime);
	Console.print("Sunset end time:");
	TimeService_Yun::displayTime(white2.Sunset().endTime);
	Console.println(); 



	Console.print("current blue1 output:");
	Console.println(blue1.CurrentOutput());
	Console.print("current blue2 output:");
	Console.println(blue2.CurrentOutput());
	Console.print("current blue3 output:");
	Console.println(blue3.CurrentOutput());
	Console.print("current white1 output:");
	Console.println(white1.CurrentOutput());
	Console.print("current white2 output:");
	Console.println(white2.CurrentOutput());
}



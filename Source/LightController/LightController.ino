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
  blue1.init(0, 10);
  blue2.init(1, 10);
  blue3.init(2, 10);
  white1.init(6, 10);
  white2.init(7, 10);

  // Set Start Times
  //blue1.SetSunriseTime(7, 00, 4);
  //blue2.SetSunriseTime(7, 30, 4);
  //blue3.SetSunriseTime(8, 00, 4);
  //white1.SetSunriseTime(7, 00, 4);
  //white2.SetSunriseTime(7, 30, 4);

  //blue1.SetSunsetTime(19, 00, 4);
  //blue2.SetSunsetTime(19, 30, 4);
  //blue3.SetSunsetTime(20, 00, 4);
  //white1.SetSunsetTime(19, 00, 4);
  //white2.SetSunsetTime(19, 30, 4);

  blue1.SetSunriseTime(20, 40, .5);
  blue2.SetSunriseTime(20, 50, .5);
  blue3.SetSunriseTime(21, 00, .5);
  white1.SetSunriseTime(20, 40, .5);
  white2.SetSunriseTime(20, 50, .5);

  blue1.SetSunsetTime(22, 00, .5);
  blue2.SetSunsetTime(22, 10, .5);
  blue3.SetSunsetTime(22, 20, .5);
  white1.SetSunsetTime(22, 00, .5);
  white2.SetSunsetTime(22, 10, .5);
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



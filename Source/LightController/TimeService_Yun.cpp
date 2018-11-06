/*
  TimeService_Yun.cpp - Library for Getting time from yun.
  Created by Jared Romano, November 2, 2018.
  Released into the public domain.
*/

#include "TimeService_Yun.h"
#include <Arduino.h>
#include <Time.h>
#include <Console.h> 
#include <Process.h>

// Var
Process date;
int hours, minutes, seconds, days, months, years;
int lastSecond = -1;

void TimeService_Yun::init()
{
	Bridge.begin();       //Start communication with draguino
	Console.begin();      //Start Draguino console
	while (!Console);
	
	//Check NTP Server
	if (!date.running()) {
		date.begin("date");
		date.addParameter("+%m,%d,%y,%A,%H,%M,%S");
		date.run();
	}
}
void TimeService_Yun::syncTime() {
	if (!date.running()) {
		date.begin("date");
		date.addParameter("+%H:%M:%S:%d:%m:%y");
		date.run();
	}
	//if there's a result from the date process, parse it:
	while (date.available() > 0) {
		// get the result of the date process (should be hh:mm:ss):
		String timeString = date.readString();
		// find the colons:
		int colon1 = timeString.indexOf(":");
		int colon2 = timeString.indexOf(':', colon1 + 1);
		int colon3 = timeString.indexOf(':', colon2 + 1);
		int colon4 = timeString.indexOf(':', colon3 + 1);
		int colon5 = timeString.lastIndexOf(":");

		// get the substrings for hour, minute second:
		String hourString = timeString.substring(0, colon1);
		String minString = timeString.substring(colon1 + 1, colon2);
		String secString = timeString.substring(colon2 + 1, colon3);
		String dayString = timeString.substring(colon3 + 1, colon4);
		String monthString = timeString.substring(colon4 + 1, colon5);
		String yearString = timeString.substring(colon5 + 1);

		// convert to ints,saving the previous second:
		hours = hourString.toInt();
		minutes = minString.toInt();
		seconds = secString.toInt();
		days = dayString.toInt();
		months = monthString.toInt();
		years = yearString.toInt();


		//Set system time
		setTime(hours, minutes, seconds, days, months, years);
	}
}

void TimeService_Yun::displayTime() {
	// digital clock display of the time
	Console.print(hour());
	printDigits(minute());
	printDigits(second());
	Console.print(' ');
	Console.print(day());
	Console.print(' ');
	Console.print(month());
	Console.print(' ');
	Console.print(year());
	Console.println();	
}

void TimeService_Yun::printDigits(int digits) {
	// utility function for digital clock display: prints preceding colon and leading 0
	Console.print(':');
	if (digits < 10)
		Console.print('0');
	Console.print(digits);
}


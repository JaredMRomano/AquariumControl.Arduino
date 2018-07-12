#include <Console.h> //use Console class for Arduino IDE debug over WiFi, similar to Serial class,
#include <Time.h>         //http://www.arduino.cc/playground/Code/Time 
#include <Wire.h>         //http://arduino.cc/en/Reference/Wire (included with Arduino IDE)
#include <Process.h>

//******Global Var*********
//Timing
unsigned long timeInterval = 60000;     // time pull rate          *minute = 60000
unsigned long confInterval = 60000;    // config settings pull rate 
unsigned long timePrevSec = 0;
unsigned long confPrevSec = 0;
//Config


//Setup
void setup() {
  Bridge.begin();       //Start communication with draguino
  Console.begin();      //Start Draguino console
  while (!Console);
  setCPUTime();
  getConfig();
  Console.println("Welcome to aquarium controller logging") ;}

//Loop
void loop() {
  
  // Var
  unsigned long currentSec = millis();
  
  //Sync Time
  if(currentSec - timePrevSec > timeInterval) {
    timePrevSec = currentSec;    
    setCPUTime();  
    digitalClockDisplay();
    Console.println(": time synced");
  }

  
  // Sync config settings
  if(currentSec - confPrevSec > confInterval) {
       confPrevSec = currentSec;
  getConfig();
  digitalClockDisplay();
  Console.println(": Config settings synced");
  }

}

//******Methods*******

//Get Config
void getConfig(){
  Process sqlConfig;
    sqlConfig.begin("lua");
    sqlConfig.addParameter("/root/linkmysql.lua");
    sqlConfig.addParameter("25");
    sqlConfig.run();

     while (sqlConfig.available() > 0) {
    // get the result of the sqlConfig process (should be hh:mm:ss):
    String state = sqlConfig.readString();
    //Console.print(state);
     }
     
  
}

//Set CPU Time
void setCPUTime(){
  Process date;
  int hours, minutes, seconds, days, months, years;
  
  if (!date.running())  {
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
    int colon2 = timeString.indexOf(':', colon1+1);
    int colon3 = timeString.indexOf(':', colon2+1);
    int colon4 = timeString.indexOf(':', colon3+1);
    int colon5 = timeString.lastIndexOf(":");

    // get the substrings for hour, minute second:
    hours = (timeString.substring(0, colon1)).toInt();
    minutes = (timeString.substring(colon1 + 1, colon2)).toInt();
    seconds = (timeString.substring(colon2 + 1, colon3)).toInt();
    days = (timeString.substring(colon3 + 1, colon4)).toInt();
    months = (timeString.substring(colon4 + 1, colon5)).toInt();
    years = (timeString.substring(colon5 + 1)).toInt();

    setTime(hours, minutes, seconds, days, months, years);  //set the system time to 23h31m30s on 13Feb2009
  }
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Console.print(':');
  if (digits < 10)
    Console.print('0');
  Console.print(digits);  
}
void digitalClockDisplay(void)
{
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
  //Console.println();
}

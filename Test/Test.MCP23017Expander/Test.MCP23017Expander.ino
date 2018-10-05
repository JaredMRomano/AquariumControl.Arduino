#include <DS3232RTC.h>
#include <Time.h>         //http://www.arduino.cc/playground/Code/Time  


#include <Wire.h>
#include <Adafruit_MCP23017.h>


Adafruit_MCP23017 mcp;
void setup() {
    mcp.begin(1);      // use default address 0
    mcp.pinMode(0, OUTPUT);
    mcp.pinMode(1, OUTPUT);



    Serial.begin(9600);
    while (!Serial) ; // wait until Arduino Serial Monitor opens
    setSyncProvider(RTC.get);   // the function to get the time from the RTC
    if(timeStatus() != timeSet) 
        Serial.println("Unable to sync with the RTC");
    else
        Serial.println("RTC has set the system time");    
}

void loop() {

    time_t t;
    if (timeStatus() == timeNotSet){
      setTime(04, 42, 00, 10, 01, 2016);
      Serial.print(hour(t));
    }
    if (t != 0) {
      RTC.set(t);   // set the RTC and the system time to the received value
      setTime(t);          
    }
  
      if (second()==0 || second()==10 || second()==20 || second()==30 || second()==40 || second()==50) {
           digitalClockDisplay();
          mcp.digitalWrite(0, LOW);
          mcp.digitalWrite(1, LOW);
        }
       else {

          mcp.digitalWrite(0, HIGH);
           mcp.digitalWrite(1, HIGH);
       }

}

void digitalClockDisplay(void)
{
    // digital clock display of the time
    Serial.print(hour());
    printDigits(minute());
    printDigits(second());
    Serial.print(' ');
    Serial.print(day());
    Serial.print(' ');
    Serial.print(month());
    Serial.print(' ');
    Serial.print(year()); 
    Serial.println(); 
}

void printDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    Serial.print(':');
    if(digits < 10)
        Serial.print('0');
    Serial.print(digits);
}

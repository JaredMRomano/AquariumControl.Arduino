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

    time_t t = RTC.now();
    if (timeStatus() == timeNotSet){
      setTime(04, 42, 00, 10, 01, 2016);
    }
    if (t != 0) {
      RTC.set(t);   // set the RTC and the system time to the received value
      setTime(t);          
    }
}
  


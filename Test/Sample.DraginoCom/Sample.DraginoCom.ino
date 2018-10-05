#include <Console.h> //use Console class for Arduino IDE debug over WiFi, similar to Serial class,
#include <DS3232RTC.h>
#include <Time.h>         //http://www.arduino.cc/playground/Code/Time 
#include <Wire.h>         //http://arduino.cc/en/Reference/Wire (included with Arduino IDE)

String name;
void setup() {
  Bridge.begin();
  Console.begin(); 
  while (!Console); 


   setSyncProvider(RTC.get);   // the function to get the time from the RTC
   if(timeStatus() != timeSet) 
       Console.println("Unable to sync with the RTC");
   else
       Console.println("RTC has set the system time");   

}
void loop() {
  if (Console.available() > 0) {
    char c = Console.read(); //read the next char received, data flow: IDE --> Yun Shield--> Arduino
    // look for the newline character, this is the last character in the string
    if (c == '\n') {
      //print text with the name received
      Console.print("Hi ");
      Console.print(name);
      Console.println("! Nice to meet you!");
      Console.println();
      // Ask again for name and clear the old name
      Console.println("Hi, what's your name?");
      name = ""; // clear the name string
    }
    else { // if the buffer is empty Cosole.read() returns -1
      name += c; // append the read char from Console to the name string
    }
  }
}

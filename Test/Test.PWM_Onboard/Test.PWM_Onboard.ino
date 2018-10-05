#include <PWM.h>

int32_t frequency = 0;
static unsigned long light_samplingInterval = 100;

void setup(){  
   // Bridge.begin();       //Start communication with draguino
  Serial.begin(9600);      //Start Draguino console
  InitTimersSafe();
  bool sucess = SetPinFrequencySafe(9, frequency);
  if (sucess) {
    //do something here
  }
}
void loop(){
  static unsigned long light_samplingTime = millis();
  if (millis() - light_samplingTime > light_samplingInterval) {
    if (frequency < 10000) {
      frequency = frequency + 10;
      bool sucess = SetPinFrequencySafe(9, frequency);
      pwmWrite(9, 100);
      Serial.println(frequency);
      light_samplingTime=millis();
    }
   
  }
}


//bool sucess = SetPinFrequencySafe(9, 5000);
//pwmWrite(9,100);




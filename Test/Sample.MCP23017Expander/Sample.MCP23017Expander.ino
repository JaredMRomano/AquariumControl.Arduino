/*
 Example 41.1 - Microchip MCP23017 with Arduino
 http://tronixstuff.com/tutorials > chapter 41
 John Boxall | CC by-sa-nc
*/
// pins 15~17 to GND, I2C bus address is 0x20
#include "Wire.h"
void setup()
{
 Wire.begin(); // wake up I2C bus
// set I/O pins to outputs
 Wire.beginTransmission(0x20);
 Wire.write(0x00); // IODIRA register
 Wire.write(0x00); // set all of port A to outputs
 Wire.endTransmission();
Wire.beginTransmission(0x20);
 Wire.write(0x01); // IODIRB register
 Wire.write(0x00); // set all of port B to outputs
 Wire.endTransmission();
}
void loop()
{
Wire.beginTransmission(0x20);
Wire.write(0x12); // address port A
Wire.write(204); // value to send
Wire.endTransmission();
Wire.beginTransmission(0x20);
Wire.write(0x13); // address port B 
Wire.write(136);     // value to send
Wire.endTransmission();
}

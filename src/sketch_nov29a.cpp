
#include <Arduino.h>
#include "mgs_modbus.h"

MGS_MODBUS Modbus;

void setup() {
  // put your setup code here, to run once:
  // open the serial port at 9600 bps:
  Serial.begin(9600);

  Modbus.initiate();
  
  //Serial.println("Setup");
}

void loop() {
  _delay_ms(1000);
  //Serial.println("Loop neu");
  //Run the modbus module.
  Modbus.run();
}
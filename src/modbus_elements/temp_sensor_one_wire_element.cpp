
#include "../project_defines.h"

#ifdef TEMP_SENSOR_ONE_WIRE_ELEMENT_ENABLED

#ifndef TEMP_SENSOR_ONE_WIRE_ELEMENT_CPP
#define TEMP_SENSOR_ONE_WIRE_ELEMENT_CPP

#include "temp_sensor_one_wire_element.h"


TEMP_SENSOR_ONE_WIRE_ELEMENT::TEMP_SENSOR_ONE_WIRE_ELEMENT()
{
  
}


void TEMP_SENSOR_ONE_WIRE_ELEMENT::initiate(OneWire *pTempSensor)
{
    this->pTempSensor = pTempSensor;
}




float32 TEMP_SENSOR_ONE_WIRE_ELEMENT::get_temp(void){
  //returns the temperature from one DS18S20 in DEG Celsius
  byte data[12];
  byte addr[8];

  if ( !pTempSensor->search(addr)) {
      //no more sensors on chain, reset search
      pTempSensor->reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  pTempSensor->reset();
  pTempSensor->select(addr);
  pTempSensor->write(0x44,1); // start conversion, with parasite power on at the end

  byte present = pTempSensor->reset();
  pTempSensor->select(addr);    
  pTempSensor->write(0xBE); // Read Scratchpad

  
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = pTempSensor->read();
  }
  
  pTempSensor->reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;
  
  return TemperatureSum;
}


#endif /* TEMP_SENSOR_ONE_WIRE_CPP */

#endif //TEMP_SENSOR_ONE_WIRE_ELEMENT_ENABLED

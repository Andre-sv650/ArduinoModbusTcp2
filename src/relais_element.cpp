

#include "relais_element.h"

#include "Arduino.h"
#include "modbus_debug.h"


RELAIS_ELEMENT::RELAIS_ELEMENT(void)
{

}


void RELAIS_ELEMENT::initiate(Uint32 StartPin, Uint8 PinCount)
{
  Uint8 i;

  this->StartPin = StartPin;
  this->SizeInBits = PinCount;
  
  for(i = 0u; i < PinCount; i++){
    pinMode(StartPin + i, OUTPUT);          // sets the digital pin 13 as output
  }
}

//Set the data of the relais.
void RELAIS_ELEMENT::set_data(Uint8 BitNumber, Uint8 Data)
{
  digitalWrite((uint8_t)StartPin + BitNumber, (uint8_t)Data);

  MODBUS_DEBUG::print_relais_set(StartPin, BitNumber, Data);
}


Uint8 RELAIS_ELEMENT::get_data()
{
  Uint8 result = 0u;
  
  for(int i = 0u; i < this->SizeInBits; i++){
    result |= (digitalRead((uint8_t)(this->StartPin + i)) << i);
  }

  MODBUS_DEBUG::print_relais_get(StartPin, SizeInBits, result);
  
  return result;
}



#include "relais_element.h"

#include "Arduino.h"


RELAIS_ELEMENT::RELAIS_ELEMENT(void)
{

}


void RELAIS_ELEMENT::initiate(Uint32 StartPin, Uint8 PinCount)
{
  this->StartPin = StartPin;
  this->SizeInBits = PinCount;
}

//Set the data of the relais.
void RELAIS_ELEMENT::set_data(Uint8 BitNumber, Uint8 Data)
{
  digitalWrite((uint8_t)BitNumber, (uint8_t)Data);
}


Uint8 RELAIS_ELEMENT::get_data()
{
  Uint8 result = 0u;
  
  for(int i = 0u; i < this->SizeInBits; i++){
    result |= (digitalRead((uint8_t)(this->StartPin + i)) << i);
  }
  
  return result;
}

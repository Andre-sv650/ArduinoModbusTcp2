

#include "relais_element.h"

#include "Arduino.h"
#include "modbus_debug.h"


RELAIS_ELEMENT::RELAIS_ELEMENT(void)
{

}


void RELAIS_ELEMENT::initiate(Uint32 StartPin, Uint8 PinCount, bool8 Reversed)
{
  Uint8 i;

  this->StartPin = StartPin;
  this->SizeInBits = PinCount;
  this->Reversed = Reversed;
  this->OnlyOneRelaisAtTime = FALSE;
  
  for(i = 0u; i < PinCount; i++){
    
    digitalWrite((uint8_t)StartPin + i, (uint8_t)Reversed);
    
    pinMode(StartPin + i, OUTPUT);          // sets the digital pin 13 as output
  }
}

void RELAIS_ELEMENT::initiate(Uint32 StartPin, Uint8 PinCount, bool8 Reversed, bool8 OnlyOneRelaisAtTime)
{
  this->initiate(StartPin, PinCount, Reversed);

  this->OnlyOneRelaisAtTime = OnlyOneRelaisAtTime;
}

//Set the data of the relais.
void RELAIS_ELEMENT::set_data(Uint8 BitNumber, Uint8 Data)
{
  //Check if only one element at one time is set.
  if(OnlyOneRelaisAtTime == TRUE)
  {
    //Set all elements to off.
    for(int i = 0u; i < SizeInBits; i++){
      digitalWrite((uint8_t)StartPin + i, (uint8_t)(0) ^ Reversed);
    }
  }
  
  //Set the new value.
  digitalWrite((uint8_t)StartPin + BitNumber, (uint8_t)(Data & 0x1) ^ Reversed);

  MODBUS_DEBUG::print_relais_set(StartPin, BitNumber, Data);
}


Uint8 RELAIS_ELEMENT::get_data()
{
  Uint8 result = 0u;
  
  for(int i = 0u; i < this->SizeInBits; i++){
    result |= ((digitalRead((uint8_t)(this->StartPin + i)) ^ Reversed) << i) ;
  }

  MODBUS_DEBUG::print_relais_get(StartPin, SizeInBits, result);
  
  return result;
}

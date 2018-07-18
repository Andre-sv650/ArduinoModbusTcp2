

#ifndef MODBUS_ELEMENT_ARRAY_CPP
#define MODBUS_ELEMENT_ARRAY_CPP

#include "modbus_element_array.h"


MODBUS_ELEMENT_ARRAY::MODBUS_ELEMENT_ARRAY()
{
  RegisteredElementsCount = 0u;
}


void MODBUS_ELEMENT_ARRAY::add_element(MODBUS_ELEMENT_BASE *pNewElement)
{
  //Set the element.
  pRegisteredElements[RegisteredElementsCount] = pNewElement;
  
  RegisteredElementsCount++;
}


/*
 * Get the element from the requested address.
 */
MODBUS_ELEMENT_BASE* MODBUS_ELEMENT_ARRAY::get_element_from_address(Uint8 ByteAddress)
{
  Uint8 i;
  MODBUS_ELEMENT_BASE *pElement = 0;
  
  for(i = 0u; (i < RegisteredElementsCount) && (pElement == 0); i++){
    Uint8 startAddress = this->pRegisteredElements[i]->StartAddress;
    Uint8 endAddress = startAddress + this->pRegisteredElements[i]->SizeInBits / 8u;
    
    if(ByteAddress > startAddress && ByteAddress < endAddress){
      //Return the element.
      pElement = pRegisteredElements[i];
    }
  }
  
  return pElement;
}



#endif /* MODBUS_ELEMENT_ARRAY_CPP_ */

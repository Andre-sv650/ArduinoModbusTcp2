

#ifndef MODBUS_ELEMENT_ARRAY_CPP
#define MODBUS_ELEMENT_ARRAY_CPP

#include "modbus_element_array.h"

MODBUS_ELEMENT_ARRAY::MODBUS_ELEMENT_ARRAY()
{
  RegisteredElementsCount = 0u;
}

void MODBUS_ELEMENT_ARRAY::background_routine(void)
{
  //Call all elements in this.
  for (Uint8 i = 0u; i < RegisteredElementsCount; i++)
  {
    //Call the routine.
    this->pRegisteredElements[i]->background_routine();
  }
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
MODBUS_ELEMENT_BASE *MODBUS_ELEMENT_ARRAY::get_element_from_address(Uint8 ByteAddress)
{
  Uint8 i;
  MODBUS_ELEMENT_BASE *pElement = 0;

  for (i = 0u; i < RegisteredElementsCount; i++)
  {
    //Check if this is the element.
    for (int x = 0u; x < this->pRegisteredElements[i]->NumberOfElements; x++)
    {
      if (this->pRegisteredElements[i]->StartAddress[x] == ByteAddress)
      {
        return pRegisteredElements[i];
      }
    }
  }

  return pElement;
}

#endif /* MODBUS_ELEMENT_ARRAY_CPP_ */

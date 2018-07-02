


#include "modbus_element_base.h"

/*
 * Constructor
 */
MODBUS_ELEMENT_BASE::MODBUS_ELEMENT_BASE()
{
  SizeInBits = 0u;
  
  StartAddress = 0u;
}


bool8 MODBUS_ELEMENT_BASE::get_data(Uint8 BitNumber)
{
  //Get the data.
  Uint8 data = this->get_data();
  
  Uint8 mask = 1 << BitNumber;

  Uint8 result = data & mask;

  result = result >> BitNumber;

  return result;
}

void MODBUS_ELEMENT_BASE::set_data(Uint8 Data)
{
  //Nothing to set.
}

void MODBUS_ELEMENT_BASE::set_data(Uint8 BitNumber, Uint8 Data)
{
  //Nothing to set.
}

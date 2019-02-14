

#include "modbus_element_base.h"

/*
 * Constructor
 */
MODBUS_ELEMENT_BASE::MODBUS_ELEMENT_BASE()
{
  for (int i = 0; i < MODBUS_ELEMENT_BASE_ARRAY_SIZE; i++)
  {
    SizeInBits[i] = 0u;

    StartAddress[i] = 0u;

    NumberOfElements = 0u;
  }
}

void MODBUS_ELEMENT_BASE::initiate(Uint8 Address, Uint8 SizeInBitsOfElement)
{
  StartAddress[0u] = Address;

  SizeInBits[0u] = SizeInBitsOfElement;

  NumberOfElements = 1u;
}

/*
*
*/
void MODBUS_ELEMENT_BASE::initiate(Uint8 AddressArray[], Uint8 NumberOfAdresses)
{
  int i;

  for (i = 0u; i < NumberOfAdresses; i++)
  {
    StartAddress[i] = AddressArray[i];
  }

  NumberOfElements = NumberOfAdresses;
}

void MODBUS_ELEMENT_BASE::background_routine(void)
{
  //Background routine in case that the module dont need it.
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

void MODBUS_ELEMENT_BASE::get_data(Uint8 Address, Uint8 pDataArray[], Uint8 NumberOfBytes)
{
  //Fallback if no overwrite function was found.
  Uint8 data = get_data();

  //Set the data to the data array.
  pDataArray[0] = data;
}

void MODBUS_ELEMENT_BASE::set_data(Uint8 Data)
{
  //Nothing to set.
}

void MODBUS_ELEMENT_BASE::set_data(Uint8 BitNumber, Uint8 Data)
{
  //Nothing to set.
}

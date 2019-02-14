
#include "../project_defines.h"
#ifdef RELAIS_ELEMENT_ENABLED

#include "relais_element.h"

#include "Arduino.h"
#include "../debug/modbus_debug.h"

/*
 * Constructor
 */
RELAIS_ELEMENT::RELAIS_ELEMENT(void)
{
  Pin = 0u;
  OnlyOneRelaisAtTime = FALSE;
  Reversed = FALSE;
}

/*
 * Call the initiate method once for the relays element.
 */
void RELAIS_ELEMENT::initiate(Uint8 Address, Uint32 StartPin, Uint8 PinCount, bool8 Reversed)
{
  this->initiate(Address, StartPin, PinCount, Reversed, FALSE);
}

void RELAIS_ELEMENT::initiate(Uint8 Address, Uint32 StartPin, Uint8 PinCount, bool8 Reversed, bool8 OnlyOneRelaisAtTime)
{
  Uint8 i;

  this->Pin = StartPin;
  this->Reversed = Reversed;
  this->OnlyOneRelaisAtTime = FALSE;

  for (i = 0u; i < PinCount; i++)
  {
    //First set the digital output, to avoid that the output is set to on if the pin mode is set first.
    digitalWrite((uint8_t)Pin + i, (uint8_t)Reversed);

    pinMode(Pin + i, OUTPUT); // sets the digital pin as output
  }

  this->OnlyOneRelaisAtTime = OnlyOneRelaisAtTime;

  MODBUS_ELEMENT_BASE::initiate(Address, PinCount);
}

//Set the data
void RELAIS_ELEMENT::set_data(Uint8 Data)
{
  //Check if only one element at one time is set.
  if (OnlyOneRelaisAtTime == TRUE)
  {
    //Set all elements to off.
    for (int i = 0u; i < SizeInBits[0]; i++)
    {
      digitalWrite((uint8_t)Pin + i, (uint8_t)(0) ^ Reversed);
    }
  }

  for (Uint8 i = 0u; i < SizeInBits[0]; i++)
  {
    Uint8 mask = 0x1 << i;

    if ((Data & mask) == mask)
    {
      //Set the new value.
      digitalWrite((uint8_t)Pin + i, (uint8_t)(0x1) ^ Reversed);

      //Abort the write.
      i = SizeInBits[0];
    }
  }

  MODBUS_DEBUG::print_relais_set(Pin, 255u, Data);
}

//Set the data of the relays.
void RELAIS_ELEMENT::set_data(Uint8 BitNumber, Uint8 Data)
{
  //Check if only one element at one time is set.
  if (OnlyOneRelaisAtTime == TRUE)
  {
    //Set all elements to off.
    for (int i = 0u; i < SizeInBits[0]; i++)
    {
      digitalWrite((uint8_t)Pin + i, (uint8_t)(0) ^ Reversed);
    }
  }

  //Set the new value.
  digitalWrite((uint8_t)Pin + BitNumber, (uint8_t)(Data & 0x1) ^ Reversed);

  MODBUS_DEBUG::print_relais_set(Pin, BitNumber, Data);
}

Uint8 RELAIS_ELEMENT::get_data()
{
  Uint8 result = 0u;

  for (int i = 0u; i < SizeInBits[0]; i++)
  {
    result |= ((digitalRead((uint8_t)(this->Pin + i)) ^ Reversed) << i);
  }

  MODBUS_DEBUG::print_relais_get(Pin, SizeInBits[0], result);

  return result;
}

#endif //RELAIS_ELEMENT_ENABLED

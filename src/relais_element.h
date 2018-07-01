
#ifndef RELAIS_ELEMENT_H
#define RELAIS_ELEMENT_H

#include "cpu_datatypes.h"
#include "modbus_element_base.h"
/*
 * One relais element of 8 bit
 */
class RELAIS_ELEMENT : public MODBUS_ELEMENT_BASE
{
private:
  Uint32 StartPin;

  bool8 Reversed;

  bool8 OnlyOneRelaisAtTime;

public:
     RELAIS_ELEMENT(void);
     
     void initiate(Uint32 StartPin, Uint8 PinCount, bool8 Reversed);

     void RELAIS_ELEMENT::initiate(Uint32 StartPin, Uint8 PinCount, bool8 Reversed, bool8 OnlyOneRelaisAtTime);

     Uint8 get_data(void);
     
     void set_data(Uint8 BitNumber, Uint8 Data);
};

#endif //Relais element
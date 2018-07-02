
#include "project_defines.h"
#ifdef RELAIS_ELEMENT_ENABLED


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
  bool8 Reversed;

  bool8 OnlyOneRelaisAtTime;

public:
     RELAIS_ELEMENT(void);
     
     void initiate(Uint32 StartPin, Uint8 PinCount, bool8 Reversed);

     void initiate(Uint32 StartPin, Uint8 PinCount, bool8 Reversed, bool8 OnlyOneRelaisAtTime);

     Uint8 get_data(void);
     
     void set_data(Uint8 Data);

     void set_data(Uint8 BitNumber, Uint8 Data);
};

#endif //Relais element

#endif //RELAIS_ELEMENT_ENABLED

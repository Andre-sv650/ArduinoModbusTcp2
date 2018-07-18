

#include "../project_defines.h"
#ifdef LIGHT_INTENSITY_ELEMENT_ENABLED

#ifndef LIGHT_INTENSITY_ELEMENT_H
#define LIGHT_INTENSITY_ELEMENT_H

#include "../cpu_datatypes.h"
#include "modbus_element_base.h"


/*
 * One presence detector element.
 */
class LIGHT_INTENSITY_ELEMENT : public MODBUS_ELEMENT_BASE
{
private:
  

public:
  LIGHT_INTENSITY_ELEMENT();
  
  void initiate(Uint32 Pin);
  
  Uint8 get_data(Uint8 ByteNumber);
};


#endif /* LIGHT_INTENSITY_ELEMENT_H */

#endif //LIGHT_INTENSITY_ELEMENT_ENABLED

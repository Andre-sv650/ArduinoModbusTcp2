

#include "project_defines.h"
#ifdef PRESENCE_DETECTOR_ELEMENT_ENABLED

#ifndef PRESENCE_DETECTOR_ELEMENT_H
#define PRESENCE_DETECTOR_ELEMENT_H

#include "cpu_datatypes.h"
#include "modbus_element_base.h"


/*
 * One presence detector element.
 */
class PRESENCE_DETECTOR_ELEMENT : public MODBUS_ELEMENT_BASE
{
private:
  

public:
  PRESENCE_DETECTOR_ELEMENT();
  
  void initiate(Uint8 Address, Uint32 Pin);
  
  void initiate(Uint8 Address, Uint32 StartPin, Uint8 NumberOfDetectors);
  
  Uint8 get_data(void);
};


#endif /* PRESENCE_DETECTOR_ELEMENT_H */

#endif //PRESENCE_DETECTOR_ELEMENT_ENABLED

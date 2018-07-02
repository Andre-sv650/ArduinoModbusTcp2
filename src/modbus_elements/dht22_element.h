

#include "project_defines.h"
#ifdef DHT22_ELEMENT_ENABLED

#ifndef DHT22_ELEMENT_H
#define DHT22_ELEMENT_H

#include "cpu_datatypes.h"
#include "modbus_element_base.h"
/*
 * One dht element
 */
class DHT22_ELEMENT : public MODBUS_ELEMENT_BASE
{
private:
  Uint32 StartPin;
  
  void trigger_data(void);

public:
     DHT22_ELEMENT(void);
     
     void initiate(Uint32 StartPin);

     Uint8 get_data(void);
};

#endif //DHT22_ELEMENT_H

#endif //DHT22_ELEMENT_ENABLED

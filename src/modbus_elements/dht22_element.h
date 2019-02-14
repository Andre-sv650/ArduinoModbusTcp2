

#include "project_defines.h"
#ifdef DHT22_ELEMENT_ENABLED

#ifndef DHT22_ELEMENT_H
#define DHT22_ELEMENT_H

#include "cpu_datatypes.h"
#include "modbus_element_base.h"
#include "external_libraries/DHT.h"
/*
 * One dht element
 */
class DHT22_ELEMENT : public MODBUS_ELEMENT_BASE
{
private:
  DHT MyDht22;

  float32 Temperature;

  float32 Humidity;

  Uint8 Dht22NotAvailableDebugMessageSet;

public:
  DHT22_ELEMENT(void);

  void initiate(Uint8 StartAddress, Uint32 StartPin);

  void background_routine(void);

  Uint8 get_data(void);

  void get_data(Uint8 Address, Uint8 pDataArray[], Uint8 NumberOfBytes);
};

#endif //DHT22_ELEMENT_H

#endif //DHT22_ELEMENT_ENABLED

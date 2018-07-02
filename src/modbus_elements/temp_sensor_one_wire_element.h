

#include "project_defines.h"
#ifdef TEMP_SENSOR_ONE_WIRE_ELEMENT_ENABLED

#ifndef TEMP_SENSOR_ONE_WIRE_H
#define TEMP_SENSOR_ONE_WIRE_H

#include "cpu_datatypes.h"
#include "modbus_element_base.h"
#include "external_libraries/DS18B20.h"


/*
 * One temp sensor one wire element
 */
class TEMP_SENSOR_ONE_WIRE_ELEMENT : public MODBUS_ELEMENT_BASE
{
private:
  OneWire OnewireSensor;
  DS18B20 Sensors;
  

public:
  TEMP_SENSOR_ONE_WIRE_ELEMENT();
  
  void initiate(Uint32 Pin);
  
  Uint8 get_data(void);
};


#endif /* TEMP_SENSOR_ONE_WIRE_H */

#endif //TEMP_SENSOR_ONE_WIRE_ELEMENT_ENABLED

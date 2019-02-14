

#include "project_defines.h"
#ifdef TEMP_SENSOR_ONE_WIRE_ELEMENT_ENABLED

#ifndef TEMP_SENSOR_ONE_WIRE_ELEMENT_H
#define TEMP_SENSOR_ONE_WIRE_ELEMENT_H


#include "cpu_datatypes.h"
#include "modbus_element_base.h"
#include "external_libraries/OneWire.h"


/*
 * One temp sensor one wire element
 */
class TEMP_SENSOR_ONE_WIRE_ELEMENT : public MODBUS_ELEMENT_BASE
{
private:
  OneWire *pTempSensor;

  float32 Temperature;

public:
  TEMP_SENSOR_ONE_WIRE_ELEMENT(void);

  void background_routine(void);
  
  void initiate(Uint8 Pin, Uint8 StartAddress, OneWire *pTempSensor);
  
  Uint8 get_data(void);

  void get_data(Uint8 Address, Uint8 pDataArray[], Uint8 NumberOfBytes);
};


#endif /* TEMP_SENSOR_ONE_WIRE_ELEMENT_H */

#endif //TEMP_SENSOR_ONE_WIRE_ELEMENT_ENABLED

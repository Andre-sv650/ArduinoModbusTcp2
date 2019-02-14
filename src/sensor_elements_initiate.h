

#include "cpu_datatypes.h"
#include "modbus_elements/modbus_data_handler.h"
#include "modbus_elements/relais_element.h"
#include "modbus_elements/dht22_element.h"
#include "modbus_elements/temp_sensor_one_wire_element.h"
//#include "modbus_elements/light_intensity_element.h"


#ifndef SENSOR_ELEMENTS_INITIATE_H
#define SENSOR_ELEMENTS_INITIATE_H

class SENSOR_ELEMENTS_INITIATE
{
//Fields
public:
  MODBUS_DATA_HANDLER DataHandler;
  
  SENSOR_ELEMENTS_INITIATE();
  
  // Intiate all sensors
  void initiate();  
  
private: 
  
  //Relais outputs.
  RELAIS_ELEMENT Relais1FromPin8;

  DHT22_ELEMENT Dth22Sensor;

  TEMP_SENSOR_ONE_WIRE_ELEMENT TempSensor;
};


#endif //SENSOR_ELEMENTS_INITIATE_H


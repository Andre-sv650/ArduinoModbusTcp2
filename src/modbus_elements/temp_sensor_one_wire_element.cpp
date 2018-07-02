
#include "project_defines.h"

#ifdef TEMP_SENSOR_ONE_WIRE_ELEMENT_ENABLED

#ifndef TEMP_SENSOR_ONE_WIRE_CPP
#define TEMP_SENSOR_ONE_WIRE_CPP


#include "temp_sensor_one_wire_element.h"


TEMP_SENSOR_ONE_WIRE_ELEMENT::TEMP_SENSOR_ONE_WIRE_ELEMENT()
{
  
}


void TEMP_SENSOR_ONE_WIRE_ELEMENT::initiate(Uint32 Pin)
{
    this.OnewireSensor = new Onewire(Pin);

    this.Sensors(&OnewireSensor);

  
}


#endif /* TEMP_SENSOR_ONE_WIRE_CPP */

#endif //TEMP_SENSOR_ONE_WIRE_ELEMENT_ENABLED

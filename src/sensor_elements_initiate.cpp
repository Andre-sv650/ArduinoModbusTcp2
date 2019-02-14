
#include "sensor_elements_initiate.h"

/*
* Default constructor.
*/
SENSOR_ELEMENTS_INITIATE::SENSOR_ELEMENTS_INITIATE()
{
}

void SENSOR_ELEMENTS_INITIATE::initiate(void)
{
  DataHandler = MODBUS_DATA_HANDLER();

  //A one wire temp sensor on arduino pin 3
  //OneWire tempSensorOneWire(3);

  //Initialize the relays outputs.
  Relais1FromPin8.initiate(0, 8, 4, TRUE, TRUE);
  DataHandler.register_coil_read_write(&Relais1FromPin8);

  //Initialize the DHT22 sensor, address 100.
  Dth22Sensor.initiate(100, 2);
  DataHandler.register_coil_read_write(&Dth22Sensor);

  //Initialize the temperatur sensor, address 110.
  //TempSensor.initiate(3, 110, &tempSensorOneWire);
  //DataHandler.register_coil_read_write(&TempSensor);
}

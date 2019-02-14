
#ifndef MODBUS_DEBUG_H
#define MODBUS_DEBUG_H

#include "cpu_datatypes.h"

class MODBUS_DEBUG
{
public:
  static void print_command_read_register_get_data(Uint8 Address, Uint8 Size, Uint8 Data);

  static void print_read_coil(Uint8 Address, Uint8 BitNumber, Uint8 Data);
  
  static void print_command_write_coil(Uint8 BitNumber, Uint8 Size, Uint8 Data);
  
  static void print_command_write_register(Uint8 Address, Uint8 Size, Uint8 Data);
  
  static void print_command_error(char Error[], Uint8 Address);

  //Section Relais
  static void print_relais_set(Uint8 Startpin, Uint8 Bitnumber, Uint8 Value);

  static void print_relais_get(Uint8 Startpin, Uint8 PinSize, Uint8 Value);

  //Section DHT22
  static void print_dht22_not_available(Uint8 StartPin);

  static void print_dht22_now_available(Uint8 StartPin);

  static void print_dht22_temperature(Uint8 StartPin, float32 Temperature);

  static void print_dht22_humidity(Uint8 StartPin, float32 Humidity);

  //Section temp sensor one wire.
  static void print_one_wire_temperature(Uint8 StartPin, int16 Temperature);

  //Section light intensity element
  static void print_light_intensity_element(Uint8 StartPin, float32 LigthIntensity);

  //Section presence detector
  static void print_presence_detector_element(Uint8 StartPin, Uint8 Data);
};


#endif //MODBUS_DEBUG_H

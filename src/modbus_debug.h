
#ifndef MODBUS_DEBUG_H
#define MODBUS_DEBUG_H

#include "cpu_datatypes.h"


class MODBUS_DEBUG
{
public:
  static void print_command_read_data(Uint8 Address, Uint8 Size, Uint8 Data);
  
  static void print_command_write_data(Uint8 Address, Uint8 Size, Uint8 Data);
  
  static void print_command_error(Uint8 Description[], Uint8 Address);

  static void print_relais_set(Uint8 Startpin, Uint8 Bitnumber, Uint8 Value);

  static void print_relais_get(Uint8 Startpin, Uint8 Bitnumber, Uint8 Value);
};


#endif //MODBUS_DEBUG_H
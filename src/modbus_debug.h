
#ifndef MODBUS_DEBUG_H
#define MODBUS_DEBUG_H

#include "cpu_datatypes.h"


class MODBUS_DEBUG
{
public:
  static void print_command_read_data(Uint8 Address, Uint8 Size, Uint8 Data);
  
  static void print_command_write_data(Uint8 Address, Uint8 Size, Uint8 Data);
  
  static void print_command_error(Uint8 Description[], Uint8 Address);
};


#endif //MODBUS_DEBUG_H
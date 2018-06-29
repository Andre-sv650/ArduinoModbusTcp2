#include "cpu_datatypes.h"
#include "modbus_debug.h"
#include <Arduino.h>


void MODBUS_DEBUG::print_command_read_data(Uint8 Address, Uint8 Size, Uint8 Data)
{
  #ifdef DEBUG
	Serial.println("Read coil started, address of the parameter: "); Serial.print(Address); 
  Serial.println("Size: "); Serial.print(Size);
  Serial.println("Data: "); Serial.print(Data);
	
	#endif
}


void MODBUS_DEBUG::print_command_write_data(Uint8 Address, Uint8 Size, Uint8 Data)
{
  #ifdef DEBUG
	Serial.println("Write coil started, address of the parameter: "); Serial.print(Address); 
  Serial.println("Size: "); Serial.print(Size);
  Serial.println("Data: "); Serial.print(Data);
	
	#endif
  
}

void MODBUS_DEBUG::print_command_error(Uint8 Description[], Uint8 Address)
{
  #ifdef DEBUG
	Serial.print("Description"); Serial.print(Address);
	#endif
}


// void ModbusDebug::check_for_commands(int InByte, MgsModbus Mb)
// {
//   if (InByte == '0') {                                          // print MbData
//     for (int i=0;i<12;i++) {

//     }
//   }
// }


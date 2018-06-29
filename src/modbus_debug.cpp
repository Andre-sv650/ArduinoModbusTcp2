#include "cpu_datatypes.h"
#include "modbus_debug.h"
#include <Arduino.h>




void MODBUS_DEBUG::print_command_read_data(Uint8 Address, Uint8 Size, Uint8 Data)
{
  #ifdef DEBUG
	Serial.print("Read coil started, address of the parameter: "); Serial.print(Address); 
  Serial.print("Size: "); Serial.println(Size);
  Serial.print("Data: "); Serial.println(Data);
	
	#endif
}


void MODBUS_DEBUG::print_command_write_data(Uint8 Address, Uint8 Size, Uint8 Data)
{
  #ifdef DEBUG
	Serial.print("Write coil started, address of the parameter: "); Serial.println(Address); 
  Serial.print("Size: "); Serial.println(Size);
  Serial.print("Data: "); Serial.println(Data);
	
	#endif
  
}

void MODBUS_DEBUG::print_command_error(Uint8 Description[], Uint8 Address)
{
  #ifdef DEBUG
	Serial.print("Description"); Serial.print(Address);
	#endif
}

void MODBUS_DEBUG::print_relais_set(Uint8 Startpin, Uint8 Bitnumber, Uint8 Value)
{
  #ifdef DEBUG
	Serial.print("Relais set with start pin: "); Serial.print(Startpin); 
  Serial.print(" Bitnumber: "); Serial.print(Bitnumber);
  Serial.print(" and value: "); Serial.print(Value);
  Serial.println(" ");
	#endif
}

void MODBUS_DEBUG::print_relais_get(Uint8 Startpin, Uint8 Bitnumber, Uint8 Value)
{
  #ifdef DEBUG
	Serial.print("Relais get with start pin: "); Serial.print(Startpin); 
  Serial.print(" Bitnumber: "); Serial.print(Bitnumber);
  Serial.print(" and value: "); Serial.print(Value);
  Serial.println(" ");
	#endif
}


// void ModbusDebug::check_for_commands(int InByte, MgsModbus Mb)
// {
//   if (InByte == '0') {                                          // print MbData
//     for (int i=0;i<12;i++) {

//     }
//   }
// }


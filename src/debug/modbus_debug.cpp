

#include "modbus_debug_defines.h"

#include "modbus_debug.h"
#include <Arduino.h>

void MODBUS_DEBUG::print_command_read_register_get_data(Uint8 Address, Uint8 Size, Uint8 Data)
{
  #ifdef MODBUS_DEBUG_READ_REGISTER_GET_DATA
	Serial.print("Read data started, address of the parameter: ") + Serial.print(Address) +
  Serial.print(". Size: ") + Serial.print(Size);
  Serial.print(". Data: ") + Serial.println(Data);
	
	#endif
}


void MODBUS_DEBUG::print_read_coil(Uint8 Address, Uint8 BitNumber, Uint8 Data)
{
#ifdef MODBUS_DEBUG_READ_COIL
  Serial.print("Read coil done with start address: ") + Serial.print(Address) + 
      Serial.print(". And bit number: ") + Serial.print(BitNumber) +
      Serial.print(". The result was: ") + Serial.println(Data);
#endif
}


void MODBUS_DEBUG::print_command_write_coil(Uint8 BitNumber, Uint8 Size, Uint8 Data)
{
  #ifdef MODBUS_DEBUG_WRITE_COIL
  Serial.print("Write coil started, bit number of the parameter: ") + Serial.print(BitNumber) +
  Serial.print("Size: ") + Serial.print(Size) +
  Serial.print("Data: ") Serial.println(Data);
  
  #endif
  
}



void MODBUS_DEBUG::print_command_write_register(Uint8 Address, Uint8 Size, Uint8 Data)
{
  #ifdef MODBUS_DEBUG_WRITE_REGISTER
	Serial.print("Write coil started, address of the parameter: ") + Serial.print(Address) +
  Serial.print("Size: ") + Serial.print(Size) +
  Serial.print("Data: ") + Serial.println(Data);
	
	#endif
  
}



void MODBUS_DEBUG::print_command_error(char Error[], Uint8 Address)
{
  #ifdef DEBUG
	Serial.print(Error) + Serial.print(". Address is: ") + Serial.print(Address) + Serial.println(" ");
	#endif
}



void MODBUS_DEBUG::print_relais_set(Uint8 Startpin, Uint8 Bitnumber, Uint8 Value)
{
  #ifdef MODBUS_DEBUG_RELAIS_SET
	Serial.print("Relais set with start pin: ") + Serial.print(Startpin) +
  Serial.print(" Bitnumber: ") + Serial.print(Bitnumber) +
  Serial.print(" and value: ") + Serial.println(Value);
	#endif
}

void MODBUS_DEBUG::print_relais_get(Uint8 Startpin, Uint8 PinSize, Uint8 Value)
{
  #ifdef MODBUS_DEBUG_RELAIS_GET
  Serial.print("Relais get with start pin: ") + Serial.print(Startpin) + 
  Serial.print(" Size: ") + Serial.print(PinSize) +
  Serial.print(" and value returned: ") + Serial.println(Value);
	#endif
}


// void ModbusDebug::check_for_commands(int InByte, MgsModbus Mb)
// {
//   if (InByte == '0') {                                          // print MbData
//     for (int i=0;i<12;i++) {

//     }
//   }
// }


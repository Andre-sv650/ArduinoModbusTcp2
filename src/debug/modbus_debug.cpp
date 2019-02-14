#include "modbus_debug_defines.h"
#include "modbus_debug.h"
#include <Arduino.h>

void MODBUS_DEBUG::print_command_read_register_get_data(Uint8 Address, Uint8 Size, Uint8 Data)
{
  #ifdef MODBUS_DEBUG_READ_REGISTER_GET_DATA
	Serial.print("|-Read data started, address of the parameter: ");
  Serial.print(Address);
  Serial.print(". Size: ") + Serial.print(Size);
  Serial.print(". Data: ") + Serial.println(Data);
	
	#endif
}


void MODBUS_DEBUG::print_read_coil(Uint8 Address, Uint8 BitNumber, Uint8 Data)
{
#ifdef MODBUS_DEBUG_READ_COIL
  Serial.print("|-Read coil done with start address: ") + Serial.print(Address) + 
      Serial.print(". And bit number: ") + Serial.print(BitNumber) +
      Serial.print(". The result was: ") + Serial.println(Data);
#endif
}


void MODBUS_DEBUG::print_command_write_coil(Uint8 BitNumber, Uint8 Size, Uint8 Data)
{
  #ifdef MODBUS_DEBUG_WRITE_COIL
  Serial.print("|-Write coil started, bit number of the parameter: ") + Serial.print(BitNumber) +
  Serial.print(". Size: ") + Serial.print(Size) +
  Serial.print(". Data: ") + Serial.println(Data);
  
  #endif
}



void MODBUS_DEBUG::print_command_write_register(Uint8 Address, Uint8 Size, Uint8 Data)
{
  #ifdef MODBUS_DEBUG_WRITE_REGISTER
	Serial.print("|-Write register started, address of the parameter: ") +
  Serial.print(Address) + Serial.print(". Data size: ") + Serial.print(Size) +
  Serial.print(". Data: ") + Serial.println(Data);
	
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
	Serial.print("|-Relais set with start pin: ") + Serial.print(Startpin) +
  Serial.print(" Bitnumber: ") + Serial.print(Bitnumber) +
  Serial.print(" and value: ") + Serial.println(Value);
	#endif
}

void MODBUS_DEBUG::print_relais_get(Uint8 Startpin, Uint8 PinSize, Uint8 Value)
{
  #ifdef MODBUS_DEBUG_RELAIS_GET
  Serial.print("|-Relais get with start pin: ") + Serial.print(Startpin) + 
  Serial.print(" Size: ") + Serial.print(PinSize) +
  Serial.print(" and value returned: ") + Serial.println(Value);
	#endif
}


void MODBUS_DEBUG::print_dht22_not_available(Uint8 StartPin)
{
  #ifdef MODBUS_DEBUG_DHT22
  Serial.println("DHT 22 element not found on pin: ") + Serial.println((int)StartPin);
	#endif
}

void MODBUS_DEBUG::print_dht22_now_available(Uint8 StartPin)
{
  #ifdef MODBUS_DEBUG_DHT22
  Serial.print("DHT 22 element found on pin: ") + Serial.println((int)StartPin);
	#endif
}

void MODBUS_DEBUG::print_dht22_temperature(Uint8 StartPin, float32 Temperature)
{
  #ifdef MODBUS_DEBUG_DHT22
  Serial.print("|-Temperature requested on pin: ") + Serial.print(StartPin) + Serial.print(". The Temperature was: ") + Serial.println(Temperature);
	#endif
}

void MODBUS_DEBUG::print_dht22_humidity(Uint8 StartPin, float32 Humidity)
{
  #ifdef MODBUS_DEBUG_DHT22
  Serial.print("|-Humidity requested on pin: ") + Serial.print(StartPin) + Serial.print(". The Humidity was: ") + Serial.println(Humidity);
	#endif
}


void MODBUS_DEBUG::print_one_wire_temperature(Uint8 StartPin, int16 Temperature)
{
  #ifdef MODBUS_DEBUG_TEMP_SENSOR_ONE_WIRE
  Serial.print("|-Temperature requested on one wire pin: ") + Serial.print(StartPin) + Serial.print(". The temperature was: ") + Serial.println(Temperature);
	#endif
}


void MODBUS_DEBUG::print_light_intensity_element(Uint8 StartPin, float32 LigthIntensity)
{
  #ifdef MODBUS_DEBUG_LIGHT_INTENSITY_ELEMENT
  Serial.print("|-Ligth intensity requested on pin: ") + Serial.print(StartPin) + Serial.print(". The ligth intensity was: ") + Serial.println(LigthIntensity);
	#endif
}


void MODBUS_DEBUG::print_presence_detector_element(Uint8 StartPin, Uint8 Data)
{
  #ifdef MODBUS_DEBUG_PRESENCE_DETECTOR_ELEMENT
  Serial.print("|-Presence detector requested on pin: ") + Serial.print(StartPin) + Serial.print(". The state was: ") + Serial.println(Data);
	#endif
}




#include "modbus_elements/modbus_data_handler.h"
#include "../debug/modbus_debug.h"
#include "Arduino.h"


void MODBUS_DATA_HANDLER::background_routine(void)
{
  ReadWriteElements.background_routine();
}

/* 
 * Register one element
 */
void MODBUS_DATA_HANDLER::register_coil_read_write(MODBUS_ELEMENT_BASE *pElement)
{
    ReadWriteElements.add_element(pElement);
}

/*
 * Iterate through all Coils and set the data.
 */
bool8 MODBUS_DATA_HANDLER::write_coil(Uint8 BitNumber, bool8 Value)
{
  bool8 result = false;
  
  //Get the element that is requested.
  MODBUS_ELEMENT_BASE *pElement = ReadWriteElements.get_element_from_address(BitNumber / 8u);
  
  if(pElement != NULL_PTR){
    //Set the data.
    pElement->set_data(BitNumber % 8, Value);
   
    result = TRUE;
    
    MODBUS_DEBUG::print_command_write_coil(BitNumber, 1, Value);
  }
  else{
    char errorMessage[] = "Write coil aborted, element not found";
    MODBUS_DEBUG::print_command_error(errorMessage, BitNumber);
  }
  
  return result;
}


int MODBUS_DATA_HANDLER::read_coil(Uint8 EthernetRequest[])
{
  int startAddress = get_word(EthernetRequest[8],EthernetRequest[9]);
  //The requested data length by the master.
  int coilDataLength = get_word(EthernetRequest[10],EthernetRequest[11]);
  int byteDataLength = coilDataLength / 8;
  Uint8 bitNumber = startAddress % 8u;
  Uint8 address = startAddress / 8u;
  Uint8 data = 0u;
  
  //If the data length is not matching.
  if((byteDataLength * 8) < coilDataLength){
     byteDataLength++;      
  }
  coilDataLength = byteDataLength * 8;

  //The number of bytes that are transmitted to the master.
  EthernetRequest[5] = byteDataLength + 3; //Number of bytes after this one.
  EthernetRequest[8] = byteDataLength;     //Number of bytes after this one (or number of bytes of data).
  
  //Get the data.  //Get the element that is requested.
  MODBUS_ELEMENT_BASE *pElement = ReadWriteElements.get_element_from_address(address);
  
  if(pElement != NULL_PTR){
    data = pElement->get_data(bitNumber);
    
    //Get the data.
    EthernetRequest[9] = data;
  }

  MODBUS_DEBUG::print_read_coil(address, bitNumber, data);
  
  if(byteDataLength == 0u){
    char errorMessage[] = "Read coil aborted, byte length 0";
    MODBUS_DEBUG::print_command_error(errorMessage, (Uint8)startAddress);
  }
  
  return byteDataLength + 9;
}

//Read the register.
int MODBUS_DATA_HANDLER::read_register(Uint8 EthernetRequest[])
{
  int startAddress = word(EthernetRequest[8], EthernetRequest[9]);
  int WordDataLength = word(EthernetRequest[10],EthernetRequest[11]);
  int ByteDataLength = WordDataLength * 2;
  
  EthernetRequest[5] = ByteDataLength + 3; //Number of bytes after this one.
  EthernetRequest[8] = ByteDataLength;     //Number of bytes after this one (or number of bytes of data).
  
  //Get the data from the registered components.
  this->read_register_get_data(EthernetRequest, startAddress, ByteDataLength);

  return ByteDataLength + 9;
}


void MODBUS_DATA_HANDLER::write_register(Uint8 EthernetRequest[])
{
   int startAddress = word(EthernetRequest[8], EthernetRequest[9]);
   int incomingData = word(EthernetRequest[10], EthernetRequest[11]);
   
   Serial.print("Write register started with address: ") +
   Serial.print(startAddress) + Serial.print(". And data: ") + Serial.println(incomingData);

  //Get the element that is requested.
  MODBUS_ELEMENT_BASE *pElement = ReadWriteElements.get_element_from_address(startAddress);
  
  if(pElement != NULL_PTR){
    //Get the data.
    pElement->set_data(incomingData);
    
    MODBUS_DEBUG::print_command_write_register(startAddress, 16u, incomingData);
  }
  else{
    int8 errorMessage[] = "Write aborted, element not found.";
    MODBUS_DEBUG::print_command_error(errorMessage, (int8)startAddress);
  } 
}


void MODBUS_DATA_HANDLER::read_register_get_data(Uint8 EthernetRequest[], int StartAddress, int ByteDataLength)
{
  EthernetRequest[9] = 0; // To get all remaining not written bits zero
  
  //Get the element that is requested.
  MODBUS_ELEMENT_BASE *pElement = ReadWriteElements.get_element_from_address(StartAddress);
  
  if(pElement != NULL_PTR){
    //Get the data
    MODBUS_DEBUG::print_command_read_register_get_data(StartAddress, ByteDataLength, EthernetRequest[9]);
    pElement->get_data(StartAddress, &EthernetRequest[9], ByteDataLength);
  }
  else{
    int8 errorMessage[] = "Read aborted, element not found. Remaining data is set to 0";
    MODBUS_DEBUG::print_command_error(errorMessage, (int8)StartAddress);

    //Set everything to 0.
    EthernetRequest[9] = 0u;
  }
}

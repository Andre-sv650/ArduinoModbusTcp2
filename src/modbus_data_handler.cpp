

#include "modbus_data_handler.h"
#include "modbus_debug.h"
#include "Arduino.h"

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
    
    MODBUS_DEBUG::print_command_write_data(BitNumber, 1, Value);
  }
  else{
    Uint8 errorMessage[] = "Write coil aborted, element not found";
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
  
  //If the data length is not matching.
  if(byteDataLength * 8 < coilDataLength){
     byteDataLength++;      
  }
  coilDataLength = byteDataLength * 8;

  //The number of bytes that are transmitted to the master.
  EthernetRequest[5] = byteDataLength + 3; //Number of bytes after this one.
  EthernetRequest[8] = byteDataLength;     //Number of bytes after this one (or number of bytes of data).
  
  for(int i = 0; i < byteDataLength ; i++)
  {
    EthernetRequest[9 + i] = 0; // To get all remaining not written bits zero
    
    //Get the element that is requested.
    MODBUS_ELEMENT_BASE *pElement = ReadWriteElements.get_element_from_address(startAddress + (i * 8));
    
    if(pElement != NULL_PTR){
      //Get the data.
      EthernetRequest[9 + i] = pElement->get_data();
      
      MODBUS_DEBUG::print_command_read_data(startAddress, coilDataLength, pElement->get_data());
    }
    else{
      Uint8 errorMessage[] = "Read coil aborted, element not found";
      MODBUS_DEBUG::print_command_error(errorMessage, (Uint8)startAddress);
    }
  }
  
  if(byteDataLength == 0u){
    Uint8 errorMessage[] = "Read coil aborted, bye length 0";
    MODBUS_DEBUG::print_command_error(errorMessage, (Uint8)startAddress);
  }
  
  return byteDataLength + 9;
}


int MODBUS_DATA_HANDLER::read_register(Uint8 EthernetRequest[])
{
  // int Start = word(EthernetRequest[8], EthernetRequest[9]);
  // int WordDataLength = word(EthernetRequest[10],EthernetRequest[11]);
  // int ByteDataLength = WordDataLength * 2;
  // MbsByteArray[5] = ByteDataLength + 3; //Number of bytes after this one.
  // MbsByteArray[8] = ByteDataLength;     //Number of bytes after this one (or number of bytes of data).
  // for(int i = 0; i < WordDataLength; i++)
  // {
  //   MbsByteArray[ 9 + i * 2] = highByte(EthernetRequest[Start + i]);
  //   MbsByteArray[10 + i * 2] =  lowByte(EthernetRequest[Start + i]);
  // }
  // MessageLength = ByteDataLength + 9;
  // client.write(MbsByteArray, MessageLength);
  // MbsFC = MB_FC_NONE;
}

#include "mgs_modbus.h"
#include "modbus_data_handler.h"

// For Arduino 1.0
EthernetServer MbServer(MB_PORT);
EthernetClient MbmClient;

// #define DEBUG
MGS_MODBUS::MGS_MODBUS()
{
  //Initialize the relais outputs.
  Relais1FromPin30.initiate(30, 8, TRUE, TRUE);
  
  MbsFC = MB_FC_NONE;
  
  DataHandler = MODBUS_DATA_HANDLER();
  
  DataHandler.register_coil_read_write(&Relais1FromPin30);
}

//****************** Receive data for ModBusSlave ****************
void MGS_MODBUS::run()
{  
  int Start, MessageLength;
  
  //****************** Read from socket ****************
  EthernetClient client = MbServer.available();
  
  if(client.available())
  {
    delay(10);
    int i = 0;
    while(client.available())
    {
      MbsByteArray[i] = client.read();
      i++;
    }
    
    //Read the incoming data.
    MbsFC = set_fc(MbsByteArray[7]);  //Byte 7 of request is FC
  }
  
  
  //****************** Read Coils (1 & 2) **********************
  if(MbsFC == MB_FC_READ_COILS || MbsFC == MB_FC_READ_DISCRETE_INPUT) {
    //Serial.println("Read coil started");
    //Read the data.
    int messageLength = this->DataHandler.read_coil(MbsByteArray);
    
    client.write(MbsByteArray, messageLength);
    MbsFC = MB_FC_NONE;

    //Serial.println("Read coil end");
  }
  
  
  //****************** Read Registers (3 & 4) ******************
 if(MbsFC == MB_FC_READ_REGISTERS || MbsFC == MB_FC_READ_INPUT_REGISTER) {
   //Serial.println("Read register started");
    //Read the data.
    int messageLength = this->DataHandler.read_register(MbsByteArray);

    client.write(MbsByteArray, messageLength);
    MbsFC = MB_FC_NONE;
 }
 
  //****************** Write Coil (5) **********************
  if(MbsFC == MB_FC_WRITE_COIL) {
    Serial.println("Write coil started");
    bool8 newValue;
    
    if(get_word(MbsByteArray[10], MbsByteArray[11]) == 0xFF00){
      newValue = TRUE;
    }
    else if((get_word(MbsByteArray[10],MbsByteArray[11])) == 0x0000){
      newValue = false;
    }
    
    Start =  get_word(MbsByteArray[8],MbsByteArray[9]);
    
    //Set the coil.
    DataHandler.write_coil(Start, newValue);
    
    MbsByteArray[5] = 2; //Number of bytes after this one.
    MessageLength = 8;
    client.write(MbsByteArray, MessageLength);
    MbsFC = MB_FC_NONE;
  } 
  //****************** Write Register (6) ******************
 if(MbsFC == MB_FC_WRITE_REGISTER) {
   DataHandler.write_register(MbsByteArray);
   MbsByteArray[5] = 6; //Number of bytes after this one.
   MessageLength = 12;
   client.write(MbsByteArray, MessageLength);
   MbsFC = MB_FC_NONE;
 }
  //****************** Write Multiple Coils (15) **********************
//  if(MbsFC == MB_FC_WRITE_MULTIPLE_COILS) {
//    Serial.println("Write mutliple coil started");
//    Start = word(MbsByteArray[8],MbsByteArray[9]);
//    CoilDataLength = word(MbsByteArray[10],MbsByteArray[11]);
//    MbsByteArray[5] = 6;
//    for(int i = 0; i < CoilDataLength; i++)
//    {
//      SetBit(Start + i,bitRead(MbsByteArray[13 + (i/8)],i-((i/8)*8)));
//    }
//    MessageLength = 12;
//    client.write(MbsByteArray, MessageLength);
//    MbsFC = MB_FC_NONE;
//  }  
  //****************** Write Multiple Registers (16) ******************
//  if(MbsFC == MB_FC_WRITE_MULTIPLE_REGISTERS) {
//    Serial.println("Write mutiple rigsters started");
//    Start = word(MbsByteArray[8],MbsByteArray[9]);
//    WordDataLength = word(MbsByteArray[10],MbsByteArray[11]);
//    ByteDataLength = WordDataLength * 2;
//    MbsByteArray[5] = 6;
//    for(int i = 0; i < WordDataLength; i++)
//    {
//      MbData[Start + i] =  word(MbsByteArray[ 13 + i * 2],MbsByteArray[14 + i * 2]);
//    }
//    MessageLength = 12;
//    client.write(MbsByteArray, MessageLength);
//    MbsFC = MB_FC_NONE;
//  }
}


//****************** ?? ******************
MB_FC MGS_MODBUS::set_fc(int fc)
{
  MB_FC FC;
  FC = MB_FC_NONE;
  if(fc == 1) FC = MB_FC_READ_COILS;
  if(fc == 2) FC = MB_FC_READ_DISCRETE_INPUT;
  if(fc == 3) FC = MB_FC_READ_REGISTERS;
  if(fc == 4) FC = MB_FC_READ_INPUT_REGISTER;
  if(fc == 5) FC = MB_FC_WRITE_COIL;
  if(fc == 6) FC = MB_FC_WRITE_REGISTER;
  if(fc == 15) FC = MB_FC_WRITE_MULTIPLE_COILS;
  if(fc == 16) FC = MB_FC_WRITE_MULTIPLE_REGISTERS;
  return FC;
}
 
//Uint16 MgsModbus::GetDataLen()
//{
//  return MbDataLen;
//}
 
 
//bool8 MgsModbus::GetBit(word Number)
//{
//  int ArrayPos = Number / 16;
//  int BitPos = Number - ArrayPos * 16;
//  bool8 Tmp = bitRead(MbData[ArrayPos],BitPos);
//  return Tmp;
//}
//
//
//bool8 MgsModbus::SetBit(word Number,boolean Data)
//{
//  int ArrayPos = Number / 16;
//  int BitPos = Number - ArrayPos * 16;
//  bool8 Overrun = ArrayPos > MbDataLen * 16; // check for data overrun
//  
//  if (!Overrun){                 
//    bitWrite(MbData[ArrayPos],BitPos,Data);
//  } 
//  return Overrun;
//}


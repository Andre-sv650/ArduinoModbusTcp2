

#include "mgs_modbus.h"
#include "debug/modbus_debug.h"

// For Arduino 1.0
EthernetServer MbServer(MB_PORT);
EthernetClient MbmClient;
//OneWire TemperaturSensor(52);

MGS_MODBUS::MGS_MODBUS()
{
  MbsFC = MB_FC_NONE;

  //Initialize all sensors.
  SensorElements.initiate();
}

//****************** Receive data for ModBusSlave ****************
void MGS_MODBUS::run()
{
  //****************** Read from socket ****************
  EthernetClient client = MbServer.available();

  if (client.available())
  {
    delay(1);
    int i = 0;
    while (client.available())
    {
      MbsByteArray[i] = client.read();
      i++;
    }

    //Read the incoming data.
    MbsFC = set_fc(MbsByteArray[7]); //Byte 7 of request is FC
  }

  //****************** Read Coils (1 & 2) **********************
  if (MbsFC == MB_FC_READ_COILS || MbsFC == MB_FC_READ_DISCRETE_INPUT)
  {
    Serial.println("Read coil or discrete input started");
    //Read the data.
    int messageLength = this->SensorElements.DataHandler.read_coil(MbsByteArray);

    client.write(MbsByteArray, messageLength);
    //Serial.println("Read coil end");
    MbsFC = MB_FC_NONE;
  }
  //****************** Read Registers (3 & 4) ******************
  else if (MbsFC == MB_FC_READ_REGISTERS || MbsFC == MB_FC_READ_INPUT_REGISTER)
  {
    Serial.println("Read register started");
    //Read the data.
    int messageLength = this->SensorElements.DataHandler.read_register(MbsByteArray);

    client.write(MbsByteArray, messageLength);
    MbsFC = MB_FC_NONE;
  }
  //****************** Write Coil (5) **********************
  else if (MbsFC == MB_FC_WRITE_COIL)
  {
    Serial.println("Write coil started");
    bool8 newValue;

    if (get_word(MbsByteArray[10], MbsByteArray[11]) == 0xFF00u)
    {
      newValue = TRUE;
    }
    else if ((get_word(MbsByteArray[10], MbsByteArray[11])) == 0x0000)
    {
      newValue = false;
    }

    int bitNumber = get_word(MbsByteArray[8], MbsByteArray[9]);

    //Set the coil.
    this->SensorElements.DataHandler.write_coil(bitNumber, newValue);
    //Send the same data back to the server.
    client.write(MbsByteArray, 12); //The message length is always 12 byte

    MbsFC = MB_FC_NONE;
  }
  //****************** Write Register (6) ******************
  else if (MbsFC == MB_FC_WRITE_REGISTER)
  {
    Serial.println("Write register started");
    
    this->SensorElements.DataHandler.write_register(MbsByteArray);
    MbsByteArray[5] = 6; //Number of bytes after this one.

    //Return the command to the sender. This is always 12 byte long.
    client.write(MbsByteArray, 12); //The message length is always 12
    MbsFC = MB_FC_NONE;
  }
  //****************** Write Multiple Coils (15) **********************
  else if (MbsFC == MB_FC_WRITE_MULTIPLE_COILS)
  {
    Serial.println("Write mutliple coil started");
    int Start = word(MbsByteArray[8], MbsByteArray[9]);
    int CoilDataLength = word(MbsByteArray[10], MbsByteArray[11]);
    MbsByteArray[5] = 6;

    for (int i = 0; i < CoilDataLength; i++)
    {
      Uint8 value = bitRead(MbsByteArray[13 + (i / 8)], i - ((i / 8) * 8));
      //Set the coil.
      this->SensorElements.DataHandler.write_coil(Start + i, value);
    }
    //Return the data to the sender.
    int MessageLength = 12;
    client.write(MbsByteArray, MessageLength);
    MbsFC = MB_FC_NONE;
  }
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

  //Call all background routines.
  this->SensorElements.DataHandler.background_routine();
}

//****************** Get the request command ******************
MODBUS_COMMAND MGS_MODBUS::set_fc(int fc)
{
  MODBUS_COMMAND command;

  if (fc == 1)
    command = MB_FC_READ_COILS;
  else if (fc == 2)
    command = MB_FC_READ_DISCRETE_INPUT;
  else if (fc == 3)
    command = MB_FC_READ_REGISTERS;
  else if (fc == 4)
    command = MB_FC_READ_INPUT_REGISTER;
  else if (fc == 5)
    command = MB_FC_WRITE_COIL;
  else if (fc == 6)
    command = MB_FC_WRITE_REGISTER;
  else if (fc == 15)
    command = MB_FC_WRITE_MULTIPLE_COILS;
  else if (fc == 16)
    command = MB_FC_WRITE_MULTIPLE_REGISTERS;
  else
    command = MB_FC_NONE;

  return command;
}

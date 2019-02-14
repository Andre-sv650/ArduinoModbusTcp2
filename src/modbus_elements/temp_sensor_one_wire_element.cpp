
#include "project_defines.h"
#include "../debug/modbus_debug.h"

#ifdef TEMP_SENSOR_ONE_WIRE_ELEMENT_ENABLED
#define TEMP_SENSOR_ONE_WIRE_ELEMENT_CPP

#include "temp_sensor_one_wire_element.h"

TEMP_SENSOR_ONE_WIRE_ELEMENT::TEMP_SENSOR_ONE_WIRE_ELEMENT(void)
{
}


void TEMP_SENSOR_ONE_WIRE_ELEMENT::initiate(Uint8 Pin, Uint8 StartAddress, OneWire *pTempSensor)
{
      //One address for the temperatur and one for the humidity
    Uint8 addressses[] = {StartAddress};
    
    this->pTempSensor = pTempSensor;
    this->Pin = Pin;
    Temperature = -200;

    MODBUS_ELEMENT_BASE::initiate(addressses, 1u);
}


void TEMP_SENSOR_ONE_WIRE_ELEMENT::background_routine(void)
{
    //Get the temperatur and save it.
    //returns the temperature from one DS18S20 in DEG Celsius
    byte data[12];
    byte addr[8];

    if (!pTempSensor->search(addr))
    {
        //no more sensors on chain, reset search
        pTempSensor->reset_search();
        Temperature = -1000;
        return;
    }

    if (OneWire::crc8(addr, 7) != addr[7])
    {
        Serial.println("CRC is not valid!");
        Temperature = -1000;
    }

    if (addr[0] != 0x10 && addr[0] != 0x28)
    {
        Serial.print("Device is not recognized");
        Temperature = -1000;
    }

    pTempSensor->reset();
    pTempSensor->select(addr);
    pTempSensor->write(0x44, 1); // start conversion, with parasite power on at the end

    byte present = pTempSensor->reset();
    pTempSensor->select(addr);
    pTempSensor->write(0xBE); // Read Scratchpad

    for (int i = 0; i < 9; i++)
    { // we need 9 bytes
        data[i] = pTempSensor->read();
    }

    pTempSensor->reset_search();

    byte MSB = data[1];
    byte LSB = data[0];

    float tempRead = ((MSB << 8) | LSB); //using two's compliment
    Temperature = tempRead / 16;
}

Uint8 TEMP_SENSOR_ONE_WIRE_ELEMENT::get_data(void)
{
    //Not possible.
    return (Uint8)255u;
}

void TEMP_SENSOR_ONE_WIRE_ELEMENT::get_data(Uint8 Address, Uint8 pDataArray[], Uint8 NumberOfBytes)
{
    Serial.println("Get method called");
    // if(isnan(Temperature)){
    //     MODBUS_DEBUG::print_command_error("Error temperatur one wire on pin is nan: ", 
    //     this->StartAddress[0]);
    // }
    // else if (NumberOfBytes == 4u)
    // {
    //     //Set the float value to the data array. This is both little endian.
    //     *((float32 *)&pDataArray[0]) = Temperature;

    //     MODBUS_DEBUG::print_one_wire_temperature(Pin, (int16)Temperature);
    // }
    // else if (NumberOfBytes == 2u)
    // {
    //     int16 temperature = (int16)Temperature;
    //     pDataArray[1] = (Uint8)temperature;
    //     pDataArray[0] = (Uint8)(temperature >> 8u);

    //     MODBUS_DEBUG::print_one_wire_temperature(Pin, temperature);
    // }
    // else{
    //     pDataArray[0] = 255u;

    //     MODBUS_DEBUG::print_one_wire_temperature(Pin, (int16)Temperature);
    // }
}

#endif /* TEMP_SENSOR_ONE_WIRE_CPP */
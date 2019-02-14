#include "../project_defines.h"
#ifdef DHT22_ELEMENT_ENABLED

// Depends on the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// See guide for details on sensor wiring and usage:
// https://learn.adafruit.com/dht/overview
#include "dht22_element.h"
#include "../debug/modbus_debug.h"

DHT22_ELEMENT::DHT22_ELEMENT()
{
}

void DHT22_ELEMENT::initiate(Uint8 StartAddress, Uint32 StartPin)
{
  //One address for the temperatur and one for the humidity
  Uint8 addressses[] = {StartAddress, StartAddress + 1};

  //Set the start pin
  Pin = StartPin;

  //Set the temperature and humditiy to invalid values.
  Temperature = -500;
  Humidity = -500;
  Dht22NotAvailableDebugMessageSet = 0u;

  MODBUS_ELEMENT_BASE::initiate(addressses, 2u);

  // Data wire is plugged on the Arduino
  // Connect a 4.7K or 10K resistor between VCC and the data pin (strong pullup) Setup a DHT22 instance
  MyDht22.begin(Pin, DHT22);
}

Uint8 DHT22_ELEMENT::get_data()
{
  //Not possible.
  return 255u;
}

void DHT22_ELEMENT::background_routine(void)
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float humidity = MyDht22.readHumidity();
  // Read temperature as Celsius (the default)
  float temperature = MyDht22.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = 0.0f; // MyDht22.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature) || isnan(f))
  {
    if(Dht22NotAvailableDebugMessageSet < 200){
      Dht22NotAvailableDebugMessageSet++;
    }

    if(Dht22NotAvailableDebugMessageSet == 200){
      //MODBUS_DEBUG::print_dht22_not_available(Pin);
      Temperature = -500;
      Humidity = -500;

      Dht22NotAvailableDebugMessageSet = 201;
    }
  }
  else{
    if(Dht22NotAvailableDebugMessageSet > 200){
      
      //MODBUS_DEBUG::print_dht22_now_available(Pin);
    }

    Dht22NotAvailableDebugMessageSet = 0;

    //Data valid. Set the data.
    Humidity = humidity;
    Temperature = temperature;
  }
}

void DHT22_ELEMENT::get_data(Uint8 Address, Uint8 pDataArray[], Uint8 NumberOfBytes)
{
  if (NumberOfBytes == 4u)
  {
    //Check which data should be get.
    if (Address == StartAddress[0])
    {
      //Get the temperature. Set the float value to the data array. This is both little endian.
      *((float32 *)&pDataArray[0]) = Temperature;

      MODBUS_DEBUG::print_dht22_temperature(Pin, Temperature);
    }
    else if(Address == StartAddress[1]){
      //Get humidity
      *((float32 *)&pDataArray[0]) = Humidity;

      MODBUS_DEBUG::print_dht22_humidity(Pin, Humidity);
    }
    else{
      //Not present
      pDataArray[0] = 255u;
    }
  }
  else if(NumberOfBytes == 2u){
    if(Address == StartAddress[0]){
      Uint16 temperature = (Uint16)Temperature;
      pDataArray[1] = (Uint8)temperature;
      pDataArray[0] = (Uint8)(temperature >> 8u);
      
      MODBUS_DEBUG::print_dht22_temperature(Pin, Temperature);
    }
    else{
      Uint16 humidity = (Uint16)Humidity;
      pDataArray[1] = (Uint8)humidity;
      pDataArray[0] = (Uint8)(humidity >> 8u);

      MODBUS_DEBUG::print_dht22_humidity(Pin, Humidity);
    }
  }
  else if(NumberOfBytes == 1u){
    if(Address == StartAddress[0]){
      pDataArray[0] = (Uint8)Temperature;
      
      MODBUS_DEBUG::print_dht22_temperature(Pin, Humidity);
    }
    else{
      pDataArray[0] = (Uint8)Humidity;

      MODBUS_DEBUG::print_dht22_humidity(Pin, Humidity);
    }
  }
  else
  {
    pDataArray[0] = 255u;

    MODBUS_DEBUG::print_command_error("Error reading DHT22", Address);
  }
}

#endif //DHT22_ELEMENT_ENABLED

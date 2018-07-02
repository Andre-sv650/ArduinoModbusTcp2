#include "../project_defines.h"
#ifdef DHT22_ELEMENT_ENABLED

// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// Depends on the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
#include "cpu_datatypes.h"
#include "external_libraries/DHT.h"
#include "dht22_element.h"

// See guide for details on sensor wiring and usage:
// https://learn.adafruit.com/dht/overview
Uint32 delayMS;

DHT22_ELEMENT::DHT22_ELEMENT()
{

}

void DHT22_ELEMENT::initiate() 
{
  // Data wire is plugged into port 7 on the Arduino
  // Connect a 4.7K resistor between VCC and the data pin (strong pullup) Setup a DHT22 instance
  DHT22 myDHT22(StartPin);
}

Uint8 DHT22_ELEMENT::get_data() 
{
  this->trigger_data();
  
  // Get temperature event and print its value.
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  }
  else {
    Serial.print("Temperature: ");
    Serial.print(event.temperature);
    Serial.println(" *C");
  }
  
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Error reading humidity!");
  }
  else {
    Serial.print("Humidity: ");
    Serial.print(event.relative_humidity);
    Serial.println("%");
  }

  return dht.temperature;
}

void DHT22_ELEMENT::trigger_data(void)
{

  DHT22_ERROR_t errorCode;

  // The sensor can only be read from every 1-2s, and requires a minimum
  // 2s warm-up after power-on.
  delay(2000);

  Serial.print("Requesting data...");
  errorCode = myDHT22.readData();
  switch(errorCode)
  {
  case DHT_ERROR_NONE:
    Serial.print("Got Data ");
    Serial.print(myDHT22.getTemperatureC());
    Serial.print("C ");
    Serial.print(myDHT22.getHumidity());
    Serial.println("%");
    // Alternately, with integer formatting which is clumsier but more compact to store and
    // can be compared reliably for equality:
    //    
    char buf[128];
    sprintf(buf, "Integer-only reading: Temperature %hi.%01hi C, Humidity %i.%01i %% RH",
        myDHT22.getTemperatureCInt()/10, abs(myDHT22.getTemperatureCInt()%10),
        myDHT22.getHumidityInt()/10, myDHT22.getHumidityInt()%10);
    Serial.println(buf);
    break;
  case DHT_ERROR_CHECKSUM:
    Serial.print("check sum error ");
    Serial.print(myDHT22.getTemperatureC());
    Serial.print("C ");
    Serial.print(myDHT22.getHumidity());
    Serial.println("%");
    break;
  case DHT_BUS_HUNG:
    Serial.println("BUS Hung ");
    break;
  case DHT_ERROR_NOT_PRESENT:
    Serial.println("Not Present ");
    break;
  case DHT_ERROR_ACK_TOO_LONG:
    Serial.println("ACK time out ");
    break;
  case DHT_ERROR_SYNC_TIMEOUT:
    Serial.println("Sync Timeout ");
    break;
  case DHT_ERROR_DATA_TIMEOUT:
    Serial.println("Data Timeout ");
    break;
  case DHT_ERROR_TOOQUICK:
    Serial.println("Polled to quick ");
    break;
  }
}

#endif //DHT22_ELEMENT_ENABLED

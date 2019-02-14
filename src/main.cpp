
#include <SPI.h>
#include <Ethernet2.h>
#include "cpu_datatypes.h"
#include "mgs_modbus.h"

MGS_MODBUS Mb;

//ModbusDebug MyModbusDebug;
int inByte = 0; // incoming serial byte

// Ethernet settings (depending on MAC and Local network)
byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0x94, 0xB5 };
IPAddress ip(192, 168, 1, 170);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);


void setup() {
  // serial setup
  Serial.begin(9600);
  Serial.println("Serial interface started");

  // initialize the ethernet device
  Ethernet.begin(mac, ip, gateway, subnet);   // start etehrnet interface
  Serial.println("Ethernet interface started");

  // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
  Serial.println();
}

void loop() {
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
  }

  Mb.run();
}

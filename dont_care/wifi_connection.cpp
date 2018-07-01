
/*
 *  Simple HTTP get webclient test
 */
 
#include <ESP8266.h>
#include "wifi_connection.h"
 
const char* ssid     = "Andre&Sylvia";
const char* password = "Paulchen";

WIFI_CONNECTION::WIFI_CONNECTION()
{

}

void WIFI_CONNECTION::initiate()
{
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
}
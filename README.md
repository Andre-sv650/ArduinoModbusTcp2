# ArduinoModbusTcp2
This is an arduino library for Modbus TCP.

##Prepare the sofware:
1. Install Visual studio code
2. Install platform IO
3. Install arduino or arduino mega Boards from the Platform IO start page inside Visual studio code.

##Prepare the hardware:
1. Buy an Arduino or Arduino Mega
2. Buy an Ethernet 2 Shield

##Instructions for first setup:
1. Check out this repository or download the zip file.
2. Go to the platform IO Site and click Open Project.
3. Open the folder where the zip file was unzipped. Click open
4. Open platform IO ini file in the Visual studio code editor. Check if you have an arduino or arduino mega, choose the correct platform.
5. Compile the project with visual studio code with platform IO installed. This should be finished without errors.


##Choose connected hardware:
1. Open the src folder.
2. Open the file sensor_elements_initiate.cpp
3. Setup the harware that is connected. There are 2 examples given.
 - The first example is Relais1FromPin8.initiate(0, 8, 4, TRUE, TRUE). This initializes a relais at modbus address 0 starting at arduino pin 8 with 4 pins means 4 relais and reversed setting means, that the Relais gets on, if the output is off. The last true is that only one relais can be set at one time. You can turn this off if needed.
 - The second example is a DHT22 sensor. Dth22Sensor.initiate(100, 2). This initializes a DHT22 element at Modbus address 100. Address 100 is the temperature and Address 101 is the humidity.
4. Setup the IP address. Open the file main.cpp and set the mac address and the IP Address of the device.

##Debug:
1. You can test the Modbus connection with the https://sourceforge.net/projects/qmodmaster/ 
 - Download the program and unzip it.
 - Start the program and click on options. Choose Modbus TCP and put in the IP address of the arduino.
 - Click on connect.

2. For the relais you can now click on read coil with the Start Address. For our example set the start address to 0.
 - Click on Read/Write left from the connect button. Now the relais state is read from arduino.
 - You can read more than one coil with the button Number of coils.
 - You can write coils to enable an relais or release an relais.
 - Also you can write multiple coils or write single register.
  
3. For the DHT22 sensor:
 - Click on the Read holding register or read input register with Stard address set. In our example the start address is 100.
 - The data is get as 16 bit value.
 
 ##Domiq Base
 Domiq Base is a product to visualize LCN smart home devices. Domiq base can also use modbus tcp connections for incoming or outgoing data.
 1. Login to Domiq Base and choose Modbus
 2. Add a connection via "Verbindung hinzufügen".
 
 ###Setup a connection to the Relais in Domiq Base
 3. Put in a name and choose TCP as connection. In my example i choose the name Carport.
 4. Put in the IP address of the arduino and set the port to 502.
 5. Now add an device with the button "Gerät hinzufügen".
 6. Put in a name and description. Set the Address to 1. In my example i choose the name Arduino.
 7. Put in a outreg with address 0, datatype Uint8 or Uint16, Multiplizierer 1 and Offset 0. Setup a Name and description.
  - Now a outreg is set and the relais elements can be switched on and off. In my example i used the name BewaesserungGesamt.
 9. Now you can use this new variable with the following string MODBUS.Carport.Arduino.BewaesserungGesamt
  - Go to register Remote and choose the element "Auswahl". Set the Kanal to MODBUS.Carport.Arduino.BewaesserungGesamt.
  - Put in Wert = 0 Kurz = OFf
  - Put in Wert = 1 Kurz = Rasen links
  - Put in Wert = 2 Kurz = Rasen rechts.
  - Put in Wert = 4 Kurz = Rasen mitte.
  - Now you can switch on and off 3 relais with a correct name.
 10. The same procedure can be used for humidity or temperatur.
  - In the Modbus tab use inreg with type int16. Put in a name, for example Aussentemperatur.
  - Set the Kanal to MODBUS.Carport.Arduino.Aussentemperatur.
  - Now you can visualize the temperature.

#License
All Software is licensed under the GNU license V3.
The library modules are licensed under the MIT license or are from https://github.com/krvarma/Dallas_DS18B20_SparkCore/blob/master/README.md
  

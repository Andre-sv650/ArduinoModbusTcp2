# ArduinoModbusTcp2
This is an arduino library for Modbus TCP.

Prepare the sofware:
1. Install Visual studio code
2. Install platform IO
3. Install arduino or arduino mega Boards from the Platform IO start page inside Visual studio code.

Prepare the hardware:
1. Buy an Arduino or Arduino Mega
2. Buy an Ethernet 2 Shield

Instructions for first setup:
1. Check out this repository or download the zip file.
2. Go to the platform IO Site and click Open Project.
3. Open the folder where the zip file was unzipped. Click open
4. Open platform IO ini file in the Visual studio code editor. Check if you have an arduino or arduino mega, choose the correct platform.
5. Compile the project with visual studio code with platform IO installed. This should be finished without errors.


Choose connected hardware:
1. Open the src folder.
2. Open the file sensor_elements_initiate.cpp
3. Setup the harware that is connected. There are 2 examples given.
  a. The first example is Relais1FromPin8.initiate(0, 8, 4, TRUE, TRUE). This initializes a relais at modbus address 0 starting at arduino pin 8 with 4 pins means 4 relais and reversed setting means, that the Relais gets on, if the output is off. The last true is that only one relais can be set at one time. You can turn this off if needed.
  b. The second example is a DHT22 sensor. Dth22Sensor.initiate(100, 2). This initializes a DHT22 element at Modbus address 100. Address 100 is the temperature and Address 101 is the humidity.
4. Setup the IP address. Open the file main.cpp and set the mac address and the IP Address of the device.

Debug:
1. You can test the Modbus connection with the https://sourceforge.net/projects/qmodmaster/ 
  a. Download the program and unzip it.
  b. Start the program and click on options. Choose Modbus TCP and put in the IP address of the arduino.
  c. Click on connect.
 2. For the relais you can now click on read coil with the Start Address. For our example set the start address to 0.
  a. Click on Read/Write left from the connect button. Now the relais state is read from arduino.
  b. You can read more than one coil with the button Number of coils.
  c. You can write coils to enable an relais or release an relais.
  d. Also you can write multiple coils or write single register.
3. For the DHT22 sensor:
  a. Click on the Read holding register or read input register with Stard address set. In our example the start address is 100.
  b. The data is get as 16 bit value.
  

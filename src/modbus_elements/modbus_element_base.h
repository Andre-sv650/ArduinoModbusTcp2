

#ifndef MODBUS_ELEMENT_BASE_H
#define MODBUS_ELEMENT_BASE_H

#include "cpu_datatypes.h"


/*
 * One element
 */
class MODBUS_ELEMENT_BASE
{
  #define MODBUS_ELEMENT_BASE_ARRAY_SIZE 3

  //Members
public:
    /*
   * The start address in full bytes.
   */
  Uint8 StartAddress[MODBUS_ELEMENT_BASE_ARRAY_SIZE];
  /*
   * The size in bits.
   */
  Uint8 SizeInBits[MODBUS_ELEMENT_BASE_ARRAY_SIZE];
  
  /*
   * The pin on the arduino.
   */
  Uint8 Pin;
  /*
  * The number of registered elements.
  */
  Uint8 NumberOfElements;
  /*
   * Methods
   */
public:
  MODBUS_ELEMENT_BASE();

  void initiate(Uint8 Address, Uint8 SizeInBitsOfElement);

  void initiate(Uint8 AddressArray[], Uint8 NumberOfAdresses);

  virtual void background_routine(void);

  bool8 get_data(Uint8 BitNumber);

  virtual Uint8 get_data(void) = 0;

  virtual void get_data(Uint8 Address, Uint8 pDataArray[], Uint8 NumberOfBytes);

  virtual void set_data(Uint8 Data);

  virtual void set_data(Uint8 BitNumber, Uint8 Data);
};




#endif /* MODBUS_ELEMENT_BASE_H_ */

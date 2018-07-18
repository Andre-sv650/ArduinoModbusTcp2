

#ifndef MODBUS_ELEMENT_BASE_H
#define MODBUS_ELEMENT_BASE_H

#include "../cpu_datatypes.h"


/*
 * One element
 */
class MODBUS_ELEMENT_BASE
{
  //Members
public:
  /*
   * The pin on the arduino.
   */
  Uint32 Pin;
  /*
   * The start address in full bytes.
   */
  Uint8 StartAddress;

  /*
   * The size in bits.
   */
  Uint8 SizeInBits;

  /*
   * Methods
   */
public:
  MODBUS_ELEMENT_BASE();

  virtual Uint8 get_data(Uint8 ByteNumber);

  bool8 get_data_bitwise(Uint8 BitNumber);

  virtual void set_data(Uint8 Data);

  virtual void set_data(Uint8 BitNumber, Uint8 Data);
};


#endif /* MODBUS_ELEMENT_BASE_H_ */

#ifndef MODBUS_ELEMENT_ARRAY_H
#define MODBUS_ELEMENT_ARRAY_H

#include "cpu_datatypes.h"
#include "modbus_element_base.h"

/*
 * The array containing all modbus elements.
 */
class MODBUS_ELEMENT_ARRAY
{
private:
#define ELEMENTS_LENGTH 20
  /*
   * The size in bits.
   */
  Uint8 RegisteredElementsCount;
  
  /*
   * The start address in full bytes.
   */
  MODBUS_ELEMENT_BASE *pRegisteredElements[ELEMENTS_LENGTH];
  
  //Members
public:
   //Methods
   MODBUS_ELEMENT_ARRAY();

   void background_routine(void);
   
   void add_element(MODBUS_ELEMENT_BASE *pNewElement);

   MODBUS_ELEMENT_BASE* get_element_from_address(Uint8 StartAddress);
};


#endif /* MODBUS_ELEMENT_ARRAY_H_ */

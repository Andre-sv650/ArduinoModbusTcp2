
#include "../project_defines.h"

#ifdef LIGHT_INTENSITY_ELEMENT_ENABLED

#ifndef LIGHT_INTENSITY_ELEMENT_CPP
#define LIGHT_INTENSITY_ELEMENT_CPP

#include "Arduino.h"
#include "light_intensity_element.h"

/*
 * Constructor
 */
LIGHT_INTENSITY_ELEMENT::LIGHT_INTENSITY_ELEMENT()
{

}


void LIGHT_INTENSITY_ELEMENT::initiate(Uint32 Pin)
{
  this->Pin = Pin;
}




Uint8 LIGHT_INTENSITY_ELEMENT::get_data(Uint8 ByteNumber)
{
  Uint8 result = 0u;
  
  for(int i = 0u; i < this->SizeInBits; i++){
    //Read the digital data.
    result |= digitalRead(this->Pin + i) << i;
  }
  
  return result;
}


#endif /* LIGHT_INTENSITY_ELEMENT_CPP */

#endif //LIGHT_INTENSITY_ELEMENT_ENABLED

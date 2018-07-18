
#include "../project_defines.h"

#ifdef PRESENCE_DETECTOR_ELEMENT_ENABLED

#ifndef PRESENCE_DETECTOR_ELEMENT_CPP
#define PRESENCE_DETECTOR_ELEMENT_CPP

#include "Arduino.h"
#include "presence_detector_element.h"

/*
 * Constructor
 */
PRESENCE_DETECTOR_ELEMENT::PRESENCE_DETECTOR_ELEMENT()
{

}


void PRESENCE_DETECTOR_ELEMENT::initiate(Uint32 Pin)
{
  this->initiate(Pin, 1u);
}

/*
 * The initiate method. Set the pin of the arduino and the number of detectors that are connected from this pin.
 * For example Pin is 30 and number of detectors is 4. Pin 30, 31, 32 and 33 are connected.
 */
void PRESENCE_DETECTOR_ELEMENT::initiate(Uint32 Pin, Uint8 NumberOfDetectors)
{
  this->Pin = Pin;
  this->SizeInBits = NumberOfDetectors;
}


Uint8 PRESENCE_DETECTOR_ELEMENT::get_data(Uint8 ByteNumber)
{
  Uint8 result = 0u;
  
  for(int i = 0u; i < this->SizeInBits; i++){
    //Read the digital data.
    result |= digitalRead(this->Pin + i) << i;
  }
  
  return result;
}


#endif /* PRESENCE_DETECTOR_ELEMENT_CPP */

#endif //PRESENCE_DETECTOR_ELEMENT_ENABLED

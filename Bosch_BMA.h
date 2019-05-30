#ifndef __BMA456_H_
#define __BMA456_H_

#include <stdint.h>
#include "Bosch_BMA456_defs.h"

//only for testing

class Bosch_BMA
{
public:
  uint8_t readAddress(uint8_t addr);
  void writeAddress(uint8_t addr, uint8_t value);

  //Bosch_BMA();
  uint8_t getChipID();
  uint8_t getInternalState();
  uint32_t getSensortime();
  void getInternalConfig(uint8_t *data);
  void writeInternalConfig(uint8_t *data);
  void init();
  uint8_t InterruptState = 0;
  uint16_t debugCntr = 0;

};

#endif // __BMA456_H_

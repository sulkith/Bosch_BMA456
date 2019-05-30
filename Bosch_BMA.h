#ifndef __BMA456_H_
#define __BMA456_H_

#include <stdint.h>
#include "Bosch_BMA456_defs.h"

//only for testing

class Bosch_BMA
{
  static const uint8_t InterruptConfigLenght =64;//from Datasheet
  uint8_t InterruptConfig[InterruptConfigLenght] ={0};
public:
  /*!
     \brief read the value of a specific register directly from the device
     \param addr Address of the Register to read
     \returns the Value of this Register
  */
  uint8_t readAddress(uint8_t addr);
  /*!
     \brief write a Value directly to a register of the device
     \param addr Address of the Register to writeReg
     \param value the Value which should be written to the register
  */
  void writeAddress(uint8_t addr, uint8_t value);

  /*!
     \brief read the chip ID
     \returns the chip ID
  */
  uint8_t getChipID();
  /*!
     \brief get the Status of the Interrupt Engine Register 0x2A
     For a better Description of the Values see the BMA456 Datasheet Register 0x2A
     \returns state of the Interrupt Engine
  */
  uint8_t getInternalState();
  void getInternalConfig(uint8_t *data);
  void writeInternalConfig(uint8_t *data);
  /*!
     \brief read the config of the Interrupt controller from the Device
  */
  void startInterruptConfig();
  /*!
     \brief write the Interrupt controller config to the Device
  */
  void writeInterruptConfig();
  /*!
     \brief setup the motion Detection funtion.
     \param threshhold the threshhold for the movement force Every increment is about 0.48mg
     \param delay the delay for motion detection in steps of 20ms
     \param axis axix config in the following bit order x-y-z
     \param nomotion if 1 the interrupt is switched to nomotion
     \pre startInterruptConfig has to be called before.
     \post writeInterruptConfig has to be called to write back the config
  */
  void setMotionDetection(uint16_t threshhold, uint8_t delay, uint8_t axis, uint8_t nomotion);

/*!
   \brief setup the Tap Detection Feature
   \param singleTap if 1 the interrupt will detect single Taps instead of double Taps
   \param strength setup the strength between 0 and 7
   \param enable if 1 the function will be enabled
   \pre startInterruptConfig has to be called before.
   \post writeInterruptConfig has to be called to write back the config
*/
  void setTapDetection(uint8_t singleTap, uint8_t strength, uint8_t enable);

/*!
   \brief setup the wrist tilt function
   \param enable if 1 enables the wrist tilt functions
   \pre startInterruptConfig has to be called before.
   \post writeInterruptConfig has to be called to write back the config
*/
  void setWristTiltFunction(uint8_t enable);
  /*!
     \brief set the config ID
     \param confID the configuration IDto write
     \pre startInterruptConfig has to be called before.
     \post writeInterruptConfig has to be called to write back the config
  */
    void setConfigID(uint8_t confID);
  /*!
     \brief set Axis Mapping
     This function sets the Mapping of the Sensor Axis.
     For some good graphical Hints see the Datasheet in the Wrist Tilt Chapter
    |Value | Axis          |
    |------|---------------|
    |   0  | Map to x Axis |
    |   1  | Map to y Axis |
    |   2  | Map to z Axis |


     \param x mapping of the x Axis
     \param x_invert invert the new x axis
     \param y mapping of the y Axis
     \param y_invert invert the new y axis
     \param z mapping of the z Axis
     \param z_invert invert the new z axis
     \pre startInterruptConfig has to be called before.
     \post writeInterruptConfig has to be called to write back the config
  */
    void setAxisMapping(uint8_t x, uint8_t x_invert, uint8_t y, uint8_t y_invert, uint8_t z, uint8_t z_invert);
  /*!
     \brief init the Device
  */
  void init();

  uint8_t InterruptState = 0;
  uint16_t debugCntr = 0;

};

#endif // __BMA456_H_

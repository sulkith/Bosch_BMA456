#ifndef __BMA456_H_
#define __BMA456_H_

#include <stdint.h>
#include "Bosch_BMA456_defs.h"

//only for testing

class Bosch_BMA
{
  static const uint8_t InterruptConfigLenght =64;//from Datasheet
  uint8_t InterruptConfig[InterruptConfigLenght] ={0};
  uint8_t AxisMapping[6] = {BMA4_X_AXIS,0,BMA4_Y_AXIS,0,BMA4_Z_AXIS,0};
  const uint8_t AxisRegister[3] = {BMA4_X_AXIS,BMA4_Y_AXIS,BMA4_Z_AXIS};
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
  /*!
     \brief read accelleration on X Axis
     \returns accelleration on X Axis
  */
  int16_t get_X_Accel();
  /*!
     \brief read accelleration on Y Axis
     \returns accelleration on Y Axis
  */
  int16_t get_Y_Accel();
  /*!
     \brief read accelleration on Z Axis
     \returns accelleration on Z Axis
  */
  int16_t get_Z_Accel();
  /*!
     \brief read accelleration on corrected X Axis
     \pre setAxisMapping has to be called before.
     \returns accelleration on X Axis
  */
  int16_t get_X_Accel_corr();
  /*!
     \brief read accelleration on corrected Y Axis
     \pre setAxisMapping has to be called before.
     \returns accelleration on Y Axis
  */
  int16_t get_Y_Accel_corr();
  /*!
     \brief read accelleration on corrected Axis specified by the argument
     \param axis identified by Number: 1-x 2-y 3-z
     \pre setAxisMapping has to be called before.
     \returns accelleration on the specified Axis
  */
  int16_t get_Accel_corr(uint8_t axis);
  /*!
     \brief read accelleration on corrected Z Axis
     \pre setAxisMapping has to be called before.
     \returns accelleration on Z Axis
  */
  int16_t get_Z_Accel_corr();
  /*
     \brief read step Counter value
     \returns step counter value
  */
  uint32_t getSteps();
  /*!
     \brief reset Step counter value
  */
  void resetSteps();
  /*!
     \brief get the whole internal Config data of the BMA
     \param pointer to the Data. This Buffer has to be 64 Bytes
  */
  void getInternalConfig(uint8_t *data);
  /*!
     \brief write the whole internal Config data of the BMA
     \param pointer to the Data. This Buffer has to be 64 Bytes
     \pre startInterruptConfig has to be called before.
  */
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
     \brief setup the step counter
     \param enable if 1 enables the Step counter
     \pre startInterruptConfig has to be called before.
     \post writeInterruptConfig has to be called to write back the config
  */
    void setStepCounter(uint8_t enable);
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

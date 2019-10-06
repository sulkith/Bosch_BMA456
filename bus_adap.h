#ifndef __BUS_ADAP_H__
#define __BUS_ADAP_H__
/*!
 * \file bus_adap.c
 * header for the com driver
 * This interface is to be implemented by the lower bus driver.
 */

  /*!
     \brief write the specified Register
     \param reg the address of the Register to write
     \param val the value to write to the Register
  */
extern void writeReg(uint8_t reg, uint8_t val);
  /*!
     \brief write the specified Registers
     \param reg the address of the first Register to write
     \param val pointer to the values to write to the BMA Chip
     \param len the length of the write command
  */
extern void writeReg(uint8_t reg, uint8_t *val, uint8_t len);
  /*!
     \brief read the Register
     \param reg the address of the first Register to read
     \param len the length to read
     \returns the Value of this Register
  */
extern uint8_t readReg(uint8_t reg, uint8_t len);

  /*!
     \brief read the Registers
     \param reg the address of the first Register to read
     \param len the length to read
     \param buffer the buffer to write the result to
     \returns the Value of the first Register
  */
extern uint8_t readRegs(uint8_t reg, uint8_t len, uint8_t *buffer);
  /*!
     \brief stream write bigger data to the FEATURES_IN register
     \param data a pointer to the data which should be written
     \param index the index of the current data chunk
     \param length the length of this data chunk
  */
extern void stream_write(uint8_t * data, uint16_t index, uint8_t length);
  /*!
     \brief initialize the com driver
  */
extern void initComDriver();

#endif //__BUS_ADAP_H__

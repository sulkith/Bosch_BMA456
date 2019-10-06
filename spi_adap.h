#ifndef __SPI_ADAP_H__
#define __SPI_ADAP_H__
  /*!
     \brief set the funtion to activate and deactivate the SPI slave
     \post the initComDriver Function should be called after calling this Function
     \param setCS the function Pointer the enable funtion for the BMA
  */
extern void set_SPI_activate_CS(void (*setCS)(uint8_t));
#endif // __SPI_ADAP_H__

#include "Bosch_BMA.h"
#include "Bosch_BMA456_defs.h"
#include "spi/spi.h"
#include <string.h>
#include <util/delay.h>

uint16_t debugCntrTmp = 0;
uint8_t readBuffer[SPI_BUFFER_LENGTH] = {0};
uint8_t readLen = 0;
void (*activateCS)(uint8_t) = NULL;
uint8_t senData[SPI_BUFFER_LENGTH];

void set_SPI_activate_CS(void (*setCS)(uint8_t))
{
	activateCS = setCS;
}

//write to register
void writeReg(uint8_t reg, uint8_t val)
{
//  spi_start();
  senData[0] = reg&0x7F;
  senData[1] = val;
  //Activate CS
  if(activateCS != NULL)activateCS(1);
  spi_write(senData,2,NULL);
  spi_wait();
  //DeActivate CS
  if(activateCS != NULL)activateCS(0);
  _delay_ms(1);
//  spi_stop();
}
void writeReg(uint8_t reg, uint8_t *val, uint8_t len)
{
//  spi_start();
  senData[0]= reg&0x7F;
  //Activate CS
  if(activateCS != NULL)activateCS(1);
  for(uint8_t i = 0;i<len;++i)senData[i+1]=val[i];
  spi_write(senData,len+1,NULL);
  spi_wait();
  //DeActivate CS
  if(activateCS != NULL)activateCS(0);
  _delay_ms(1);
//  spi_stop();
  return;
}
//Callback funtion for reading more than one byte
void saveReadData(uint8_t *data)
{
  for(uint8_t i = 0;i<readLen;++i)
  {
    readBuffer[i] = data[i+1];
  }
  readLen = 0;
}
//Read register. Byte 0 is returned.
uint8_t readReg(uint8_t reg, uint8_t len)
{
//  spi_start();
  senData[0] = 0x80|reg;//Set first bit to signalize read
  //Activate CS
  if(activateCS != NULL)activateCS(1);
  spi_write(senData,1,NULL); //Send reg address
  spi_wait();
  readLen = len;//set the length for the read Data
  spi_read(len+1,&saveReadData);//Add the Dummy Byte
  spi_wait();
  //DeActivate CS
  if(activateCS != NULL)activateCS(0);
  _delay_ms(1);
//  spi_stop();
  return readBuffer[0];
}

uint8_t readRegs(uint8_t reg, uint8_t len, uint8_t *buffer)
{
//  spi_start();
  senData[0] = 0x80|reg;//Set first bit to signalize read
  //Activate CS
  if(activateCS != NULL)activateCS(1);
  spi_write(senData,1,NULL); //Send reg address
  spi_wait();
  readLen = len;//set the length for the read Data
  spi_read(len+1,&saveReadData);//Add the Dummy Byte
  spi_wait();
  if(activateCS != NULL)activateCS(0);
  //DeActivate CS
  //so this function is also usable for just one Byte
  if(buffer != NULL)
  {
    for(uint8_t i = 0;i<len;++i)
    {
      buffer[i] = readBuffer[i];
    }
  }
//  spi_stop();
  return readBuffer[0];
}
void stream_write(uint8_t * data, uint16_t index, uint8_t length)
{
//	void (*activateCS_temp)(uint8_t) = NULL;
//	activateCS_temp = activateCS;
//	activateCS = NULL;
//	debugCntrTmp+=length;
	uint8_t asic_msb = (uint8_t)((index / 2) >> 4);
	uint8_t asic_lsb = ((index / 2) & 0x0F);

	writeReg(BMA4_RESERVED_REG_5B_ADDR, asic_lsb);
	_delay_us(2);
  writeReg(BMA4_RESERVED_REG_5C_ADDR, asic_msb);
	_delay_us(2);

  writeReg(BMA4_FEATURE_CONFIG_ADDR, data, length);
//	activateCS = activateCS_temp;
  return;
}
void initComDriver()
{
	_delay_ms(1);//Toogle CSB Pin to get the BMA into SPI mode
  	if(activateCS != NULL)activateCS(1);
	_delay_ms(1);
  	if(activateCS != NULL)activateCS(0);
	_delay_ms(1);
}

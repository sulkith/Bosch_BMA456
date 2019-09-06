#include "Bosch_BMA.h"
#include "spi/spi.h"
#include <string.h>
#include <util/delay.h>

uint16_t debugCntrTmp = 0;
uint8_t readBuffer[SPI_BUFFER_LENGTH] = {0};
uint8_t readLen = 0;
void (*activateCS)(uint8_t) = NULL;

void set_SPI_activate_CS(void (*setCS)(uint8_t))
{
	activateCS = setCS;
}

//write to register
void writeReg(uint8_t reg, uint8_t val)
{
  uint8_t senData[2] = {reg,val};
  //Activate CS
  if(activateCS != NULL)activateCS(1);
  spi_write(senData,2,NULL);
  spi_wait();
  //DeActivate CS
  if(activateCS != NULL)activateCS(0);
}
void writeReg(uint8_t reg, uint8_t *val, uint8_t len)
{
  uint8_t senData[SPI_BUFFER_LENGTH];
  senData[0]= reg;
  //Activate CS
  if(activateCS != NULL)activateCS(1);
  for(uint8_t i = 0;i<len;++i)senData[i+1]=val[i];
  spi_write(senData,len+1,NULL);
  spi_wait();
  //DeActivate CS
  if(activateCS != NULL)activateCS(0);
  return;
}
//Callback funtion for reading more than one byte
void saveReadData(uint8_t *data)
{
  for(uint8_t i = 0;i<readLen;++i)
  {
    readBuffer[i] = data[i];
  }
  readLen = 0;
}
//Read register. Byte 0 is returned.
uint8_t readReg(uint8_t reg, uint8_t len)
{
  uint8_t senData = reg;
  //Activate CS
  if(activateCS != NULL)activateCS(1);
  spi_write(&senData,1,NULL); //Send reg address
  spi_wait();
  readLen = len;//set the length for the read Data
  spi_read(len,&saveReadData);
  spi_wait();
  //DeActivate CS
  if(activateCS != NULL)activateCS(0);
  return readBuffer[0];
}

uint8_t readRegs(uint8_t reg, uint8_t len, uint8_t *buffer)
{
  uint8_t senData = reg;
  //Activate CS
  if(activateCS != NULL)activateCS(1);
  spi_write(&senData,1,NULL); //Send reg address
  spi_wait();
  readLen = len;//set the length for the read Data
  spi_read(len,&saveReadData);
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
  return readBuffer[0];
}
void stream_write(uint8_t * data, uint16_t index, uint8_t length)
{
	debugCntrTmp+=length;
	uint8_t asic_msb = (uint8_t)((index / 2) >> 4);
	uint8_t asic_lsb = ((index / 2) & 0x0F);

	writeReg(BMA4_RESERVED_REG_5B_ADDR, asic_lsb);
  writeReg(BMA4_RESERVED_REG_5C_ADDR, asic_msb);

  writeReg(BMA4_FEATURE_CONFIG_ADDR, data, length);
  return;
}


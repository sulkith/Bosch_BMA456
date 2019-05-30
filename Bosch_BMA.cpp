#include "Bosch_BMA.h"
#include "i2c/twi.h"
#include <string.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

//#define DEBUG_BMA

extern const uint8_t PROGMEM bma456_config_file[];

uint16_t debugCntrTmp = 0;
uint8_t readBuffer[TWI_BUFFER_LENGTH] = {0};
uint8_t readLen = 0;

//write to register
void writeReg(uint8_t reg, uint8_t val)
{
  uint8_t senData[2] = {reg,val};
  twi_write(BMA_ADDRESS,senData,2,NULL);
  twi_wait();
}
//Callback funtion for reading more than one byte
void saveReadData(uint8_t address, uint8_t *data)
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
  twi_write(BMA_ADDRESS,&senData,1,NULL); //Send reg address
  twi_wait();
  readLen = len;
  twi_read(BMA_ADDRESS,len,&saveReadData);
  twi_wait();
  return readBuffer[0];

}
void stream_write(uint8_t * data, uint16_t index, uint8_t length)
{
	debugCntrTmp+=length;
	uint8_t asic_msb = (uint8_t)((index / 2) >> 4);
	uint8_t asic_lsb = ((index / 2) & 0x0F);

	writeReg(BMA4_RESERVED_REG_5B_ADDR, asic_lsb);
  writeReg(BMA4_RESERVED_REG_5C_ADDR, asic_msb);

  uint8_t sendData[16+1];
  sendData[0] = BMA4_FEATURE_CONFIG_ADDR;
  for(uint8_t i = 0;i<length;++i)
  {
    sendData[i+1] = data[i];
  }
  twi_write(BMA_ADDRESS,sendData,length+1,NULL);
}
uint8_t writeConfigFile()
{
	const uint8_t chunkSize = 16;
  uint8_t config_stream_status = 0;
  uint16_t index = 0;

	writeReg(BMA4_POWER_CONF_ADDR,0x00);

	/* Wait for sensor time synchronization. Refer the data-sheet for
	more information*/
	_delay_ms(1);

		/* Disable config loading*/
		writeReg(BMA4_INIT_CTRL_ADDR, 0);
		/* Write the config stream */
		for (index = 0; index < BMA4_CONFIG_STREAM_SIZE; index += chunkSize)
		{
			//misusing the readBuffer as send Buffer here
			for(uint16_t i = 0; i<chunkSize; ++i)
			{
				readBuffer[i] = pgm_read_byte(&(bma456_config_file[index+i]));
			}
			stream_write((uint8_t*)(readBuffer), index, chunkSize);
#ifdef DEBUG_BMA
			_delay_ms(10);//To keep the slow logic analyzer from freaking out
#endif /*DEBUG_BMA*/
		}

		/* Enable config loading and FIFO mode */
    writeReg(BMA4_INIT_CTRL_ADDR, 1);
		/* Wait till ASIC is initialized. Refer the data-sheet for
		more information*/
		 _delay_ms(150);

		/* Read the status of config stream operation */
    config_stream_status = readReg(BMA4_INTERNAL_STAT, 1);

		writeReg(BMA4_POWER_CONF_ADDR,0x01);
    return config_stream_status;
}
void Bosch_BMA::init()
{

	writeReg(BMA4_CMD_ADDR,0xB6);//soft reset
	_delay_ms(500);

  InterruptState = writeConfigFile();

	//0x40 --> 0xAC
	writeReg(BMA4_ACCEL_CONFIG_ADDR,0xAC); //SamplingRate 1,6KHz, Averaging 4 Samples, Continous Filter
	//0x41 --> 0x01
	writeReg(BMA4_ACCEL_RANGE_ADDR,0x01); //Range +-4g

	//read 0x7D
	uint8_t temp7d = readAddress(BMA4_POWER_CTRL_ADDR);
	temp7d |= 0x04;
	writeAddress(BMA4_POWER_CTRL_ADDR, temp7d);
	writeReg(BMA4_POWER_CONF_ADDR,0x00);
	//set 0x04
	//writeback 0x7D
  //writeReg(0x59,0x01);
  //BMA_I2C.writeAddress(0x59, 0x01);//iniend

  //writeReg(0x7C,0x00);
  //BMA_I2C.writeAddress(0x7C, 0x00);//powerup*/
  //BMA_I2C.writeAddress(0x7D, 0x04);
  //BMA_I2C.writeAddress(0x40, 0x17);
  //BMA_I2C.writeAddress(0x7C, 0x03);
	debugCntr = debugCntrTmp;

}

void Bosch_BMA::writeAddress(uint8_t addr, uint8_t value)
{
	writeReg(addr, value);
}
uint8_t Bosch_BMA::readAddress(uint8_t addr)
{
  return readReg(addr, 1);//BMA_I2C.readAddress(addr);
}

uint8_t Bosch_BMA::getChipID()
{
  return readReg(BMA4_CHIP_ID, 1);//BMA_I2C.readAddress(0x00);
}
uint8_t Bosch_BMA::getInternalState()
{
	return readReg(BMA4_INTERNAL_STAT, 1);
}
uint32_t Bosch_BMA::getSensortime()
{
  uint8_t data[3] = {0};
  //BMA_I2C.readAddress(0x1A,3,data);

  return ((uint32_t)data[2]) + ((uint32_t)data[1])*256 + ((uint32_t)data[0])*256*256;
}
void Bosch_BMA::getInternalConfig(uint8_t *data)
{
	const uint8_t len =64;//from Datasheet
	uint8_t senData = BMA4_FEATURE_CONFIG_ADDR;
	twi_write(BMA_ADDRESS,&senData,1,NULL); //Send reg address
	twi_wait();
	readLen = len;
	twi_read(BMA_ADDRESS,len,&saveReadData);
	for(uint8_t i = 0;i<len;++i)
	{
		data[i] = readBuffer[i];
	}
	twi_wait();
}
void Bosch_BMA::writeInternalConfig(uint8_t *data)
{
	const uint8_t len =64;//from Datasheet
	uint8_t sendData[len+1];
	sendData[0] = BMA4_FEATURE_CONFIG_ADDR;
	for(uint8_t i = 0;i<len;++i)
	{
		sendData[i+1] = data[i];
	}
	twi_write(BMA_ADDRESS,sendData,len+1,NULL); //send Data
	twi_wait();
}

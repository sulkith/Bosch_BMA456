#include "Bosch_BMA.h"
#include "i2c/twi.h"
#include <string.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "bus_adap.h"

//#define DEBUG_BMA

//extern const uint8_t PROGMEM bma456_config_file[];
extern const uint8_t get_bma456_config_file(uint16_t i);

uint8_t writeConfigFile()
{
	const uint8_t chunkSize = 16;
  uint8_t config_stream_status = 0;
  uint16_t index = 0;
	uint8_t chunkBuffer[chunkSize+2] = {0};

	writeReg(BMA4_POWER_CONF_ADDR,0x00);

	/* Wait for sensor time synchronization. Refer the data-sheet for
	more information*/
	_delay_ms(10);

		/* Disable config loading*/
		writeReg(BMA4_INIT_CTRL_ADDR, 0);
		/* Write the config stream */
		for (index = 0; index < BMA4_CONFIG_STREAM_SIZE; index += chunkSize)
		{
			for(uint16_t i = 0; i<chunkSize; ++i)
			{
				chunkBuffer[i] = get_bma456_config_file(index+i);
			}
			stream_write(chunkBuffer, index, chunkSize);
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

	initComDriver();
	writeReg(BMA4_CMD_ADDR,0xB6);//soft reset
	_delay_ms(500);
	initComDriver();
	getChipID();//Test Code to see if the Bus is working in the Logic analyzer
	getChipID();
	getChipID();

  InterruptState = writeConfigFile();
	getChipID();//Test Code to see if the Bus is working in the Logic analyzer

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

void Bosch_BMA::getInternalConfig(uint8_t *data)
{
  startInterruptConfig();
  for(uint8_t i = 0;i<InterruptConfigLenght;++i)
  {
    data[i] = InterruptConfig[i];
  }
}
void Bosch_BMA::writeInternalConfig(uint8_t *data)
{
  for(uint8_t i = 0;i<InterruptConfigLenght;++i)
  {
    InterruptConfig[i] = data[i];
  }
}
int16_t Bosch_BMA::get_X_Accel()
{
  uint8_t databuffer[2];
  readRegs(BMA4_X_AXIS,2,databuffer);
  return (int16_t)((databuffer[1])<<8|databuffer[0]);
}
int16_t Bosch_BMA::get_Y_Accel()
{
  uint8_t databuffer[2];
  readRegs(BMA4_Y_AXIS,2,databuffer);
  return (int16_t)((databuffer[1])<<8|databuffer[0]);
}
int16_t Bosch_BMA::get_Z_Accel()
{
  uint8_t databuffer[2];
  readRegs(BMA4_Z_AXIS,2,databuffer);
  return (int16_t)((databuffer[1])<<8|databuffer[0]);
}
void Bosch_BMA::startInterruptConfig()
{
  readRegs(BMA4_FEATURE_CONFIG_ADDR,InterruptConfigLenght,InterruptConfig);
  return;
}

void Bosch_BMA::writeInterruptConfig()
{
  writeReg(BMA4_FEATURE_CONFIG_ADDR, InterruptConfig, InterruptConfigLenght);
  return;
}

void Bosch_BMA::setMotionDetection(uint16_t threshhold, uint8_t delay, uint8_t axis, uint8_t nomotion)
{
	InterruptConfig[0] = threshhold&0xFF;
	InterruptConfig[1] = (threshhold >> 8 )&0x07;
	if(nomotion > 0) InterruptConfig[1] |= 0x08;
	InterruptConfig[2] = delay & 0xFF;
	InterruptConfig[3] = (delay >> 8) & 0x1F;
	InterruptConfig[3] |= axis << 5;
	//intConf[0] = 0x10;//7mg threshhold
	//intConf[1] = 0x00;//select anymotion
	//intConf[2] = 0x05;//duration 100ms
	//intConf[3] = 0x80;//enable for all axis
}
void Bosch_BMA::setTapDetection(uint8_t singleTap, uint8_t strength, uint8_t enable)
{
  InterruptConfig[0x38]=enable&0x01;
  InterruptConfig[0x38]|=(strength&0x07)<<1;
  InterruptConfig[0x38]|=(singleTap&0x01)<<4;
}
void Bosch_BMA::setWristTiltFunction(uint8_t enable)
{
  InterruptConfig[0x3A]=enable&0x01;
}
void Bosch_BMA::setConfigID(uint8_t confID)
{
  InterruptConfig[0x3C]=confID;
}
void Bosch_BMA::setAxisMapping(uint8_t x, uint8_t x_invert, uint8_t y, uint8_t y_invert, uint8_t z, uint8_t z_invert)
{
  //map_x_axis = 0
  //map_x_axis_sign = 1
  //map_y_axis = 1
  //map_y_axis_sign = 0
  //map_z_axis = 2
  //map_z_axis_sign = 1
  //                        sz  z sy  y sx  x
  //const uint16_t axisW =0b 1 10  1 01  1 00 //compiler doesnt support bit defines :-(
  //0b 1 1010 1100 = 0x1AC
  //const uint16_t axisW = 0x1AC;
  InterruptConfig[0x3E] = x&0x03;
  InterruptConfig[0x3E] |= (x_invert&0x01)<<2;
  InterruptConfig[0x3E] |= (y&0x03)<<3;
  InterruptConfig[0x3E] |= (y_invert&0x01)<<5;
  InterruptConfig[0x3E] |= (z&0x03)<<6;
  InterruptConfig[0x3F] = z_invert&0x01;
}

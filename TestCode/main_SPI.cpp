#include <stdint.h>
#include <string.h>
#include <util/delay.h>
#include <avr/io.h>
#include "TestCode.h"
#include "../spi_adap.h"
#include "../bus_adap.h"
#include "../spi/spi.h"

void setCS(uint8_t t){

	if(t==0)
		PORTB |= _BV(PB2);
	else

		PORTB &= ~_BV(PB2);
}
void showLEDs(uint8_t number, uint8_t row)
{
	uint8_t value_row_temp = (1<<row);
	uint8_t value_row = (value_row_temp&0x03) |(value_row_temp&0b1100)<<6;
	PORTD = (value_row) | (~number <<2);
}
//Initialize SPI Master Device
void spi_init_master (void)
{
	DDRB |= (1<<5)|(1<<3);              //Set MOSI, SCK as Output
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0); //Enable SPI, Set as Master
	//Prescaler: Fosc/16, Enable Interrupts
}
//Function to send and receive data
unsigned char spi_tranceiver (unsigned char data)
{
	SPDR = data;                       //Load data into the buffer
	while(!(SPSR & (1<<SPIF) ));       //Wait until transmission complete
	return(SPDR);                      //Return received data
}
uint8_t readbuffer[10];
void readData(uint8_t *data)
{
	for(uint8_t i=0;i<10;++i)
	{
		readbuffer[i]=data[i];
	}
}
void ASSERT(uint8_t condition, uint8_t ID)
{
	if(!(condition))
	{
		showLEDs(0x0f&ID,0);
		while(1);
	}
}
int main(){
	_delay_ms(500);
	showLEDs(2,1);

	DDRD = 0xFF;

	spi_init();

	set_SPI_activate_CS(&setCS);

	initComDriver();

//	uint8_t test1 = readReg(0x00,1);
//	showLEDs(0x0f&test1,2);

	_delay_ms(1);

	ASSERT(readReg(0x00,1)==0x16,1);
	writeReg(0x73,0xAA);
	ASSERT(readReg(0x73,1)==0xAA,2);
	uint8_t writeArr[]{0xBB,0xCC};
	writeReg(0x71,writeArr,2);
	ASSERT(readReg(0x71,1)==0xBB,3);
	ASSERT(readReg(0x72,1)==0xCC,4);

	
	showLEDs(3,1);
	init_BMA();
	uint8_t test3 = readReg(0x2A,1);
	ASSERT(readReg(0x2A,1)==0x01,test3);
	showLEDs(4,1);


	showLEDs(8,1);

	while(1){
		if((test_BMA())!=0)showLEDs(15,1);
	}
}

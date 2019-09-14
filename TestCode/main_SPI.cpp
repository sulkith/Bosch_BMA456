#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include "TestCode.h"
#include "../spi_adap.h"
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

int main(){
	_delay_ms(500);
	DDRD = 0xFF;
	showLEDs(1,1);
	DDRB |= _BV(PB2);
	spi_init_master();

	_delay_ms(1);//Toogle CSB Pin to get the BMA into SPI mode
	setCS(1);
	_delay_ms(1);
	setCS(0);
	_delay_ms(1);

	setCS(1);
	_delay_ms(1);
	spi_tranceiver(0x80);
	spi_tranceiver(0xFF);//Dummy Byte
	uint8_t test = 0;
	while((spi_tranceiver(0xFF))==0)
	{
		setCS(0);
		_delay_ms(1);
		setCS(1);
		spi_tranceiver(0x80);
		test ++;
	}
	showLEDs(test&0x0f,1);
	if(test==0)
	showLEDs(0x0f,2);
	while(1);
	showLEDs(2,1);
	set_SPI_activate_CS(&setCS);
	showLEDs(3,1);
	init_BMA();
	showLEDs(4,1);

	while(1){
		if(test_BMA()!=0)showLEDs(15,1);
	}
}

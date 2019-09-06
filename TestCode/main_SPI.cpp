#include <stdint.h>
#include <avr/io.h>
#include "TestCode.h"
#include "../spi_adap.h"

void setCS(uint8_t t){

	if(t>0)
		PORTB |= _BV(PB2);
	else

		PORTB &= ~_BV(PB2);
}

int main(){
	DDRB = _BV(PB2);
	set_SPI_activate_CS(&setCS);
	init_BMA();
}

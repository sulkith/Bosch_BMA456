#include <stdint.h>
#include "TestCode.h"
#include "../spi_adap.h"

void setCS(uint8_t t){

}

int main(){
	set_SPI_activate_CS(&setCS);
	init_BMA();
}

#include <stdint.h>
#include "../Bosch_BMA.h"

Bosch_BMA bma;
extern void showLEDs(uint8_t number, uint8_t row);

void init_BMA()
{
	bma.init();
	bma.getChipID();
	bma.getInternalState();
	bma.startInterruptConfig();
	bma.setTapDetection(0, 3, 1);
	bma.setMotionDetection(10,5,7,1);
	bma.setConfigID(1);
	bma.writeInterruptConfig();
	bma.writeAddress(0x00,0xb0);
	bma.writeAddress(0x56,0xEE);
	bma.getInternalState();
	bma.readAddress(0x1C);
}
uint8_t test_BMA()
{
	bma.getInternalState();
	return bma.getChipID();

}

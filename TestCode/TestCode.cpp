#include "../Bosch_BMA.h"

Bosch_BMA bma;

void init_BMA()
{
	bma.getChipID();
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
	while(1){
		bma.getInternalState();
		bma.readAddress(0x1C);
	}
}

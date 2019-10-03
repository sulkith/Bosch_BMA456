#include <iostream>
#include "../Bosch_BMA456_defs.h"
extern volatile const uint8_t bma456_config_file[];
int main()
{
	for(int i=0;i<BMA4_CONFIG_STREAM_SIZE;++i)
	{
		std::cout << static_cast<int>(bma456_config_file[i]) << std::endl;
	}
}

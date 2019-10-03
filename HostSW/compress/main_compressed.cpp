#include <iostream>
#include "../Bosch_BMA456_defs.h"
extern volatile const uint8_t bma456_config_file[];
uint8_t get(int i)
{
	if(i<4528)//381-4 --> 377*3+1
		return bma456_config_file[i];
	return bma456_config_file[4528+(i%4)];
	//6144 - (4528 + 4) -->  6144 - 4532 --> 1612

}
int main()
{
	for(int i=0;i<BMA4_CONFIG_STREAM_SIZE;++i)
	{
		std::cout << static_cast<int>(get(i)) << std::endl;
	}
}

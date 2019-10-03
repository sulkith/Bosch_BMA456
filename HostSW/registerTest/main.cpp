#include <iostream>

uint8_t InterruptConfig[255];
void setAxisMapping(uint8_t x, uint8_t x_invert, uint8_t y, uint8_t y_invert, uint8_t z, uint8_t z_invert)
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
  InterruptConfig[0x3F] |= z_invert&0x01;
}
int main()
{
 	setAxisMapping(0,0,1,1,2,1);
	std::cout << static_cast<int>(InterruptConfig[0x3E]) << std::endl;	
	std::cout << static_cast<int>(InterruptConfig[0x3F]) << std::endl;	
}

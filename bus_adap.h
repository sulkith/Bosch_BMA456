#ifndef __BUS_ADAP_H__
#define __BUS_ADAP_H__

extern void writeReg(uint8_t reg, uint8_t val);
extern void writeReg(uint8_t reg, uint8_t *val, uint8_t len);
extern uint8_t readReg(uint8_t reg, uint8_t len);

extern uint8_t readRegs(uint8_t reg, uint8_t len, uint8_t *buffer);
extern void stream_write(uint8_t * data, uint16_t index, uint8_t length);
extern void initComDriver();

#endif //__BUS_ADAP_H__

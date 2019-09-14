# Makefile for programming the ATtiny85
# modified the one generated by CrossPack

DEVICE      = atmega328p
#CLOCK      = 8000000
CLOCK      = 1000000
PROGRAMMER = -c buspirate 
OBJECTS     = Bosch_BMA.o Bosch_BMA456_config_file.o TestCode/TestCode.o
OBJECTS_TWI = TestCode/main.o i2c_adap.o i2c/twi.o
OBJECTS_SPI = TestCode/main_SPI.o spi_adap.o spi/spi.o
PORT = /dev/ttyUSB0
# for ATTiny85
# see http://www.engbedded.com/fusecalc/
#FUSES       = -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xff:m 
FUSES       = -U lfuse:w:0x62:m -U hfuse:w:0xD9:m -U efuse:w:0xFF:m 

# Tune the lines below only if you know what you are doing:
AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE) -P $(PORT)
COMPILE = avr-g++ -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

# symbolic targets:
all:	main.hex main_SPI.hex

.c.o:
	$(COMPILE) -c $< -o $@

.cpp.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:main.hex:i
flash_SPI:	all
	$(AVRDUDE) -U flash:w:main_SPI.hex:i

test:	all flash
	gtkterm

fuse:
	$(AVRDUDE) $(FUSES)

# Xcode uses the Makefile targets "", "clean" and "install"
install: flash fuse

# if you use a bootloader, change the command below appropriately:
load: all
	bootloadHID main.hex

clean:
	rm -f main.hex main.elf main_SPI.elf main_SPI.hex $(OBJECTS) $(OBJECTS_TWI) $(OBJECTS_SPI)

# file targets:
main.elf: $(OBJECTS) $(OBJECTS_TWI)
	$(COMPILE) -o main.elf $(OBJECTS) $(OBJECTS_TWI)

main_SPI.elf: $(OBJECTS) $(OBJECTS_SPI)
	$(COMPILE) -o main_SPI.elf $(OBJECTS) $(OBJECTS_SPI)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.
main_SPI.hex: main_SPI.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main_SPI.elf main_SPI.hex
	avr-size --format=avr --mcu=$(DEVICE) main_SPI.elf

# Targets for code debugging and analysis:
disasm:	main.elf
	avr-objdump -d main.elf

cpp:
	$(COMPILE) -E main.c

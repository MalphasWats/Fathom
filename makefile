#
# Makefile template for ATMega1284p
#

TARGET      = fathom

GLYPHLIB    = ../glyphlib
VPATH       = $(GLYPHLIB)

LIB        = GLYPH.o tilemap-engine.o
BUILD      = fathom.o main.o

OBJECTS    =  $(LIB) $(BUILD)

DEVICE     = atmega1284p
PROGRAMMER = -cstk500v2 -P/dev/ttyACM0 -B0.5

C_FLAGS    = -Wl,--gc-sections -Wl,--relax -ffunction-sections -fdata-sections -fno-inline-small-functions -fpack-struct -fshort-enums

# fuse settings:
# use http://www.engbedded.com/fusecalc
FUSES      = -U lfuse:w:0xfe:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m  # External Xtal

AVRDUDE = avrdude $(PROGRAMMER) -p$(DEVICE)
COMPILE = avr-gcc -Wall -O3 -mmcu=$(DEVICE) $(C_FLAGS) -I$(GLYPHLIB)

# symbolic targets:
all:	$(TARGET).hex

.c.o:
	$(COMPILE) -c $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:$(TARGET).hex:i

fuse:
	$(AVRDUDE) $(FUSES)

clean:
	rm -f $(TARGET).hex $(TARGET).elf $(OBJECTS)

size: $(TARGET).elf
	avr-size --format=avr --mcu=$(DEVICE) $(TARGET).elf
	avr-nm -S -td --size-sort $(TARGET).elf

# file targets:
$(TARGET).elf: $(OBJECTS)
	$(COMPILE) -o $(TARGET).elf $(OBJECTS)

$(TARGET).hex: $(TARGET).elf
	rm -f $(TARGET).hex
	avr-objcopy -j .text -j .data -O ihex $(TARGET).elf $(TARGET).hex

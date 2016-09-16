CROSS_COMPILE = /usr/local/arm/arm-2009q3/bin/arm-none-linux-gnueabi-

AS	= $(CROSS_COMPILE)as
LD	= $(CROSS_COMPILE)ld
CC	= $(CROSS_COMPILE)gcc
CPP	= $(CC) -E
AR	= $(CROSS_COMPILE)ar
NM	= $(CROSS_COMPILE)nm
LDR	= $(CROSS_COMPILE)ldr
STRIP	= $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
RANLIB	= $(CROSS_COMPILE)RANLIB


ALL = led.bl1

all : $(ALL)

led.bin:start.s led.c
	$(CC) -nostdlib -c -o start.o start.s
	$(CC) -nostdlib -c -o led.o led.c
	$(LD) start.o led.o -o led_elf
	$(OBJCOPY) -O binary -S led_elf led.bin

led.bl1 : led.bin
	../../../tools/mkbl1/mkbl1 $< $@

clean:
	@rm -rf led_elf led.bin *.o led.bl1


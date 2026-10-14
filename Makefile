
CC       = arm-none-eabi-gcc
OBJCOPY  = arm-none-eabi-objcopy
SIZE     = arm-none-eabi-size
OPENOCD  = openocd

TARGET   = firmware
MCUFLAGS = -mcpu=cortex-m3 -mthumb

CFLAGS = $(MCUFLAGS) \
         -std=c11 \
         -Wall -Wextra \
         -ffreestanding \
         -fno-unwind-tables \
         -fno-asynchronous-unwind-tables \
         -O0

LDFLAGS = $(MCUFLAGS) \
          -nostdlib \
          -T stm32f103.ld \
          -Wl,-Map=$(TARGET).map

OBJECTS = startup.o main.o

.PHONY: all flash clean

all: $(TARGET).elf $(TARGET).bin

startup.o: startup.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJECTS) stm32f103.ld
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	$(SIZE) $@

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

flash: $(TARGET).elf
	sudo $(OPENOCD) \
		-f interface/stlink.cfg \
		-f target/stm32f1x.cfg \
		-c "program $(TARGET).elf verify reset exit"

clean:
	rm -f $(OBJECTS) $(TARGET).elf $(TARGET).bin $(TARGET).map

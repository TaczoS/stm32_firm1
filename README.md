# STM32 Bare metal 

My first bare metal firmware project for the STM32F103C8T6.


compile the main.c file using 
"
arm-none-eabi-gcc \
  -mcpu=cortex-m3 \
  -mthumb \
  -std=c11 \
  -Wall -Wextra \
  -ffreestanding \
  -c main.c -o main.o
"
compile the startup.c file using 
" 
arm-none-eabi-gcc \
  -mcpu=cortex-m3 \
  -mthumb \
  -std=c11 \
  -Wall -Wextra \
  -ffreestanding \
  -fno-unwind-tables \
  -fno-asynchronous-unwind-tables \
  -c startup.c -o startup.o
"

to compile the linker file stm32f103.c run

"
arm-none-eabi-gcc \
  -mcpu=cortex-m3 \
  -mthumb \
  -nostdlib \
  -T stm32f103.ld \
  -Wl,-Map=firmware.map \
  startup.o main.o \
  -o firmware.elf
"

or just run the Makefile 

"
    make clean
    make 
    make flash
"

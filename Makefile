output.hex : output.elf
	arm-none-eabi-objcopy -O ihex -S -R .comment output.elf output.hex
output.elf : main.o startup.o
	arm-none-eabi-ld -T STM32F103C8Tx_FLASH.ld startup.o main.o -L /mingw64/arm-none-eabi/lib/ -L /mingw64/lib/gcc/arm-none-eabi/12.2.0/ -o output.elf
startup.o : startup_stm32f103xb.s
	arm-none-eabi-as -mcpu=cortex-m3 -mthumb -o startup.o startup_stm32f103xb.s
main.o : main.c
	arm-none-eabi-gcc -g -mcpu=cortex-m3 -mthumb main.c -nostartfiles -c -o main.o
clean:
	-rm -rf main.o startup.o output.elf output.hex
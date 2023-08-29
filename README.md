# stm32f103c8t6_mini_code
硬件--stm32f103c8t6最小系统板
环境--Windows + MSYS2
工具--pacman -S mingw-w64-x86_64-arm-none-eabi-gcc
代码：
    |-- main.c //C文件--实现点灯
    |-- Makefile //
    |-- README.md //
    |-- startup_stm32f103xb.s //启动汇编，来自stm32cubemx生成
    |-- STM32F103C8Tx_FLASH.ld //链接脚本，来自stm32cubemx生成
    |-- tempcode //备份代码
编译方式：
    make
下载方式：
   st-flash.exe --format ihex write output.hex

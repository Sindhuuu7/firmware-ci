.RECIPEPREFIX = >
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size
CFLAGS  = -mcpu=cortex-m3 -mthumb -Os -Wall -Wextra -Werror -ffreestanding -Iinclude
SRCS    = src/main.c src/sensor.c src/led.c src/startup.c

all: build/firmware.bin

build:
> mkdir -p build

build/firmware.elf: $(SRCS) linker.ld | build
> $(CC) $(CFLAGS) $(SRCS) -T linker.ld -nostdlib -o $@

build/firmware.bin: build/firmware.elf
> $(OBJCOPY) -O binary $< $@

analyze:
> cppcheck --enable=warning,style,performance,portability --error-exitcode=1 --inline-suppr -Iinclude src

test: | build
> gcc -Wall -Wextra -Iinclude tests/test_main.c src/sensor.c src/led.c -o build/test_runner
> ./build/test_runner

size: build/firmware.elf
> $(SIZE) $<

clean:
> rm -f build/*

.PHONY: all analyze test size clean

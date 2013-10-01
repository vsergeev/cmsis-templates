# Project Name
PROJECT=blink
# List of the objects files to be made
OBJECTS=core/core_cm3.o lpc13xx/system_LPC13xx.o startup.o main.o
# Linker script
LINKER_SCRIPT = lpc1313.dld

OPT = s
DEBUG =
INCLUDES = -Icore/ -Ilpc13xx/
THUMB =

#  Compiler Options
GCFLAGS = -Wall -Wextra -fno-common -mcpu=cortex-m3 -mthumb -O$(OPT) $(DEBUG)
GCFLAGS += -Wcast-align -Wcast-qual -Wimplicit -Wpointer-arith -Wswitch
GCFLAGS += -Wredundant-decls -Wreturn-type -Wshadow -Wunused $(INCLUDES)
LDFLAGS = $(THUMB) -O$(OPT) -nostartfiles -Wl,-Map=$(PROJECT).map -T$(LINKER_SCRIPT) -nostdlib
ASFLAGS = -ahls -mcpu=cortex-m3 -mthumb

#  Compiler/Assembler/Linker Paths
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
REMOVE = rm -f
SIZE = arm-none-eabi-size

#########################################################################

all: $(PROJECT).hex $(PROJECT).bin

$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) -O binary -S $(PROJECT).elf $(PROJECT).bin

$(PROJECT).hex: $(PROJECT).elf
	$(OBJCOPY) -R .stack -R .bss -O ihex $(PROJECT).elf $(PROJECT).hex

$(PROJECT).elf: $(OBJECTS) $(LINKER_SCRIPT)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(PROJECT).elf

stats: $(PROJECT).elf
	$(SIZE) $(PROJECT).elf

clean:
	$(REMOVE) $(OBJECTS)
	$(REMOVE) $(PROJECT).hex
	$(REMOVE) $(PROJECT).elf
	$(REMOVE) $(PROJECT).map
	$(REMOVE) $(PROJECT).bin

#########################################################################

%.o : %.c
	$(CC) $(GCFLAGS) -c $< -o $@

#########################################################################


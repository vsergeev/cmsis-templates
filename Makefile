# Project Name
PROJECT = blink
# List of the objects files to be made
OBJECTS = lpc13xx/system_LPC13xx.o startup.o main.o
# Linker script
LINKER_SCRIPT = lpc1313.dld

OPT = s
DEBUG =
INCLUDES = -Icore/ -Ilpc13xx/
THUMB =

# Compiler Options
GCFLAGS = -Wall -Wextra -fno-common -mcpu=cortex-m3 -mthumb -O$(OPT) $(DEBUG)
GCFLAGS += -Wcast-align -Wcast-qual -Wimplicit -Wpointer-arith -Wswitch
GCFLAGS += -Wredundant-decls -Wreturn-type -Wshadow -Wunused $(INCLUDES)
LDFLAGS = $(THUMB) -O$(OPT) -nostartfiles -Wl,-Map=$(PROJECT).map -T$(LINKER_SCRIPT) -nostdlib
ASFLAGS = -ahls -mcpu=cortex-m3 -mthumb

# Compiler/Assembler/Linker Paths
CROSS = arm-none-eabi-
CC = $(CROSS)gcc
AS = $(CROSS)as
LD = $(CROSS)ld
OBJDUMP = $(CROSS)objdump
OBJCOPY = $(CROSS)objcopy
SIZE = $(CROSS)size
REMOVE = rm -f

#########################################################################

all: $(PROJECT).hex $(PROJECT).bin stats

$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) -O binary -S $(PROJECT).elf $(PROJECT).bin

$(PROJECT).hex: $(PROJECT).elf
	$(OBJCOPY) -R .stack -R .bss -O ihex $(PROJECT).elf $(PROJECT).hex

$(PROJECT).elf: $(OBJECTS) $(LINKER_SCRIPT)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(PROJECT).elf

stats: $(PROJECT).elf
	$(OBJDUMP) -th $(PROJECT).elf
	$(SIZE) $(PROJECT).elf

clean:
	$(REMOVE) $(OBJECTS)
	$(REMOVE) $(PROJECT).elf
	$(REMOVE) $(PROJECT).hex
	$(REMOVE) $(PROJECT).bin
	$(REMOVE) $(PROJECT).map

#########################################################################

%.o : %.c
	$(CC) $(GCFLAGS) -c $< -o $@

#########################################################################


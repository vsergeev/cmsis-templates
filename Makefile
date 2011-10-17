#  Project Name
PROJECT=blink
#  List of the objects files to be made
OBJECTS=startup.o core_cm3.o system_LPC13xx.o main.o

OPTIMIZATION = s 
DEBUG =

#  Compiler Options
GCFLAGS = -Wall -Wextra -fno-common -mcpu=cortex-m3 -mthumb -O$(OPTIMIZATION) $(DEBUG)
GCFLAGS += -Wcast-align -Wcast-qual -Wimplicit -Wpointer-arith -Wswitch
GCFLAGS += -Wredundant-decls -Wreturn-type -Wshadow -Wunused 
LDFLAGS = $(THUMB) -O$(OPTIMIZATION) -nostartfiles -Wl,-Map=$(PROJECT).map -Tlpc1313.dld -nostdlib 
ASFLAGS = -ahls -mcpu=cortex-m3 -mthumb

#  Compiler/Assembler/Linker Paths
GCC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
REMOVE = rm -f
SIZE = arm-none-eabi-size

#########################################################################

all:: $(PROJECT).hex $(PROJECT).bin

$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) -O binary -S $(PROJECT).elf $(PROJECT).bin

$(PROJECT).hex: $(PROJECT).elf
	$(OBJCOPY) -R .stack -R .bss -O ihex $(PROJECT).elf $(PROJECT).hex

$(PROJECT).elf: $(OBJECTS) lpc1313.dld
	$(GCC) $(LDFLAGS) $(OBJECTS) -o $(PROJECT).elf

stats: $(PROJECT).elf
	$(SIZE) $(PROJECT).elf

clean:
	$(REMOVE) $(OBJECTS)
	$(REMOVE) $(PROJECT).hex
	$(REMOVE) $(PROJECT).elf
	$(REMOVE) $(PROJECT).map
	$(REMOVE) $(PROJECT).bin
	$(REMOVE) $(OBJECTS)
	$(REMOVE) $(PROJECT)_crt.lst

#########################################################################
#  Default rules to compile .c and .cpp file to .o
#  and assemble .s files to .o

.c.o :
	$(GCC) $(GCFLAGS) -c $<

.cpp.o :
	$(GCC) $(GCFLAGS) -c $<

.S.o :
	$(AS) $(ASFLAGS) -o $(PROJECT)_crt.o $< > $(PROJECT)_crt.lst

#########################################################################

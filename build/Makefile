#######################################################

TARGET = ProjectName

#######################################################

CC        = sdcc
OBJCOPY   = objcopy
CHFLASHER = ./chflasher/chflasher.py

#######################################################

# Adjust the XRAM location and size to leave space for the USB DMA buffers
# Buffer layout in XRAM:
# 0x0000 Ep0Buffer[8]
# 0x0040 Ep1Buffer[8]
# 0x0080 EP2Buffer[2*64]
#
# This takes a total of 256bytes, so there are 768 bytes left.
XRAM_SIZE = 0x0300
XRAM_LOC = 0x0100

# Select all *.c files from main and lib folder, and debug.c from Framework
# for some helper functions
C_FILES = $(wildcard ../lib/*.c) \
	$(wildcard ../*.c)

pre-flash:

# TODO Check size for different types CH551g, CH552g, CH553g, CH554g

ifndef FREQ_SYS
FREQ_SYS = 24000000
endif

ifndef XRAM_SIZE
XRAM_SIZE = 0x0400
endif

ifndef XRAM_LOC
XRAM_LOC = 0x0000
endif

ifndef CODE_SIZE
CODE_SIZE = 0x2800
endif

ROOT_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# C Flags
CFLAGS := -V -mmcs51 --model-small \
	--xram-size $(XRAM_SIZE) --xram-loc $(XRAM_LOC) \
	--code-size $(CODE_SIZE) \
	-I$(ROOT_DIR)../framework/include -DFREQ_SYS=$(FREQ_SYS) \
	$(EXTRA_FLAGS)

LFLAGS := $(CFLAGS)

RELS := $(C_FILES:.c=.rel)

# Print macro for debugging
print-%  : ; @echo $* = $($*)

%.rel : %.c
	@echo "--------------------------------------------------------------------------------"
	@echo "Compile $<"
	@echo "--------------------------------------------------------------------------------"
	$(CC) -c $(CFLAGS) $<


# Note: SDCC will dump all of the temporary files into this one, so strip the paths from RELS
# For now, get around this by stripping the paths off of the RELS list.

$(TARGET).ihx: $(RELS)
	$(CC) $(notdir $(RELS)) $(LFLAGS) -o $(TARGET).ihx

$(TARGET).bin: ../usb-descriptor/usb-descriptor.h $(TARGET).ihx
	$(OBJCOPY) -I ihex -O binary $(TARGET).ihx $(TARGET).bin
	@echo "################################################################################"
	@echo "Programm size `du -k -b "$(TARGET).bin" | cut -f1` Bytes"
	@echo "################################################################################"

../usb-descriptor/usb-descriptor.h: ../usb-descriptor/usb-descriptor.json
	../usb-descriptor/generate.py

flash: $(TARGET).bin pre-flash
	@echo "Flash"
	@echo "################################################################################"
	../test-tools/reset-over-usb.py
	$(CHFLASHER) $(TARGET).bin

.DEFAULT_GOAL := all
all: $(TARGET).bin


clean:
	rm -f \
	$(notdir $(RELS:.rel=.asm)) \
	$(notdir $(RELS:.rel=.lst)) \
	$(notdir $(RELS:.rel=.mem)) \
	$(notdir $(RELS:.rel=.rel)) \
	$(notdir $(RELS:.rel=.rst)) \
	$(notdir $(RELS:.rel=.sym)) \
	$(notdir $(RELS:.rel=.adb)) \
	../usb-descriptor/usb-descriptor.h \
	$(TARGET).lk \
	$(TARGET).map \
	$(TARGET).mem \
	$(TARGET).ihx \
	$(TARGET).hex \
	$(TARGET).bin



## Download framework
framework:
	# Files are included in this repository, with minimized code, documented in
	# english and optimized
	# git clone https://github.com/Blinkinlabs/ch554_sdcc.git ../framework
	git clone https://github.com/atc1441/chflasher.git chflasher




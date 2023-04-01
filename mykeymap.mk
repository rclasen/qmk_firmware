# included from keymap/Makefile
#
# need
# TOP=relative topdir
# BOARD=keyboard dir/name
# MAP=keymap dir/name
# FLASH=target for flashing the firmware
# NAMES=list of physical boards

NAMES	?= default

build:
	make -C $(TOP) $(BOARD):$(MAP)

flash: $(FLASH)

eeleft	:= $(patsubst %,$(FLASH)-split-%,$(filter %left,$(NAMES)))
eeleft: $(eeleft)
eeright	:= $(patsubst %,$(FLASH)-split-%,$(filter %right,$(NAMES)))
eeright: $(eeright)
eehand: eeleft eeright

all	:= $(FLASH) $(eeleft) $(eeright)
$(all):
	@echo "************ flashing $(BOARD):$(MAP):$@"
	make -C $(TOP) $(BOARD):$(MAP):$@
	date > .$@

stamps := $(patsubst %,.%,$(all))
pending: $(stamps)
$(stamps): .%: rules.mk config.h keymap.c
	@echo "************ $(BOARD): $@"


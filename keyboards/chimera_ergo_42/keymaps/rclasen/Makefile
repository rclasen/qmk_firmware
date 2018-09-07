
TOP	:= ../../../..
BOARD	:= chimera_ergo_42
MAP	:= rclasen
FLASH	:= avrdude

build:
	make -C $(TOP) $(BOARD):$(MAP)

$(FLASH) flash:
	make -C $(TOP) $(BOARD):$(MAP):$(FLASH)

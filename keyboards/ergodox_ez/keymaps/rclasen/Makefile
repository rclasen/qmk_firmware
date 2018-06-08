
TOP	:= ../../../..
BOARD	:= ergodox_ez
MAP	:= rclasen
FLASH	:= teensy

build:
	make -C $(TOP) $(BOARD):$(MAP)

$(FLASH) flash:
	make -C $(TOP) $(BOARD):$(MAP):$(FLASH)

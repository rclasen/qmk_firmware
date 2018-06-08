
TOP	:= ../../../..
BOARD	:= myatreus
MAP	:= default
FLASH	:= teensy

build:
	make -C $(TOP) $(BOARD):$(MAP)

$(FLASH) flash:
	make -C $(TOP) $(BOARD):$(MAP):$(FLASH)

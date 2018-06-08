
TOP	:= ../../../..
BOARD	:= mydiverge
MAP	:= default
FLASH	:= avrdude

build:
	make -C $(TOP) $(BOARD):$(MAP)

$(FLASH) flash:
	make -C $(TOP) $(BOARD):$(MAP):$(FLASH)

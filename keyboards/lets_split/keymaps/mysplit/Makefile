
TOP	:= ../../../..
BOARD	:= lets_split
MAP	:= mysplit
FLASH	:= avrdude

build:
	make -C $(TOP) $(BOARD):$(MAP)

$(FLASH) flash:
	make -C $(TOP) $(BOARD):$(MAP):$(FLASH)

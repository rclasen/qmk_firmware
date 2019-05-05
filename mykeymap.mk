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

pending	:= $(patsubst %,.flash-%,$(NAMES))
pending: $(pending)
$(pending): .flash-%: rules.mk config.h keymap.c
	@echo "************ $(BOARD): $@"

flash	:= $(patsubst %,flash-%,$(NAMES))
$(FLASH) flash: $(flash)
$(flash): flash-%: build
	@echo "************ flashing $(BOARD): $@"
	make -C $(TOP) $(BOARD):$(MAP):$(FLASH)
	date > .$@

eeleft	:= $(patsubst %,eeleft-%,$(filter %left,$(NAMES)))
eeleft: $(eeleft)
eeright	:= $(patsubst %,eeright-%,$(filter %right,$(NAMES)))
eeright: $(eeright)
eehand: eeleft eeright

splitdir	:= $(TOP)/keyboards/lets_split

$(eeleft): eeleft-%:
	@echo "************ eehand left $(BOARD): $@"
	@printf "Detecting USB port, reset your controller now."; \
		ls /dev/tty* > /tmp/1; \
		while [ -z $$USB ]; do \
			sleep 0.5; \
			printf "."; \
			ls /dev/tty* > /tmp/2; \
			USB=`comm -13 /tmp/1 /tmp/2 | grep -o '/dev/tty.*'`; \
			mv /tmp/2 /tmp/1; \
		done; \
		echo ""; \
		echo "Detected controller on USB port at $$USB"; \
		if grep -q -s 'MINGW\|MSYS' /proc/version; then \
			USB=`echo "$$USB" | perl -pne 's/\/dev\/ttyS(\d+)/COM.($$1+1)/e'`; \
			echo "Remapped MSYS2 USB port to $$USB"; \
		fi; \
		sleep 1; \
		avrdude -p atmega32u4 -P $$USB -c avr109 -U eeprom:w:$(splitdir)/eeprom-lefthand.eep

$(eeright): eeright-%:
	@echo "************ eehand right $(BOARD): $@"
	@printf "Detecting USB port, reset your controller now."; \
		ls /dev/tty* > /tmp/1; \
		while [ -z $$USB ]; do \
			sleep 0.5; \
			printf "."; \
			ls /dev/tty* > /tmp/2; \
			USB=`comm -13 /tmp/1 /tmp/2 | grep -o '/dev/tty.*'`; \
			mv /tmp/2 /tmp/1; \
		done; \
		echo ""; \
		echo "Detected controller on USB port at $$USB"; \
		if grep -q -s 'MINGW\|MSYS' /proc/version; then \
			USB=`echo "$$USB" | perl -pne 's/\/dev\/ttyS(\d+)/COM.($$1+1)/e'`; \
			echo "Remapped MSYS2 USB port to $$USB"; \
		fi; \
		sleep 1; \
		avrdude -p atmega32u4 -P $$USB -c avr109 -U eeprom:w:$(splitdir)/eeprom-righthand.eep


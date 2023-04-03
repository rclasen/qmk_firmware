# Having a file like this allows you to override Makefile definitions
# for your own particular keymap

include myrules.mk

# pro-micro:
BOOTLOADER = caterina

RGBLIGHT_ENABLE = yes
#RGB_MATRIX_ENABLE = yes
#RGB_MATRIX_DRIVER = WS2812

SPLIT_KEYBOARD = yes


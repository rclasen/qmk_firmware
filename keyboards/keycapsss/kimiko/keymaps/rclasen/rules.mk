# Having a file like this allows you to override Makefile definitions
# for your own particular keymap

include myrules.mk

# pro-micro:
BOOTLOADER = caterina

RGBLIGHT_ENABLE := no
RGB_MATRIX_ENABLE := yes

SPLIT_KEYBOARD = yes


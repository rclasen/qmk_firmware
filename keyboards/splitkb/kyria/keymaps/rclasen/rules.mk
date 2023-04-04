# Having a file like this allows you to override Makefile definitions
# for your own particular keymap

include myrules.mk

# pro-micro:
BOOTLOADER = caterina

OLED_DRIVER_ENABLE = yes
RGBLIGHT_ENABLE = yes
RGBMATRIX_ENABLE = no

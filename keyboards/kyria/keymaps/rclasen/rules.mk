# Having a file like this allows you to override Makefile definitions
# for your own particular keymap

include myrules.mk

# breaks fn_actions:
LINK_TIME_OPTIMIZATION_ENABLE = no

# TODO: OLED_DRIVER_ENABLE = yes
# TODO: RGBLIGHT_ENABLE = yes

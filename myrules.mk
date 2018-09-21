# makefile snippet included by all of my keymaps:
# include mykeymap.mk

BOOTMAGIC_ENABLE    := no  # Virtual DIP switch configuration(+1000)

BACKLIGHT_ENABLE    := no
RGBLIGHT_ENABLE     := no
SLEEP_LED_ENABLE    := no  # Breathing sleep LED during USB suspend

CONSOLE_ENABLE      := no        # Console for debug(+400)
COMMAND_ENABLE      := no        # Commands for debug and configuration

NKRO_ENABLE         := yes # USB Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work

UNICODE_ENABLE      := no # Unicode
MOUSEKEY_ENABLE     := yes # Mouse keys(+4700)
EXTRAKEY_ENABLE     := yes # Audio control and System control(+450)
ONEHAND_ENABLE      := no # Allow swapping hands of keyboard
MYEVENT_ENABLE      := yes


#TAP_DANCE_ENABLE    := yes



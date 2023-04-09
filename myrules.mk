# makefile snippet included by all of my keymaps:
# include mykeymap.mk

# unwanted:
BOOTMAGIC_ENABLE    := no  # Virtual DIP switch configuration(+1000)
MAGIC_ENABLE		:= no
SPACE_CADET_ENABLE	:= no
GRAVE_ESC_ENABLE	:= no
SLEEP_LED_ENABLE    := no  # Breathing sleep LED during USB suspend
MIDI_ENABLE			:= no
AUDIO_ENABLE		:= no
UNICODE_ENABLE      := no # Unicode
ONEHAND_ENABLE      := no # Allow swapping hands of keyboard
TAP_DANCE_ENABLE    := no

# default off, enable per keymap where installed/desired
BACKLIGHT_ENABLE    := no
RGBLIGHT_ENABLE     := no
RGB_MATRIX_ENABLE   := no
OLED_ENABLE			:= no
ENCODER_ENABLE		:= no

CONSOLE_ENABLE      := no        # Console for debug(+400)
COMMAND_ENABLE      := no        # Commands for debug and configuration

# keymap requirements:
NKRO_ENABLE         := yes
MOUSEKEY_ENABLE     := yes # Mouse keys(+4700)
EXTRAKEY_ENABLE     := yes # Audio control and System control(+450)
MYEVENT_ENABLE      := yes
# alternative to myevent:
#ONESHOT_ENABLE		:= yes





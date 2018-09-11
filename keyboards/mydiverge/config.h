/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x3060
#define DEVICE_VER      0x0001
#define MANUFACTURER    zuto.de
#define PRODUCT         diverge3
#define DESCRIPTION     A split keyboard for the cheap makers

// lets_split/matrix.c has DIODE_DIRECTION COL2ROW hardwired...
// so, hack around this by transposing the keybaord matrix in KEYMAP() // macro

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 16
#define MATRIX_COLS 5

// 4 (vcc) to A3 (GND) works when top right of right half is pressed

// wiring of each half
// pro micro / arduino pin labels:
//#define MATRIX_COL_PINS { 4,   6,   7,   8,   9 }
//#define MATRIX_ROW_PINS { A3,  A2,  A1,  A0,  15,  14,  16,  10 }
// avr / QMK pin names:
#define MATRIX_COL_PINS   { D4,  D7,  E6,  B4,  B5 }
#define MATRIX_ROW_PINS   { F4,  F5,  F6,  F7,  B1,  B3,  B2,  B6 }

// backlight
// arduino D5, portc, bit6, avr PC6, pin 5, timer 3A
#define BACKLIGHT_PIN C6
// #define BACKLIGHT_LEVELS 5
// add BACKLIGHT_ENABLE=yes to your keymap rules.mk/Makefule


/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* key combination for command */
#define IS_COMMAND() ( \
        keyboard_report->mods == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || \
        keyboard_report->mods == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) \
)


#endif


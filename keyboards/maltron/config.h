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

/* USB Device descriptor parameter */

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 19

// ROWS: Top to bottom
// COLS: Left to right,
#define MATRIX_ROW_PINS { C5, C4, C3, C2, C1, C0 }
#define MATRIX_COL_PINS { B6, B5, B4, B3, B2, B1,       /* left */ \
                          B0, E7, E6, E1, E0, D7, D5,   /* center */ \
                          D4, D3, D2, D1, D0, B7 }      /* right */

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

#define RGB_DI_PIN C7
#define RGBLED_NUM 30

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)


#endif

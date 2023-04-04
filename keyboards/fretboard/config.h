/*
Copyright 2018 Rainer Clasen <bj@zuto.de>

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
#define MATRIX_ROWS 4
#define MATRIX_COLS 13

// COLS: Left to right, ROWS: Top to bottom
#define MATRIX_ROW_PINS { B5, B4, B6, B2 }
#define MATRIX_COL_PINS { D1, D0, D4, C5, D7, E6,/* left */ \
                          D3, /* center */ \
                          B3, B1, F4, F6, F5, F4 } /* right */

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

#endif

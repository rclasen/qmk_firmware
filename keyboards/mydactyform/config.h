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

#pragma once
/* key matrix size */
// thumb cluster has an extra row -> 5x6
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

#define DIODE_DIRECTION COL2ROW

// wiring of each half
// pro micro / arduino pin labels - see QMKDIR/drivers/avr/pro_micro.h
//#define MATRIX_ROW_PINS { A0, 15, 14, 16, 10 }
//#define MATRIX_COL_PINS {  4,  5,  6,  7,  8,  9 }
// avr / QMK pin names:
#define MATRIX_ROW_PINS   { F7, B1, B3, B2, B6 }
#define MATRIX_COL_PINS   { D4, C6, D7, E6, B4, B5 }

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* key combination for command */
#define IS_COMMAND() ( \
        keyboard_report->mods == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || \
        keyboard_report->mods == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) \
)

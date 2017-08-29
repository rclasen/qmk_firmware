#include "diverge3.h"
#include "action_layer.h"
#include "print.h"

enum {
    BASE    = 0,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE
 *
 * .------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  | del  |
 * |------+------+------+------+-------------+------|
 * |  tab |   q  |   w  |   e  |   e  |   r  |      |
 * |------+------+------+------+-------------+------|
 * |      |   a  |   s  |   d  |   d  |   f  |      |
 * |------+------+------+------+------|------+------|
 * | shift|   z  |   x  |   c  |   v  |   b  | ins  |
 * |------+------+------+------+------+------+------+------.
 * |      |      |  lgui| lalt | lctrl| space|      | esc  |
 * '-------------------------------------------------------.
 *
 *        .------------------------------------------------.
 *        | print|   6  |   7  |   8  |   9  |   0  |   -  |
 *        +------+------+------+------+-------------+------|
 *        |      |   y  |   u  |   i  |   o  |   p  |      |
 *        +------+------+------+------+-------------+------|
 *        |      |   j  |   k  |   k  |   l  |      |      |
 *        +------+------+------+------+------|------+------|
 *        |      |   n  |   m  |   ,  |   ,  |      |      |
 * .------+------+------+------+------+------+------+------|
 * | tab  | BSPC | enter| shift| lalt | lgui | ralt |      |
 * `-------------------------------------------------------'
 */
[BASE] = KEYMAP( \
        // left hand
        KC_GRV,         KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_DEL,
        KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_F1,
        KC_F2,          KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           KC_F3,
        KC_LSFT,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           LSFT(KC_INS),
        KC_F4,          KC_F5,          KC_LGUI,        KC_LALT,        KC_LCTL,        KC_SPC,         KC_F6,          KC_ESC,

        // right hand
                        KC_PSCR,        KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINS,
                        KC_F7,          KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_F8,
                        KC_F9,          KC_H,           KC_J,           KC_K,           KC_L,           KC_F10,         KC_F11,
                        KC_F12,         KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_F13,         KC_LSFT,
        KC_TAB,         KC_BSPC,        KC_ENTER,       KC_LSFT,        KC_LALT,        KC_LGUI,        KC_RALT,        KC_F14
 ),

};

void matrix_init_user(void) {
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;
    print("miu\n");
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // not sufficient to set debug_enable from matrix_init
    debug_enable=true;
    debug_matrix=true;
    debug_keyboard=true;

    if( keycode == KC_F13 ){
        print("huhu\n");
    }

    return true;
}


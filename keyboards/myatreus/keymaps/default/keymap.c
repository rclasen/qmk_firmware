#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "print.h"

#include <mykeys.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE
 *
 * .----------------------------------.
 * |   q  |   w  |   e  |   e  |   r  |
 * |------+------+------+-------------|
 * |   a  |   s  |   d  |   d  |   f  |
 * |------+------+------+------|------|
 * |   z  |   x  |   c  |   v  |   b  |
 * |------+------+------+------+------+------.
 * | tab  | fMOS | lalt | lctl | lsft | fNAV |
 * '-----------------------------------------'
 *
 *        .----------------------------------.
 *        |   y  |   u  |   i  |   o  |   p  |
 *        +------+------+------+-------------|
 *        |   j  |   k  |   k  |   l  | COMP |
 *        +------+------+------+------|------|
 *        |   n  |   m  |   ,  |   ,  | Enter|
 * .------+------+------+------+------+------|
 * | BSPC | space| fSYM | fMOS | rctl | lgui |
 * `-----------------------------------------'
 */
[BASE] = KEYMAP( \
        // left hand
        KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,
        KC_A,           KC_S,           KC_D,           KC_F,           KC_G,
        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,
        KC_TAB,         XL_MOS,         XM_LALT,        XM_LCTL,        XM_LSFT,        XL_NAV,

        // right hand
                        KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,
                        KC_H,           KC_J,           KC_K,           KC_L,           KC_COMP,
                        KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_ENTER,
        KC_BSPC,        KC_SPC,         XL_SYM,         XL_MOS,         XM_RCTL,        XM_LGUI
 ),
/* Keymap 1: Symbol Layer
 *
 * TODO: add more exotic characters
 *
 * ,-----------------------------------
 * |  @   |  _   |  [   |  ]   |   ^  |
 * |------+------+------+------+------|
 * |  \   |  /   |  {   |  }   |   *  |
 * |------+------+------+------+------|
 * |  #   |  $   |  |   |  ~   |   `  |
 * |------+------+------+------+------+------.
 * |      |      |      |      |      |      |
 * `-----------------------------------------'

 *        ,----------------------------------.
 *        |  !   |  <   |  >   |  =   |  &   |
 *        |------+------+------+------+------|
 *        |  ?   |  (   |  )   |  -   |  :   |
 *        |------+------+------+------+------|
 *        |  +   |  %   |  "   |  '   |  ;   |
 * ,------+------+------+------+------+------|
 * |      |      |      |      |      |      |
 * `-----------------------------------------'

 */
[SYM] = KEYMAP(
       // left hand
       KC_AT,   KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC,
       KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR,
       KC_HASH, KC_DLR,  KC_PIPE, KC_TILD, KC_GRV,
       _______, _______, _______, _______, _______, _______,

       // right hand
                KC_EXLM, KC_LABK, KC_RABK, KC_EQL,  KC_AMPR,
                KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_COLN,
                KC_PLUS, KC_PERC, KC_DQT,  KC_QUOT, KC_SCLN,
       _______, _______, _______, _______, _______, _______
),
/* keymap 2: navigation and keypad
 *
 * ,----------------------------------.
 * | PgUp | BSpac| up   | Del  | PgDn |
 * |------+------+------+------+------|
 * | Home | left | down | right| End  |
 * |------+------+------+------+------|
 * | Esc  | Tab  | Ins  | Enter| space|
 * |------+------+------+------+------+------.
 * |      |      |      |      |      |      |
 * `-----------------------------------------'

 *        ,----------------------------------.
 *        |  -   |  7   |  8   |  9   |  +   |
 *        |------+------+------+------+------|
 *        |  .   |  4   |  5   |  6   |  ,   |
 *        |------+------+------+------+------|
 *        |  :   |  1   |  2   |  3   |  ;   |
 * ,------+------+------+------+------+------|
 * |      |      |      |  0   |      |      |
 * `-----------------------------------------'
 */
[NAV] = KEYMAP(
       KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN,
       KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,KC_END,
       KC_ESC,  KC_TAB,  KC_INS,  KC_ENTER,KC_SPACE,
       _______, _______, _______, _______, _______, _______,
       // right hand
       // TODO: use Keypad keys:
                MC_MINS, MC_7,    MC_8,    MC_9,    MC_PLUS,
                MC_DOT,  MC_4,    MC_5,    MC_6,    MC_COMM,
                MC_COLN, MC_1,    MC_2,    MC_3,    MC_SCLN,
       _______, _______, _______, KC_0,    _______, _______
),
/* Keymap 3: Media and mouse keys
 *
 * TODO: more media keys
 *
 * ,----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |
 * |------+------+------+------+------|
 * |  F6  |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|
 * |  F11 |  F12 | MENU | print| CAPS |
 * |------+------+------+------+------+------.
 * |      |      |      |      |      |      |
 * `-----------------------------------------'

 *        ,----------------------------------.
 *        |NumLck| vold | volu | mute | Mclk |
 *        |------+------+------+------+------|
 *        | Mleft| Mdown| Mup  | Mrigh| Lclk |
 *        |------+------+------+------+------|
 *        | mprev| mstop| mplay| mnext| Rclk |
 * ,------+------+------+------+------+------|
 * |      |      |      |      |      |      |
 * `-----------------------------------------'
 */
[MOS] = KEYMAP(
       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
       KC_F11,  KC_F12,  KC_APP,  KC_PAUS, KC_CAPS,
       _______, _______, _______, _______, _______, _______,
       // right hand
                KC_NLCK, KC_VOLD, KC_VOLU, KC_MUTE, KC_BTN3,
                KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1,
                KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_BTN2,
       _______, _______, _______, _______, _______, _______
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // not sufficient to set debug_enable from matrix_init
    debug_enable=true;

    if( ! mytap_process_record( keycode, record ) )
        return false;

    switch(keycode){
        case KC_BASE:
            if( record->event.pressed ){
                clear_oneshot_mods();
                clear_oneshot_locked_mods();
                mytap_clear();
                unregister_mods(get_mods());
                // TODO: caps lock
                // TODO: num lock

                reset_oneshot_layer();
                layer_clear();
            }
            return true;

    }

    return true;
}


// Runs constantly in the background, in a loop.
void matrix_scan_user(void)
{
    mytap_matrix_scan();
}




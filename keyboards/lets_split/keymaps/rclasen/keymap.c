#include QMK_KEYBOARD_H
#include "action_layer.h"

#include <mykeys.h>

// TODO keys: (tab), (ESC), (menu)

#define KEYMAP_HAND( \
    l00, l01, l02, l03, l04, l05, \
    l10, l11, l12, l13, l14, l15, \
    l20, l21, l22, l23, l24, l25, \
    l30, l31, l32, l33, l34, l35, \
    r00, r01, r02, r03, r04, r05, \
    r10, r11, r12, r13, r14, r15, \
    r20, r21, r22, r23, r24, r25, \
    r30, r31, r32, r33, r34, r35 \
    ) LAYOUT_ortho_4x12( \
    l00, l01, l02, l03, l04, l05, \
    r00, r01, r02, r03, r04, r05, \
    l10, l11, l12, l13, l14, l15, \
    r10, r11, r12, r13, r14, r15, \
    l20, l21, l22, l23, l24, l25, \
    r20, r21, r22, r23, r24, r25, \
    l30, l31, l32, l33, l34, l35, \
    r30, r31, r32, r33, r34, r35 \
    )

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,-----------------------------------------.
 * |   Q  |   W  |   E  |   R  |   T  |  GHK |
 * |------+------+------+------+------+------+
 * |   A  |   S  |   D  |   F  |   G  | sIns |
 * |------+------+------+------+------+------+
 * |   Z  |   X  |   C  |   V  |   B  | ESC  |
 * |------+------+------+------+------+------|
 * | Tab  | fMOS | LALT | LCTL | LSFT | fNAV |
 * `-----------------------------------------'
 *
 *        ,-----------------------------------------.
 *        | Print|   Y  |   U  |   I  |   O  |   P  |
 *        |------+------+------+------+------+------|
 *        | Base |   H  |   J  |   K  |   L  | COMP |
 *        |------+------+------+------+------+------|
 *        |      |   N  |   M  |   ,  |   .  | ENTER|
 *        |------+------+------+------+------+------|
 *        | BSPC | Space| fSYM | fMOS | RCTL | LGUI |
 *        `-----------------------------------------'
 */
[BASE] = KEYMAP_HAND(  // layer 0 : default
        // left hand
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XM_GHK,
        TX_A,    TX_S,    TX_D,    TX_F,    KC_G,    S_INS,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_ESC,
        KC_TAB,  XL_MOS,  XM_LALT, XM_LCTL, XM_LSFT, XL_NAV,

        // right hand
        KC_PSCR, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        MC_BASE, KC_H,    TX_J,    TX_K,    TX_L,    TX_COMP,
        XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_ENTER,
        KC_BSPC, KC_SPACE,XL_SYM,  XL_MOS,  XM_RCTL, XM_LGUI
    ),
/* Keymap 1: Symbol Layer
 *
 * ,-----------------------------------------.
 * |  @   |  _   |  [   |  ]   |   ^  |      |
 * |------+------+------+------+------+------+
 * |  \   |  /   |  {   |  }   |   *  |      |
 * |------+------+------+------+------+------+
 * |  #   |  $   |  |   |  ~   |   `  |      |
 * |------+------+------+------+------+------+
 * |      |      |      |      |      |      |
 * `-----------------------------------------'
 *        ,-----------------------------------------.
 *        |      |  !   |  <   |  >   |  =   |  &   |
 *        |------+------+------+------+------+------|
 *        |      |  ?   |  (   |  )   |  -   |  :   |
 *        |------+------+------+------+------+------|
 *        |      |  +   |  %   |  "   |  '   |  ;   |
 *        |------+------+------+------+------+------|
 *        |      |      |      |      |      |      |
 *        `-----------------------------------------'
 */
[SYM] = KEYMAP_HAND(
       // left hand
       KC_AT,   KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC, _______,
       KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR, _______,
       KC_HASH, KC_DLR,  KC_PIPE, KC_TILD, KC_GRV,  _______,
       _______, _______, _______, _______, _______, _______,
       // right hand
       _______, KC_EXLM, KC_LABK, KC_RABK, KC_EQL,  KC_AMPR,
       _______, KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_COLN,
       _______, KC_PLUS, KC_PERC, KC_DQT,  KC_QUOT, KC_SCLN,
       _______, _______, _______, _______, _______, _______
),
/* keymap 2: navigation and keypad
 *
 * ,-----------------------------------------.
 * | PgUp | BSpac| up   | Del  | PgDn |      |
 * |------+------+------+------+------+------+
 * | Home | left | down | right| End  |      |
 * |------+------+------+------+------+------+
 * | Esc  | sIns | Ins  | Enter| space|      |
 * |------+------+------+------+------+------+
 * | GHK  |      |      |      |      |      |
 * `-----------------------------------------'
 *        ,-----------------------------------------.
 *        |      |  -   |  7   |  8   |  9   |  +   |
 *        |------+------+------+------+------+------|
 *        |      |  .   |  4   |  5   |  6   |  ,   |
 *        |------+------+------+------+------+------|
 *        |      |  :   |  1   |  2   |  3   | ENTER|
 *        |------+------+------+------+------+------|
 *        |      |      |      |  0   |      |      |
 *        `-----------------------------------------'
 */
[NAV] = KEYMAP_HAND(
       KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN, _______,
       KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,KC_END,  _______,
       KC_ESC,  S_INS,   KC_INS,  KC_ENTER,KC_SPACE,_______,
       XM_GHK,  _______, _______, _______, _______, _______,
       // right hand
       // TODO: use Keypad keys:
       _______, MC_MINS, MC_7,    MC_8,    MC_9,    MC_PLUS,
       _______, MC_DOT,  TX_4,    TX_5,    TX_6,    TX_COMM,
       _______, KC_COLN, MC_1,    MC_2,    MC_3,    KC_ENTER,
       _______, _______, _______, KC_0,    _______, _______
),
/* Keymap 3: Media and mouse keys
 *
 * TODO: more media keys
 *
 * ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  | RESET|
 * |------+------+------+------+------+------+
 * |  F6  |  F7  |  F8  |  F9  |  F10 |      |
 * |------+------+------+------+------+------+
 * |  F11 |  F12 | MENU | PRINT| CAPS |      |
 * |------+------+------+------+------+------+
 * |      |      |      |      |      |      |
 * `-----------------------------------------'
 *        ,-----------------------------------------.
 *        | RESET|NumLck| VolD | VolUp| Mute | Mclk |
 *        |------+------+------+------+------+------|
 *        |      | Mleft| Mdown| Mup  | Mrigh| Lclk |
 *        |------+------+------+------+------+------|
 *        |      | mprev| mstop| mplay| mnext| Rclk |
 *        |------+------+------+------+------+------|
 *        |      |      |      |      |      |      |
 *        `-----------------------------------------'
 */
[MOS] = KEYMAP_HAND(
       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_RST,
       TX_F6,   TX_F7,   TX_F8,   TX_F9,   KC_F10,  _______,
       KC_F11,  KC_F12,  KC_APP,  KC_PSCR, KC_CAPS, _______,
       _______, _______, _______, _______, _______, _______,
       // right hand
       KC_RST,  KC_NLCK, KC_VOLD, KC_VOLU, KC_MUTE, KC_BTN3,
       _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1,
       _______, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_BTN2,
       _______, _______, _______, _______, _______, _______
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{

    if( ! myevent_process_record( keycode, record ) )
        return false;

    return true;
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void)
{
    myevent_matrix_scan();

#ifdef BACKLIGHT_ENABLE
    mybacklight_layer();
#endif
}

#include <mykeys.h>

// TODO keys: (TAB), (ESC), (sIns), (GHK), (print), base, (menu)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* keymap: BASE
 *
 * .----------------------------------.
 * |   q  |   w  |   e  |   e  |   r  |
 * |------+------+------+------+------|
 * |   a  |   s  |   d  |   f  |   g  |
 * |------+------+------+------+------|
 * |   z  |   x  |   c  |   v  |   b  |
 * |------+------+------+------+------+------.
 * | tab  |      |      | fMOS | lsft | fNAV |
 * '-----------------------------------------'

 *        .----------------------------------.
 *        |   y  |   u  |   i  |   o  |   p  |
 *        +------+------+------+------+------|
 *        |   j  |   k  |   k  |   l  | COMP |
 *        +------+------+------+------+------|
 *        |   n  |   m  |   ,  |   ,  | Enter|
 * .------+------+------+------+------+------|
 * | BSPC | space| fSYM |      | rctl | lgui |
 * '-----------------------------------------'
 */

[BASE] = LAYOUT( \
        // left hand
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        TX_A,    TX_S,    TX_D,    TX_F,    KC_G,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
        KC_TAB,  XXXXXXX, XXXXXXX, XL_MOS,  XM_LSFT, XL_NAV,

        // right hand
                 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
                 KC_H,    TX_J,    TX_K,    TX_L,    TX_COMP,
                 KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_ENTER,
        KC_BSPC, KC_SPC,  XL_SYM,  XXXXXXX, XM_RCTL, XM_LGUI
 ),

/* keymap: Symbol Layer
 *
 * .----------------------------------.
 * |  @   |  _   |  [   |  ]   |   ^  |
 * |------+------+------+------+------|
 * |  \   |  /   |  {   |  }   |   *  |
 * |------+------+------+------+------|
 * |  #   |  $   |  |   |  ~   |   `  |
 * |------+------+------+------+------+------.
 * |      |      |      |      |      |      |
 * '-----------------------------------------'

 *        .----------------------------------.
 *        |  !   |  <   |  >   |  =   |  &   |
 *        |------+------+------+------+------|
 *        |  ?   |  (   |  )   |  -   |  :   |
 *        |------+------+------+------+------|
 *        |  +   |  %   |  "   |  '   |  ;   |
 * .------+------+------+------+------+------|
 * |      |      |      |      |      |      |
 * '-----------------------------------------'
 */

[SYM] = LAYOUT(
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

/* keymap: navigation and keypad
 *
 * .----------------------------------.
 * | PgUp | BSpac| up   | Del  | PgDn |
 * |------+------+------+------+------|
 * | Home | left | down | right| End  |
 * |------+------+------+------+------|
 * | Esc  | sIns | Ins  | Enter| space|
 * |------+------+------+------+------+------.
 * | GHK  |      |      |      |      |      |
 * '-----------------------------------------'

 *        .----------------------------------.
 *        |  -   |  7   |  8   |  9   |  +   |
 *        |------+------+------+------+------|
 *        |  .   |  4   |  5   |  6   |  ,   |
 *        |------+------+------+------+------|
 *        |  :   |  1   |  2   |  3   |  ;   |
 * .------+------+------+------+------+------|
 * |      |      |      |  0   |      |      |
 * '-----------------------------------------'
 */

[NAV] = LAYOUT(
       KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN,
       KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,KC_END,
       KC_ESC,  S_INS,   KC_INS,  KC_ENTER,KC_SPACE,
       XM_GHK,  _______, _______, _______, _______, _______,

       // right hand
                MC_MINS, MC_7,    MC_8,    MC_9,    MC_PLUS,
                MC_DOT,  TX_4,    TX_5,    TX_6,    TX_COMM,
                MC_COLN, MC_1,    MC_2,    MC_3,    MC_SCLN,
       _______, _______, KC_0,    KC_0,    _______, _______
),

/* keymap: Media and mouse keys
 *
 * .----------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |
 * |------+------+------+------+------|
 * |  F6  |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------|
 * |  F11 |  F12 | MENU | print| CAPS |
 * |------+------+------+------+------+------.
 * |      |      |      |      |      |      |
 * '-----------------------------------------'

 *        .----------------------------------.
 *        |NumLck| vold | volu | mute | Mclk |
 *        |------+------+------+------+------|
 *        | Mleft| Mdown| Mup  | Mrigh| Lclk |
 *        |------+------+------+------+------|
 *        | mprev| mstop| mplay| mnext| Rclk |
 * .------+------+------+------+------+------|
 * |      |      |      |      | VER  | RESET|
 * '-----------------------------------------'
 */

[MOS] = LAYOUT(
       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
       TX_F6,   TX_F7,   TX_F8,   TX_F9,   KC_F10,
       KC_F11,  KC_F12,  KC_APP,  KC_PSCR, KC_CAPS,
       _______, _______, _______, _______, _______, _______,

       // right hand
                KC_NLCK, KC_VOLD, KC_VOLU, KC_MUTE, KC_BTN3,
                KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1,
                KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_BTN2,
       _______, _______, _______, _______, MC_VER,  KC_RST
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{

    // not sufficient to set debug_enable from matrix_init
    debug_enable=true;

    return mymacro_process_record( keycode, record );
}

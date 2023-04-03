#include <mykeys.h>

#define KEYMAP_HAND( \
    l00, l01, l02, l03, l04, l05, \
    l10, l11, l12, l13, l14, l15, \
    l20, l21, l22, l23, l24, l25, \
                        l34, l35, l36, \
    \
         r01, r02, r03, r04, r05, r06, \
         r11, r12, r13, r14, r15, r16, \
         r21, r22, r23, r24, r25, r26, \
    r30, r31, r32 \
    ) LAYOUT_split_3x6_3( \
    l00, l01, l02, l03, l04, l05,              r01, r02, r03, r04, r05, r06, \
    l10, l11, l12, l13, l14, l15,              r11, r12, r13, r14, r15, r16, \
    l20, l21, l22, l23, l24, l25,              r21, r22, r23, r24, r25, r26, \
                        l34, l35, l36,    r30, r31, r32 \
    )


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* keymap: BASE
 *
 * .-----------------------------------------.
 * | GHK  |   q  |   w  |   e  |   e  |   r  |
 * |------+------+------+------+------+------|
 * | tab  |   a  |   s  |   d  |   d  |   f  |
 * |------+------+------+------+------+------|
 * |      |   z  |   x  |   c  |   v  |   b  |
 * '---------------------------+------+------+------.
 *                             | fMOV | lsft | fNAV |
 *                             '--------------------'

 *        .-----------------------------------------.
 *        |   y  |   u  |   i  |   o  |   p  | vold |
 *        +------+------+------+------+------+------|
 *        |   j  |   k  |   k  |   l  | COMP | ENTER |
 *        +------+------+------+------+------+------|
 *        |   n  |   m  |   ,  |   .  | enter|      |
 * .------+------+------+---------------------------'
 * | bspc | space| fSYM |
 * '--------------------'
 */

[BASE] = KEYMAP_HAND( \
        // left hand
        XM_GHK,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_TAB,  TX_A,    TX_S,    TX_D,    TX_F,    KC_G,
        XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
                                            XL_MOS,  XM_LSFT, XL_NAV,

        // right hand
                 KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_PSCR,
                 KC_H,    TX_J,    TX_K,    TX_L,    TX_COMP, RGB_TOG,
                 KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_ENTER,RGB_HUI,
        KC_BSPC, KC_SPC,  XL_SYM
 ),

/* keymap: Symbol Layer
 *
 * .-----------------------------------------.
 * |      |  @   |  _   |  [   |  ]   |   ^  |
 * |------+------+------+------+------+------|
 * |      |  \   |  /   |  {   |  }   |   *  |
 * |------+------+------+------+------+------|
 * |      |  #   |  $   |  |   |  ~   |   `  |
 * '---------------------------+------+------+------.
 *                             |      |      |      |
 *                             '--------------------'

 *        .-----------------------------------------.
 *        |  !   |  <   |  >   |  =   |  &   |      |
 *        |------+------+------+------+------+------|
 *        |  ?   |  (   |  )   |  -   |  :   |      |
 *        |------+------+------+------+------+------|
 *        |  +   |  %   |  "   |  '   |  ;   |      |
 * .------+------+------+---------------------------'
 * |      |      |      |
 * '--------------------'
 */

[SYM] = KEYMAP_HAND(
       // left hand
       _______, KC_AT,   KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC,
       _______, KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR,
       _______, KC_HASH, KC_DLR,  KC_PIPE, KC_TILD, KC_GRV,
                                           _______, _______, _______,

       // right hand
                KC_EXLM, KC_LABK, KC_RABK, KC_EQL,  KC_AMPR, _______,
                KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_COLN, _______,
                KC_PLUS, KC_PERC, KC_DQT,  KC_QUOT, KC_SCLN, _______,
       _______, _______, _______
),

/* keymap: navigation and keypad
 *
 * .-----------------------------------------.
 * |      | PgUp | BSpac| up   | Del  | PgDn |
 * |------+------+------+------+------+------|
 * |      | Home | left | down | right| End  |
 * |------+------+------+------+------+------|
 * |      | Esc  | sIns | Ins  | Enter| space|
 * '---------------------------+------+------+------.
 *                             |      |      |      |
 *                             '--------------------'

 *        .-----------------------------------------.
 *        |  -   |  7   |  8   |  9   |  +   |      |
 *        |------+------+------+------+------+------|
 *        |  .   |  4   |  5   |  6   |  ,   |      |
 *        |------+------+------+------+------+------|
 *        |  :   |  1   |  2   |  3   | Enter|      |
 * .------+------+------+---------------------------'
 * |      |      |  0   |
 * '--------------------'
 */

[NAV] = KEYMAP_HAND(
       _______, KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN,
       _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,KC_END,
       _______, KC_ESC,  S_INS,   KC_INS,  KC_ENTER,KC_SPACE,
                                           _______, _______, _______,

       // right hand
                MC_MINS, MC_7,    MC_8,    MC_9,    MC_PLUS, RGB_SAI,
                MC_DOT,  TX_4,    TX_5,    TX_6,    TX_COMM, RGB_MOD,
                MC_COLN, MC_1,    MC_2,    MC_3,    KC_ENTER,RGB_VAI,
       _______, _______, KC_0
),

/* keymap: Media and mouse keys
 *
 * .-----------------------------------------.
 * | RESET|  F1  |  F2  |  F3  |  F4  |  F5  |
 * |------+------+------+------+------+------|
 * |  VER |  F6  |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------+------|
 * |      |  F11 |  F12 | MENU | print| CAPS |
 * '---------------------------+------+------+------.
 *                             |      |      |      |
 *                             '--------------------'

 *        .-----------------------------------------.
 *        |NumLck| vold | volu | mute | Mclk | RESET|
 *        |------+------+------+------+------+------|
 *        | Mleft| Mdown| Mup  | Mrigh| Lclk |  VER |
 *        |------+------+------+------+------+------|
 *        | mprev| mstop| mplay| mnext| Rclk |      |
 * .------+------+------+---------------------------'
 * |      |      |      |
 * '--------------------'
 */

[MOS] = KEYMAP_HAND(
       KC_RST,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
       MC_VER,  TX_F6,   TX_F7,   TX_F8,   TX_F9,   KC_F10,
       _______, KC_F11,  KC_F12,  KC_APP,  KC_PSCR, KC_CAPS,
                                           _______, _______, _______,

       // right hand
                KC_NLCK, KC_VOLD, KC_VOLU, KC_MUTE, KC_BTN3, KC_RST,
                KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1, MC_VER,
                KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_BTN2, _______,
       _______, _______, _______
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{

    // not sufficient to set debug_enable from matrix_init
    debug_enable=true;

    return mymacro_process_record( keycode, record );
}

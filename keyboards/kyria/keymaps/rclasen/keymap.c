#include <mykeys.h>

#define KEYMAP_HAND( \
    l00, l01, l02, l03, l04, l05, \
    l10, l11, l12, l13, l14, l15, \
    l20, l21, l22, l23, l24, l25, l26, l27, \
                   l33, l34, l35, l36, l37, \
    \
                   r02, r03, r04, r05, r06, r07, \
                   r12, r13, r14, r15, r16, r17, \
         r20, r21, r22, r23, r24, r25, r26, r27, \
         r30, r31, r32, r33, r34 \
    ) LAYOUT( \
    l00, l01, l02, l03, l04, l05,                       r02, r03, r04, r05, r06, r07, \
    l10, l11, l12, l13, l14, l15,                       r12, r13, r14, r15, r16, r17, \
    l20, l21, l22, l23, l24, l25, l26, l27,   r20, r21, r22, r23, r24, r25, r26, r27, \
                   l33, l34, l35, l36, l37,   r30, r31, r32, r33, r34 \
    )

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* keymap: BASE
 *
 * .-----------------------------------------.
 * | GHK  |   q  |   w  |   e  |   e  |   r  |
 * |------+------+------+------+------+------|
 * | tab  |   a  |   s  |   d  |   d  |   f  |
 * |------+------+------+------+------+------+-------------.
 * | lsft |   z  |   x  |   c  |   v  |   b  |      |      |
 * '------+------+------+------+------+------+------+------|
 *                      |      | fMOS | lsft | fNAV |      |
 *                      '----------------------------------'

 *               .-----------------------------------------.
 *               |   y  |   u  |   i  |   o  |   p  | PSCR |
 *               |------+------+------+------+------+------|
 *               |   h  |   j  |   k  |   l  | COMP |      |
 * .-------------+------+------+------+------+------+------|
 * |      |      |   n  |   m  |   ,  |   ,  | enter|      |
 * |------+------+------+------+------+--------------------'
 * |      | BSPC |SPACE | fSYM |      |
 * '----------------------------------'
 */

[BASE] = KEYMAP_HAND( \
        // left hand
        XM_GHK,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_TAB,  TX_A,    TX_S,    TX_D,    TX_F,    KC_G,
        XM_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX, XXXXXXX,
                                   XXXXXXX, XL_MOS,  XM_LSFT, XL_NAV,  XXXXXXX,

        // right hand
                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_PSCR,
                          KC_H,    TX_J,    TX_K,    TX_L,    TX_COMP, RGB_TOG,
        XXXXXXX, MC_BASE, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_ENTER,RGB_HUI,
        XXXXXXX, KC_BSPC, KC_SPC,  XL_SYM,  XXXXXXX
 ),

/* keymap: Symbol Layer
 *
 * .-----------------------------------------.
 * |      |  @   |  _   |  [   |  ]   |   ^  |
 * |------+------+------+------+------+------|
 * |      |  \   |  /   |  {   |  }   |   *  |
 * |------+------+------+------+------+------+-------------.
 * |      |  #   |  $   |  |   |  ~   |   `  |      |      |
 * '--------------------+------+------+------+------+------|
 *                      |      |      |      |      |      |
 *                      '----------------------------------'

 *               .-----------------------------------------.
 *               |  !   |  <   |  >   |  =   |  &   |      |
 *               |------+------+------+------+------+------|
 *               |  ?   |  (   |  )   |  -   |  :   |      |
 * .-------------+------+------+------+------+------+------|
 * |      |      |  +   |  %   |  "   |  '   |  ;   |      |
 * |------+------+------+------+------+--------------------'
 * |      |      |      |      |      |
 * '----------------------------------'
 */

[SYM] = KEYMAP_HAND(
       // left hand
       _______, KC_AT,   KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC,
       _______, KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR,
       _______, KC_HASH, KC_DLR,  KC_PIPE, KC_TILD, KC_GRV,  _______, _______,
                                  _______, _______, _______, _______, _______,

       // right hand
                         KC_EXLM, KC_LABK, KC_RABK, KC_EQL,  KC_AMPR, _______,
                         KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_COLN, _______,
       _______, _______, KC_PLUS, KC_PERC, KC_DQT,  KC_QUOT, KC_SCLN, _______,
       _______, _______, _______, _______, _______
),

/* keymap: navigation and keypad
 *
 * .-----------------------------------------.
 * |      | PgUp | BSpac| up   | Del  | PgDn |
 * |------+------+------+------+------+------|
 * |      | Home | left | down | right| End  |
 * |------+------+------+------+------+------+-------------.
 * |      | Esc  | sIns | Ins  | Enter| space|      |      |
 * '--------------------+------+------+------+------+------|
 *                      |      |      |      |      |      |
 *                      '----------------------------------'

 *               .-----------------------------------------.
 *               |  -   |  7   |  8   |  9   |  +   |      |
 *               |------+------+------+------+------+------|
 *               |  .   |  4   |  5   |  6   |  ,   |      |
 * .-------------+------+------+------+------+------+------|
 * |      |      |  :   |  1   |  2   |  3   | Enter|      |
 * |------+------+------+------+------+--------------------'
 * |      |      |      |  0   |      |
 * '----------------------------------'
 */

[NAV] = KEYMAP_HAND(
       _______, KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN,
       _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,KC_END,
       _______, KC_ESC,  S_INS,   KC_INS,  KC_ENTER,KC_SPACE, _______, _______,
                                   _______, _______, _______, _______, _______,

       // right hand
                         MC_MINS, MC_7,    MC_8,    MC_9,    MC_PLUS, RGB_SAI,
                         MC_DOT,  TX_4,    TX_5,    TX_6,    TX_COMM, RGB_MOD,
       _______, _______, MC_COLN, MC_1,    MC_2,    MC_3,    KC_ENTER,RGB_VAI,
       _______, _______, _______, KC_0,    _______
),

/* keymap: Media and mouse keys
 *
 * .-----------------------------------------.
 * | RESET|  F1  |  F2  |  F3  |  F4  |  F5  |
 * |------+------+------+------+------+------|
 * |  VER |  F6  |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------+------+-------------.
 * |      |  F11 |  F12 | MENU | print| CAPS |      |      |
 * '--------------------+------+------+------+------+------|
 *                      |      |      |      |      |      |
 *                      '----------------------------------'

 *               .-----------------------------------------.
 *               |NumLck| vold | volu | mute | Mclk | RESET|
 *               |------+------+------+------+------+------|
 *               | Mleft| Mdown| Mup  | Mrigh| Lclk |  VER |
 * .-------------+------+------+------+------+------+------|
 * |      |      | mprev| mstop| mplay| mnext| Rclk |      |
 * |-------------+------+------+------+--------------------'
 * |      |      |      |      |      |
 * '----------------------------------'
 */

[MOS] = KEYMAP_HAND(
       KC_RST,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
       MC_VER,  TX_F6,   TX_F7,   TX_F8,   TX_F9,   KC_F10,
       _______, KC_F11,  KC_F12,  KC_APP,  KC_PSCR, KC_CAPS, _______, _______,
                                  _______, _______, _______, _______, _______,

       // right hand
                         KC_NLCK, KC_VOLD, KC_VOLU, KC_MUTE, KC_BTN3, KC_RST,
                         KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1, MC_VER,
       _______, _______, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_BTN2, _______,
       _______, _______, _______, _______, _______
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{

    // not sufficient to set debug_enable from matrix_init
    debug_enable=true;

    return mymacro_process_record( keycode, record );
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_status(void) {
    static const char nolayer[] PROGMEM = {"    "};
    static const char nolock[] PROGMEM = {"    "};

    // Host Keyboard Layer Status
    if( layer_state_is(SYM) ){
            oled_write_P(PSTR("SYM "), false);
    } else {
            oled_write( nolayer, false );
    }

    if( layer_state_is(NAV) ){
            oled_write_P(PSTR("NAV "), false);
    } else {
            oled_write( nolayer, false );
    }

    if( layer_state_is(MOS) ){
            oled_write_P(PSTR("MOS "), false);
    } else {
            oled_write( nolayer, false );
    }
    oled_write_P(PSTR("\n"), false);


    // oneshot modifiers
    oled_write_P( MOD_ACTIVE(MB_LSFT|MB_RSFT) ? PSTR("SFT ") : nolock, false );
    oled_write_P( MOD_ACTIVE(MB_LCTL|MB_RCTL) ? PSTR("CTL ") : nolock, false );
    oled_write_P( MOD_ACTIVE(MB_LALT|MB_RALT) ? PSTR("ALT ") : nolock, false );
    oled_write_P( MOD_ACTIVE(MB_LGUI|MB_RGUI) ? PSTR("GUI ") : nolock, false );
    oled_write_P(PSTR("\n"), false);

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUM ") : nolock, false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAP ") : nolock, false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCR ") : nolock, false);
    oled_write_P(PSTR("\n"), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    }
}
#endif


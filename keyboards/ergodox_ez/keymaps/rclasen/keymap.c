#include <mykeys.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* keymap: Basic layer
 *
 * .--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  |      |
 * |--------+------+------+------+------+------+------|
 * | GHK    |   Q  |   W  |   E  |   R  |   T  |  GHK |
 * |--------+------+------+------+------+------|      |
 * | Tab    |   A  |   S  |   D  |   F  |   G  |------|
 * |--------+------+------+------+------+------| sIns |
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |
 * '-+------+------+------+------+------+-------------'
 *   |      | Tab  |      |      | fMOS |
 *   '----------------------------------'
 *                                                    .-------------.
 *                                                    | MENU | right|
 *                                             .------+------+------|
 *                                             |LShift| fNAV | left |
 *                                             +      +      +------|
 *                                             |LShift| fNAV | ESC  |
 *                                             '--------------------'


 *               .--------------------------------------------------.
 *               |      |   6  |   7  |   8  |   9  |   0  |        |
 *               |------+------+------+------+------+------+--------|
 *               | Print|   Y  |   U  |   I  |   O  |   P  | PSCR   |
 *               |      |------+------+------+------+------+--------|
 *               |------|   H  |   J  |   K  |   L  | COMP |        |
 *               | BASE |------+------+------+------+------+--------|
 *               |      |   N  |   M  |   ,  |   .  | Enter| RShift |
 *               '-------------+------+------+------+------+------+-'
 *                             | fSYM |      | RCTL | LGUI |      |
 *                             '----------------------------------'
 * .-------------.
 * |  up  | COMP |
 * |------+------+------.
 * | down | BSPC | Space|
 * |------+      +      |
 * | RALT | BSPC | Space|
 * '--------------------'
 */

[BASE] = LAYOUT_ergodox_80(  // layer 0 : default
        // left hand
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,
        XM_GHK,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XM_GHK,
        KC_TAB,  TX_A,    TX_S,    TX_D,    TX_F,    KC_G,
        XM_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    S_INS,
        XXXXXXX, KC_TAB,  XXXXXXX, XXXXXXX, XL_MOS,
                                            // left thumb
                                                     KC_APP,  KC_RIGHT,
                                            XM_LSFT, XL_NAV,  KC_LEFT,
                                            XM_LSFT, XL_NAV,  KC_ESC,

        // right hand
        XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
        KC_PSCR, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_PSCR,
                 KC_H,    TX_J,    TX_K,    TX_L,    TX_COMP, XXXXXXX,
        MY_BASE, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_ENTER,XM_RSFT,
                          XL_SYM,  XXXXXXX, XM_RCTL, XM_LGUI, XXXXXXX,
        // right thum
        KC_UP,   KC_COMP,
        KC_DOWN, KC_BSPC, KC_SPACE,
        KC_RALT, KC_BSPC, KC_SPACE
    ),

/* keymap: Symbol Layer
 *
 * .--------------------------------------------------.
 * |        |      |      |      |      |      |      |
 * |--------+------+------+------+------+------+------|
 * |        |  @   |  _   |  [   |  ]   |   ^  |      |
 * |--------+------+------+------+------+------|      |
 * |        |  \   |  /   |  {   |  }   |   *  |------|
 * |--------+------+------+------+------+------|      |
 * |        |  #   |  $   |  |   |  ~   |   `  |      |
 * '--------+------+------+------+------+-------------'
 *   |      |      |      |      |      |
 *   '----------------------------------'
 *                                        .-------------.
 *                                        |      |      |
 *                                 .------+------+------|
 *                                 |      |      |      |
 *                                 |------+------+------|
 *                                 |      |      |      |
 *                                 '--------------------'

 *   .--------------------------------------------------.
 *   |      |      |      |      |      |      |        |
 *   |------+------+------+------+------+------+--------|
 *   |      |  !   |  <   |  >   |  =   |  &   |        |
 *   |      |------+------+------+------+------+--------|
 *   |------|  ?   |  (   |  )   |  -   |  :   |        |
 *   |      |------+------+------+------+------+--------|
 *   |      |  +   |  %   |  "   |  '   |  ;   |        |
 *   '-------------+------+------+------+------+--------'
 *                 |      |      |      |      |      |
 *                 '----------------------------------'
 * .-------------.
 * |      |      |
 * |------+------+------.
 * |      |      |      |
 * |------+------+------|
 * |      |      |      |
 * '--------------------'
 */

[SYM] = LAYOUT_ergodox_80(
       // left hand
       _______, _______, _______, _______, _______, _______, _______,
       _______, KC_AT,   KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC, _______,
       _______, KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR,
       _______, KC_HASH, KC_DLR,  KC_PIPE, KC_TILD, KC_GRV,  _______,
       _______, _______, _______, _______, _______,
                                                    _______, _______,
                                           _______, _______, _______,
                                           _______, _______, _______,

       // right hand
       _______, _______, _______, _______, _______, _______, _______,
       _______, KC_EXLM, KC_LABK, KC_RABK, KC_EQL,  KC_AMPR, _______,
                KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_COLN, _______,
       _______, KC_PLUS, KC_PERC, KC_DQT,  KC_QUOT, KC_SCLN, _______,
                         _______, _______, _______, _______, _______,
       _______, _______,
       _______, _______, _______,
       _______, _______, _______
),

/* keymap: navigation and keypad
 *
 * .--------------------------------------------------.
 * |        |      |      |      |      |      |      |
 * |--------+------+------+------+------+-------------|
 * |        | PgUp | BSpac| up   | Del  | PgDn |      |
 * |--------+------+------+------+------+------|      |
 * |        | Home | left | down | right| End  |------|
 * |--------+------+------+------+------+------|      |
 * |        | Esc  | sIns | Ins  | Enter| space|      |
 * '--------+------+------+------+------+-------------'
 *   |      | GHK  |      |      |      |
 *   '----------------------------------'
 *                                        .-------------.
 *                                        |      |      |
 *                                 .------+------+------|
 *                                 |      |      |      |
 *                                 |------+------+------|
 *                                 |      |      |      |
 *                                 '--------------------'

 *   .--------------------------------------------------.
 *   |      | Tab  |NumLck|  /   |  *   |      |        |
 *   |------+------+------+------+------+------+--------|
 *   |      |  -   |  7   |  8   |  9   |  +   |        |
 *   |      |------+------+------+------+------+--------|
 *   |------|  .   |  4   |  5   |  6   |  ,   |        |
 *   |      |------+------+------+------+------+--------|
 *   |      |  :   |  1   |  2   |  3   | Enter|        |
 *   '-------------+------+------+------+------+--------'
 *                 |  0   |  0   |      |      |      |
 *                 '----------------------------------'
 * .-------------.
 * |      |      |
 * |------+------+------.
 * |      |      |      |
 * |------+------+------|
 * |      |      |      |
 * '--------------------'
 */

[NAV] = LAYOUT_ergodox_80(
       _______, _______, _______, _______, _______, _______, _______,
       _______, KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN, _______,
       _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,KC_END,
       _______, KC_ESC,  S_INS,   KC_INS,  KC_ENTER,KC_SPACE,_______,
       _______, XM_GHK,  _______, _______, _______,
                                                    _______, _______,
                                           _______, _______, _______,
                                           _______, _______, _______,

       // right hand
       // TODO: use Keypad keys:
       _______, KC_TAB,  KC_NUM,  KC_SLSH, KC_ASTR, _______, _______,
       _______, MY_MINS, MY_7,    MY_8,    MY_9,    MY_PLUS, _______,
                MY_DOT,  TX_4,    TX_5,    TX_6,    TX_COMM, _______,
       _______, KC_COLN, MY_1,    MY_2,    MY_3,    KC_ENTER,_______,
                         KC_0,    KC_0,    _______, _______, _______,
       _______, _______,
       _______, _______, _______,
       _______, _______, _______
),

/* keymap: Media and mouse keys
 *
 * TODO: more media keys
 *
 * .--------------------------------------------------.
 * |        |      |      |      |      |      |      |
 * |--------+------+------+------+------+-------------|
 * | RESET  |  F1  |  F2  |  F3  |  F4  |  F5  | RESET|
 * |--------+------+------+------+------+------|      |
 * | VER    |  F6  |  F7  |  F8  |  F9  |  F10 |------|
 * |--------+------+------+------+------+------| VER  |
 * |        |  F11 |  F12 | MENU | PRINT| CAPS |      |
 * '--------+------+------+------+------+-------------'
 *   |      |      |      |      |      |
 *   '----------------------------------'
 *                                        .-------------.
 *                                        |      |      |
 *                                 .------+------+------|
 *                                 |      |      |      |
 *                                 |------+------+------|
 *                                 |      |      |      |
 *                                 '--------------------'

 *   .--------------------------------------------------.
 *   |      |      |      |      |      |      |        |
 *   |------+------+------+------+------+------+--------|
 *   | RESET|NumLck| VolD | VolUp| Mute | Mclk | RESET  |
 *   |      |------+------+------+------+------+--------|
 *   |------| Mleft| Mdown| Mup  | Mrigh| Lclk | VER    |
 *   | VER  |------+------+------+------+------+--------|
 *   |      | mprev| mstop| mplay| mnext| Rclk |        |
 *   '-------------+------+------+------+------+--------'
 *                 |      |      | VER  | RESET|      |
 *                 '----------------------------------'
 * .-------------.
 * |      |      |
 * |------+------+------.
 * |      |      |      |
 * |------+------+------|
 * |      |      |      |
 * '--------------------'
 */

[MOS] = LAYOUT_ergodox_80(
       _______, _______, _______, _______, _______, _______, _______,
       QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   QK_BOOT,
       MY_VER,  TX_F6,   TX_F7,   TX_F8,   TX_F9,   KC_F10,
       _______, KC_F11,  KC_F12,  KC_APP,  KC_PSCR, KC_CAPS, MY_VER,
       _______, _______, _______, _______, _______,
                                                    _______, _______,
                                           _______, _______, _______,
                                           _______, _______, _______,

       // right hand
       _______, _______, _______, _______, _______, _______, _______,
       QK_BOOT, KC_NUM,  KC_VOLD, KC_VOLU, KC_MUTE, KC_BTN3, QK_BOOT,
                KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1, MY_VER,
       MY_VER,  KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_BTN2, _______,
                         _______, _______, MY_VER,  QK_BOOT, _______,
       _______, _______,
       _______, _______, _______,
       _______, _______, _______
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{

    // not sufficient to set debug_enable from matrix_init
    debug_enable=true;

    return mymacro_process_record( keycode, record );
}

#if 0
// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    debug_enable=true;

};
#endif


static uint8_t usbled = 0;

void led_set_kb( uint8_t usb_led )
{
	usbled = usb_led;
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void)
{

	uint8_t led[] = {
		0, 0, 0
	};

	// layer

	if( layer_state & 1UL<<NAV ){
		led[1] |= 1UL<<5;
	}

	if( layer_state & 1UL<<MOS ){
		led[1] |= 1UL<<6;
	}

	if( layer_state & 1UL<<SYM ){
		led[1] |= 1UL<<7;
	}

	// OS state

	if( ! ( usbled & (1UL<<USB_LED_NUM_LOCK) )){
		led[0] |= 1UL<<3;
	}

	if( usbled & (1UL<<USB_LED_COMPOSE) ){
		led[0] |= 1UL<<5;
	}

	if( usbled & (1UL<<USB_LED_CAPS_LOCK) ){
		led[0] |= 1UL<<7;
	}

	// modifier

	if( MOD_ACTIVE( MB_LSFT | MB_RSFT ) ){
		led[2] |= 1UL<<4;
	}

	if( MOD_ACTIVE( MB_LCTL | MB_RCTL ) ){
		led[2] |= 1UL<<5;
	}

	if( MOD_ACTIVE( MB_LALT | MB_RALT ) ){
		led[2] |= 1UL<<6;
	}

	if( MOD_ACTIVE( MB_LGUI | MB_RGUI ) ){
		led[2] |= 1UL<<7;
	}



	// finally: set led on/off/brightness

	if( led[0] ){
		ergodox_right_led_1_set( led[0] );
		ergodox_right_led_1_on();
	} else {
		ergodox_right_led_1_off();
	}

	if( led[1] ){
		ergodox_right_led_2_set( led[1] );
		ergodox_right_led_2_on();
	} else {
		ergodox_right_led_2_off();
	}

	if( led[2] ){
		ergodox_right_led_3_set( led[2] );
		ergodox_right_led_3_on();
	} else {
		ergodox_right_led_3_off();
	}

};



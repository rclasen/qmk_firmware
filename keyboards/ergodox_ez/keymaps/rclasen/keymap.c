#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#include <mykeys.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  |      |
 * |--------+------+------+------+------+-------------|
 * |        |   Q  |   W  |   E  |   R  |   T  |  GHK |
 * |--------+------+------+------+------+------|      |
 * | Tab    |   A  |   S  |   D  |   F  |   G  |------|
 * |--------+------+------+------+------+------| sIns |
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |
 * `--------+------+------+------+------+-------------'
 *   |      | Tab  | fMOS | LALT | LCTL |
 *   `----------------------------------'
 *                                        ,-------------.
 *                                        | MENU | right|
 *                                 ,------|------|------|
 *                                 |LShift| fNAV | left |
 *                                 +      +      +------+
 *                                 |LShift| fNAV | ESC  |
 *                                 `--------------------'
 *
 *   ,--------------------------------------------------.
 *   |      |   6  |   7  |   8  |   9  |   0  | VolUp  |
 *   |------+------+------+------+------+------+--------|
 *   | Print|   Y  |   U  |   I  |   O  |   P  | VolDown|
 *   |      |------+------+------+------+------+--------|
 *   |------|   H  |   J  |   K  |   L  | COMP |        |
 *   | BASE |------+------+------+------+------+--------|
 *   |      |   N  |   M  |   ,  |   .  | Enter| RShift |
 *   `-------------+------+------+------+------+--------'
 *                 | fSYM | fMOS | RCTL | LGUI |      |
 *                 `----------------------------------'
 * ,-------------.
 * |  up  | COMP |
 * |------+------+------.
 * | down | BSPC | Space|
 * +------+      +      +
 * | RALT | BSPC | Space|
 * `--------------------'
 */
[BASE] = KEYMAP_80(  // layer 0 : default
        // left hand
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,
        XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XM_GHK,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        XM_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    LSFT(KC_INS),
        XXXXXXX, KC_TAB,  XL_MOS,  XM_LALT, XM_LCTL,
                                            // left thumb
                                                     KC_APP,  KC_RIGHT,
                                            XM_LSFT, XL_NAV,  KC_LEFT,
                                            XM_LSFT, XL_NAV,  KC_ESC,

        // right hand
        XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_VOLU,
        KC_PSCR, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_VOLD,
                 KC_H,    KC_J,    KC_K,    KC_L,    KC_COMP, XXXXXXX,
        KC_BASE, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_ENTER,KC_RSFT,
                          XL_SYM,  XL_MOS,  XM_RCTL, XM_LGUI, XXXXXXX,
        // right thum
        KC_UP,   KC_COMP,
        KC_DOWN, KC_BSPC, KC_SPACE,
        KC_RALT, KC_BSPC, KC_SPACE
    ),
/* Keymap 1: Symbol Layer
 *
 * TODO: add more exotic characters
 *
 * ,--------------------------------------------------.  
 * |        |      |      |      |      |      |      |  
 * |--------+------+------+------+------+-------------|  
 * |        |  @   |  _   |  [   |  ]   |   ^  |      |  
 * |--------+------+------+------+------+------|      |  
 * |        |  \   |  /   |  {   |  }   |   *  |------|  
 * |--------+------+------+------+------+------|      |  
 * |        |  #   |  $   |  |   |  ~   |   `  |      |  
 * `--------+------+------+------+------+-------------'  
 *   |      |      |      |      |      |                
 *   `----------------------------------'                
 *                                        ,-------------.
 *                                        |      |      |
 *                                 ,------|------|------|
 *                                 |      |      |      |
 *                                 |------|------|------|
 *                                 |      |      |      |
 *                                 `--------------------'
 *   ,--------------------------------------------------.
 *   |      |      |      |      |      |      |        |
 *   |------+------+------+------+------+------+--------|
 *   |      |  !   |  <   |  >   |  =   |  &   |        |
 *   |      |------+------+------+------+------+--------|
 *   |------|  ?   |  (   |  )   |  -   |  :   |        |
 *   |      |------+------+------+------+------+--------|
 *   |      |  +   |  %   |  "   |  '   |  ;   |        |
 *   `-------------+------+------+------+------+--------'
 *                 |      |      |      |      |      |
 *                 `----------------------------------'
 * ,-------------.
 * |      |      |
 * |------+------+------.
 * |      |      |      |
 * |------|------|------|
 * |      |      |      |
 * `--------------------'
 */
[SYM] = KEYMAP_80(
       // left hand
       _______, _______, _______, _______, _______, _______, _______,
       _______, KC_AT,   KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC, _______,
       _______, KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR,
       XXXXXXX, KC_HASH, KC_DLR,  KC_PIPE, KC_TILD, KC_GRV,  _______,
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
/* keymap 2: navigation and keypad
 *
 * ,--------------------------------------------------.  
 * |        |      |      |      |      |      |      |  
 * |--------+------+------+------+------+-------------|  
 * |        | PgUp | BSpac| up   | Del  | PgDn |      |  
 * |--------+------+------+------+------+------|      |  
 * |        | Home | left | down | right| End  |------|  
 * |--------+------+------+------+------+------|      |  
 * |        | Esc  | Tab  | Ins  | Enter| space|      |  
 * `--------+------+------+------+------+-------------'  
 *   |      |      |      |      |      |                
 *   `----------------------------------'                
 *                                        ,-------------.
 *                                        |      |      |
 *                                 ,------|------|------|
 *                                 |      |      |      |
 *                                 |------|------|------|
 *                                 |      |      |      |
 *                                 `--------------------'
 *   ,--------------------------------------------------.
 *   |      | Tab  |NumLck|  /   |  *   |      |        |
 *   |------+------+------+------+------+------+--------|
 *   |      |  -   |  7   |  8   |  9   |  +   |        |
 *   |      |------+------+------+------+------+--------|
 *   |------|  .   |  4   |  5   |  6   |  ,   |        |
 *   |      |------+------+------+------+------+--------|
 *   |      |  :   |  1   |  2   |  3   | Enter|        |
 *   `-------------+------+------+------+------+--------'
 *                 |      |  0   |      |      |      |
 *                 `----------------------------------'
 * ,-------------.
 * |      |      |
 * |------+------+----------.
 * |      |      |          |
 * |------|------|----------|
 * |      |      |          |
 * `------------------------'
 */
[NAV] = KEYMAP_80(
       _______, _______, _______, _______, _______, _______, _______,
       _______, KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN, _______,
       _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,KC_END,
       _______, KC_ESC,  KC_TAB,  KC_INS,  KC_ENTER,KC_SPACE,_______,
       _______, _______, _______, _______, _______,
                                                    _______, _______,
                                           _______, _______, _______,
                                           _______, _______, _______,
       // right hand
       // TODO: use Keypad keys:
       _______, KC_TAB,  KC_NLCK, KC_SLSH, KC_ASTR, _______, _______,
       _______, MC_MINS, MC_7,    MC_8,    MC_9,    MC_PLUS, _______,
                MC_DOT,  MC_4,    MC_5,    MC_6,    MC_COMM, _______,
       _______, KC_COLN, MC_1,    MC_2,    MC_3,    KC_ENTER,_______,
                         _______, KC_0,    _______, _______, _______,
       _______, _______,
       _______, _______, _______,
       _______, _______, _______
),
/* Keymap 3: Media and mouse keys
 *
 * TODO: more media keys
 *
 * ,--------------------------------------------------.  
 * |  RESET |      |      |      |      |      |      |  
 * |--------+------+------+------+------+-------------|  
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |  
 * |--------+------+------+------+------+------|      |  
 * |        |  F6  |  F7  |  F8  |  F9  |  F10 |------|  
 * |--------+------+------+------+------+------|      |  
 * |        |  F11 |  F12 | MENU | PRINT| CAPS |      |  
 * `--------+------+------+------+------+-------------'  
 *   |      |      |      |      |      |                
 *   `----------------------------------'                
 *                                        ,-------------.
 *                                        |      |      |
 *                                 ,------|------|------|
 *                                 |      |      |      |
 *                                 |------|------|------|
 *                                 |      |      |      |
 *                                 `--------------------'
 *   ,--------------------------------------------------.
 *   |      |      |      |      |      |      |        |
 *   |------+------+------+------+------+------+--------|
 *   |      |NumLck| VolD | VolUp| Mute | Mclk |        |
 *   |      |------+------+------+------+------+--------|
 *   |------| Mleft| Mdown| Mup  | Mrigh| Lclk |        |
 *   |      |------+------+------+------+------+--------|
 *   |      | mprev| mstop| mplay| mnext| Rclk |        |
 *   `-------------+------+------+------+------+--------'
 *                 |      |      |      |      |      |
 *                 `----------------------------------'
 * ,-------------.
 * |      |      |
 * |------+------+----------.
 * |      |      |          |
 * |------|------|----------|
 * |      |      |          |
 * `------------------------'
 */
[MOS] = KEYMAP_80(
       KC_RST,  _______, _______, _______, _______, _______, _______,
       _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______,
       _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
       _______, KC_F11,  KC_F12,  KC_APP,  KC_PSCR, KC_CAPS, _______,
       _______, _______, _______, _______, _______,
                                                    _______, _______,
                                           _______, _______, _______,
                                           _______, _______, _______,
       // right hand
       _______, _______, _______, _______, _______, _______, _______,
       _______, KC_NLCK, KC_VOLD, KC_VOLU, KC_MUTE, KC_BTN3, _______,
                KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1, _______,
       _______, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_BTN2, _______,
                         _______, _______, _______, _______, _______,
       _______, _______,
       _______, _______, _______,
       _______, _______, _______
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{

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


#define MOD_ACTIVE(bits) ( keyboard_report->mods & (bits) || (\
	(get_oneshot_mods() & (bits)) \
	&& !has_oneshot_mods_timed_out() \
	) )

// Runs constantly in the background, in a loop.
void matrix_scan_user(void)
{

	uint8_t led[] = {
		0, 0, 0
	};

    mytap_matrix_scan();

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

	if( MOD_ACTIVE( MOD_BIT(KC_LSFT) ) ){
		led[2] |= 1UL<<4;
	}

	if( MOD_ACTIVE( MOD_BIT(KC_RSFT) ) ){
		led[2] |= 1UL<<4;
	}

	if( MOD_ACTIVE( MOD_BIT(KC_LCTL) ) ){
		led[2] |= 1UL<<5;
	}

	if( MOD_ACTIVE( MOD_BIT(KC_RCTL) ) ){
		led[2] |= 1UL<<5;
	}

	if( MOD_ACTIVE( MOD_BIT(KC_LALT) ) ){
		led[2] |= 1UL<<6;
	}

	if( MOD_ACTIVE( MOD_BIT(KC_RALT) ) ){
		led[2] |= 1UL<<6;
	}

	if( MOD_ACTIVE( MOD_BIT(KC_LGUI) ) ){
		led[2] |= 1UL<<7;
	}

	if( MOD_ACTIVE( MOD_BIT(KC_RGUI) ) ){
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



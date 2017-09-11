#include "diverge3.h"
#include "action_layer.h"
#include "print.h"

#include <mykeys.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE
 *
 * .------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |      |
 * |------+------+------+------+-------------+------|
 * |      |   q  |   w  |   e  |   e  |   r  | GHK  |
 * |------+------+------+------+-------------+------|
 * | tab  |   a  |   s  |   d  |   d  |   f  | sINS |
 * |------+------+------+------+------|------+------|
 * | tab  |   z  |   x  |   c  |   v  |   b  |      |
 * |------+------+------+------+------+------+------+------.
 * | lsft | lgui | fMOS | lalt | lctl | lsft | fNAV | esc  |
 * '-------------------------------------------------------'
 *
 *        .------------------------------------------------.
 *        |      |   6  |   7  |   8  |   9  |   0  |   -  |
 *        +------+------+------+------+-------------+------|
 *        | print|   y  |   u  |   i  |   o  |   p  |      |
 *        +------+------+------+------+-------------+------|
 *        | COMP |   j  |   k  |   k  |   l  | CUML | enter|
 *        +------+------+------+------+------|------+------|
 *        | BASE |   n  |   m  |   ,  |   ,  | COMP | enter|
 * .------+------+------+------+------+------+------+------|
 * | ralt | BSPC | space| fSYM | fMOS | rctl | MENU |      |
 * `-------------------------------------------------------'
 */
[BASE] = KEYMAP( \
        // left hand
        KC_GRV,         KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_NO,
        KC_NO,          KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           XM_GHK,
        KC_TAB,         KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           KC_NO,
        KC_TAB,         KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           LSFT(KC_INS),
        XM_LSFT,        XM_LGUI,        XL_MOS,         XM_LALT,        XM_LCTL,        XM_LSFT,        XL_NAV,         KC_ESC,

        // right hand
                        KC_NO,          KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINS,
                        KC_PSCR,        KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_NO,
                        KC_COMP,        KC_H,           KC_J,           KC_K,           KC_L,           MC_CUML,        KC_ENTER,
                        KC_BASE,        KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_COMP,        KC_ENTER,
        KC_RALT,        KC_BSPC,        KC_SPC,         XL_SYM,         XL_MOS,         XM_RCTL,        KC_APP,         KC_NO
 ),
/* Keymap 1: Symbol Layer
 *
 * TODO: add more exotic characters
 *
 * ,------------------------------------------------.
 * |   °  |  §   |  £   |  «   |  »   |  EUR |      |
 * |------+------+------+------+------+------+------|
 * |      |  @   |  _   |  [   |  ]   |   ^  |      |
 * |------+------+------+------+------+------+------|
 * |      |  \   |  /   |  {   |  }   |   *  |      |
 * |------+------+------+------+------+------+------|
 * |      |  #   |  $   |  |   |  ~   |   `  |      |
 * |------+------+------+------+------+------+------+------.
 * |      |      |      |      |      |      |      |      |
 * `-------------------------------------------------------'

 *        ,------------------------------------------------.
 *        |      |      |  “   |  ”   |  ‘   |  ’   |      |
 *        |------+------+------+------+------+------+------|
 *        |      |  !   |  <   |  >   |  =   |  &   |      |
 *        |------+------+------+------+------+------+------|
 *        |      |  ?   |  (   |  )   |  -   |  :   |      |
 *        |------+------+------+------+------+------+------|
 *        |      |  +   |  %   |  "   |  '   |  ;   |      |
 * ,------+------+------+------+- -----+------+------+------|
 * |      |      |      |      |      |      |      |      |
 * `-------------------------------------------------------'

 */
[SYM] = KEYMAP(
       // left hand
       KC_DEGR, KC_PARA, KC_POUN, KC_RDTQ, KC_LDTQ, KC_EURO, KC_TRNS,
       KC_TRNS, KC_AT,   KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC, KC_TRNS,
       KC_TRNS, KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR, KC_TRNS,
       KC_NO,   KC_HASH, KC_DLR,  KC_PIPE, KC_TILD, KC_GRV,  KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

       // right hand
                KC_TRNS, KC_TRNS, KC_LDQ,  KC_RDQ,  KC_LSQ,  KC_RSQ,  KC_TRNS,
                KC_TRNS, KC_EXLM, KC_LABK, KC_RABK, KC_EQL,  KC_AMPR, KC_TRNS,
                KC_TRNS, KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_COLN, KC_TRNS,
                KC_TRNS, KC_PLUS, KC_PERC, KC_DQT,  KC_QUOT, KC_SCLN, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),
/* keymap 2: navigation and keypad
 *
 * ,------------------------------------------------.
 * |      |      |      |  >   |   <  |      |      |
 * |------+------+------+------+------+-------------|
 * |      | PgUp | BSpac| up   | Del  | PgDn |      |
 * |------+------+------+------+------+------|      |
 * |      | Home | left | down | right| End  |------|
 * |------+------+------+------+------+------|      |
 * |      | Esc  | Tab  | Ins  | Enter| sIns |      |
 * |------+------+------+------+------+------+------+------.
 * |      |      |      |      |      |      |      |      |
 * `-------------------------------------------------------'

 *        ,------------------------------------------------.
 *        |      | Tab  |NumLck|  /   |  *   |  ÷   |   ×  |
 *        |------+------+------+------+------+------+------|
 *        |      |  -   |  7   |  8   |  9   |  +   |      |
 *        |      |------+------+------+------+------+------|
 *        |------|  .   |  4   |  5   |  6   |  ,   |      |
 *        |      |------+------+------+------+------+------|
 *        |      |  0   |  1   |  2   |  3   |  :   |      |
 * ,------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |
 * `-------------------------------------------------------'
 */
[NAV] = KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_LSTQ, KC_RSTQ, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN, KC_TRNS,
       KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,KC_END,  KC_TRNS,
       KC_TRNS, KC_ESC,  KC_TAB,  KC_INS,  KC_ENTER,LSFT(KC_INS), KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       // TODO: use Keypad keys:
                KC_TRNS, KC_TAB,  KC_NLCK, KC_SLSH, KC_ASTR, KC_DIV,  KC_MUL,
                KC_TRNS, MC_MINS, MC_7,    MC_8,    MC_9,    MC_PLUS, KC_TRNS,
                KC_TRNS, MC_DOT,  MC_4,    MC_5,    MC_6,    MC_COMM, KC_TRNS,
                KC_TRNS, MC_0,    MC_1,    MC_2,    MC_3,    MC_COLN, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_0,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 3: Media and mouse keys
 *
 * TODO: more media keys
 *
 * ,------------------------------------------------.
 * |RESET |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |
 * |------+------+------+------+------+------|      |
 * |      |  F6  |  F7  |  F8  |  F9  |  F10 |------|
 * |------+------+------+------+------+------|      |
 * |      |  F11 |  F12 |      |      | CAPS |      |
 * |------+------+------+------+------+------+------+------.
 * |      |      |      |      |      |      |      |      |
 * `-------------------------------------------------------'

 *        ,------------------------------------------------.
 *        |      |      |      |      |      |      | VolD |
 *        |------+------+------+------+------+------+------|
 *        |      |NumLck|      |      |      | Mclk | VolUp|
 *        |------+------+------+------+------+------+------|
 *        |      | Mleft| Mdown| Mup  | Mrigh| Lclk |      |
 *        |------+------+------+------+------+------+------|
 *        |      | mprev| mstop| mplay| mnext| Rclk |      |
 * ,------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |
 * `-------------------------------------------------------'
 */
[MOS] = KEYMAP(
       RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
       KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
       KC_TRNS, KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_CAPS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD,
                KC_TRNS, KC_NLCK, KC_TRNS, KC_NO,   KC_TRNS, KC_BTN3, KC_VOLU,
                KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1, KC_TRNS,
                KC_TRNS, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_BTN2, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
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


static uint8_t usbled = 0;

void led_set_kb( uint8_t usb_led ){
	usbled = usb_led;
}


#define MOD_ACTIVE(bits) ( keyboard_report->mods & bits || (\
	(get_oneshot_mods() & bits) \
	&& !has_oneshot_mods_timed_out() \
	) )

static uint8_t led = 0;

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

	uint8_t new = 0;

    mytap_matrix_scan();

	// layer

	if( layer_state ){
		new |= 1UL<<7;
	}

	// modifier
	if( MOD_ACTIVE( MOD_BIT(KC_LSFT|KC_RSFT|KC_LCTL|KC_RCTL|KC_LALT|KC_RALT|KC_LGUI|KC_RGUI) ) ){
		new |= 1UL<<4;
	}

	// finally: set led on/off/brightness

    if( led != new ){
        if( new ){
            diverge_led_back_set( new );
            diverge_led_back_on();

        } else {
            diverge_led_back_off();

        }

        led = new;
	}
}



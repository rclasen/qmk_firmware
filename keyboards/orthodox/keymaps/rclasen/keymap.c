#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "print.h"

#include <mykeys.h>

#define KEYMAP_HAND( \
    l00, l01, l02, l03, l04, l05, \
    l10, l11, l12, l13, l14, l15, \
    l20, l21, l22, l23, l24, l25, l26, l27, \
                             l35, l36, l37, \
    \
              r02, r03, r04, r05, r06, r07, \
              r12, r13, r14, r15, r16, r17, \
    r20, r21, r22, r23, r24, r25, r26, r27, \
    r30, r31, r32 \
    ) LAYOUT( \
    l00, l01, l02, l03, l04, l05,                     r02, r03, r04, r05, r06, r07, \
    l10, l11, l12, l13, l14, l15,                     r12, r13, r14, r15, r16, r17, \
    l20, l21, l22, l23, l24, l25, l26, l27, r20, r21, r22, r23, r24, r25, r26, r27, \
                             l35, l36, l37, r30, r31, r32 \
    )

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE
 *
 * .-----------------------------------------.
 * |      |   q  |   w  |   e  |   e  |   r  |
 * |------+------+------+------+-------------|
 * | tab  |   a  |   s  |   d  |   d  |   f  |
 * |------+------+------+------+------+------+-------------.
 * | tab  |   z  |   x  |   c  |   v  |   b  | fNAV | lalt |
 * '----------------------------------+------+------+------|
 *                                    |      | lsft | lctl |
 *                                    ---------------------'
 *
 *               .-----------------------------------------.
 *               |   y  |   u  |   i  |   o  |   p  | vold |
 *               |------+------+------+-------------+------|
 *               |   j  |   k  |   k  |   l  | COMP | CUML |
 * .-------------+------+------+------+------|------+------|
 * | fMOS | BSPC |   n  |   m  |   ,  |   ,  | enter| CUML |
 * |------+------+------+------+---------------------------'
 * | fSYM | space|      |
 * '--------------------'
 */
[BASE] = KEYMAP_HAND( \
        // left hand
        XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_TAB,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XL_NAV,  XM_LALT,
                                                     XXXXXXX, XM_LSFT, XM_LCTL,

        // right hand
                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_VOLD,
                          KC_H,    KC_J,    KC_K,    KC_L,    KC_COMP, MC_CUML,
        XL_MOS,  KC_BSPC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_ENTER,MC_CUML,
        XL_SYM,  KC_SPC,  XXXXXXX
 ),
/* Keymap 1: Symbol Layer
 *
 * TODO: add more exotic characters
 *
 * .-----------------------------------------.
 * |      |  @   |  _   |  [   |  ]   |   ^  |
 * |------+------+------+------+------+------|
 * |      |  \   |  /   |  {   |  }   |   *  |
 * |------+------+------+------+------+------+-------------.
 * |      |  #   |  $   |  |   |  ~   |   `  |      |      |
 * '----------------------------------+------+------+------|
 *                                    |      |      |      |
 *                                    '--------------------'

 *               .-----------------------------------------.
 *               |  !   |  <   |  >   |  =   |  &   |      |
 *               |------+------+------+------+------+------|
 *               |  ?   |  (   |  )   |  -   |  :   |      |
 * .-------------+------+------+------+------+------+------|
 * |      |      |  +   |  %   |  "   |  '   |  ;   |      |
 * |------+------+------+----------------------------------'
 * |      |      |      |
 * '--------------------'

 */
[SYM] = KEYMAP_HAND(
       // left hand
       _______, KC_AT,   KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC,
       _______, KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR,
       XXXXXXX, KC_HASH, KC_DLR,  KC_PIPE, KC_TILD, KC_GRV,  _______, _______,
                                                    _______, _______, _______,

       // right hand
                         KC_EXLM, KC_LABK, KC_RABK, KC_EQL,  KC_AMPR, _______,
                         KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_COLN, _______,
       _______, _______, KC_PLUS, KC_PERC, KC_DQT,  KC_QUOT, KC_SCLN, _______,
       _______, _______, _______
),
/* keymap 2: navigation and keypad
 *
 * .-----------------------------------------.
 * |      | PgUp | BSpac| up   | Del  | PgDn |
 * |------+------+------+------+------+------|
 * |      | Home | left | down | right| End  |
 * |------+------+------+------+------+------+-------------.
 * |      | Esc  | Tab  | Ins  | Enter| space|      |      |
 * '----------------------------------+------+------+------|
 *                                    |      |      |      |
 *                                    '--------------------'

 *               .-----------------------------------------.
 *               |  -   |  7   |  8   |  9   |  +   |      |
 *               |------+------+------+------+------+------|
 *               |  .   |  4   |  5   |  6   |  ,   |      |
 * .-------------+------+------+------+------+------+------|
 * |      |      |  :   |  1   |  2   |  3   | Enter|      |
 * |------+------+------+----------------------------------'
 * |      |      |  0   |
 * '--------------------'
 */
[NAV] = KEYMAP_HAND(
       _______, KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN,
       _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,KC_END,
       _______, KC_ESC,  KC_TAB,  KC_INS,  KC_ENTER,KC_SPACE,_______, _______,
                                                    _______, _______, _______,
       // right hand
       // TODO: use Keypad keys:
                         MC_MINS, MC_7,    MC_8,    MC_9,    MC_PLUS, _______,
                         MC_DOT,  MC_4,    MC_5,    MC_6,    MC_COMM, _______,
       _______, _______, MC_COLN, MC_1,    MC_2,    MC_3,    KC_ENTER,_______,
       _______, _______, KC_0
),
/* Keymap 3: Media and mouse keys
 *
 * TODO: more media keys
 *
 * .-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |
 * |------+------+------+------+------+------|
 * |      |  F6  |  F7  |  F8  |  F9  |  F10 |
 * |------+------+------+------+------+------+-------------.
 * |      |  F11 |  F12 | MENU | print| CAPS |      |      |
 * '----------------------------------+------+------+------|
 *                                    |      |      |      |
 *                                    '--------------------'

 *               .-----------------------------------------.
 *               |NumLck| vold | volu | mute | Mclk |      |
 *               |------+------+------+------+------+------|
 *               | Mleft| Mdown| Mup  | Mrigh| Lclk |      |
 * .-------------+------+------+------+------+------+------|
 * |      |      | mprev| mstop| mplay| mnext| Rclk |      |
 * |------+------+------+----------------------------------'
 * |      |      |      |
 * '--------------------'
 */
[MOS] = KEYMAP_HAND(
       _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
       _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
       _______, KC_F11,  KC_F12,  KC_APP,  KC_PAUS, KC_CAPS, _______, _______,
                                                    _______, _______, _______,
       // right hand
                         KC_NLCK, KC_VOLD, KC_VOLU, KC_MUTE, KC_BTN3, _______,
                         KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1, _______,
       _______, _______, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_BTN2, _______,
       _______, _______, _______
),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
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


#ifdef BACKLIGHT_ENABLE

static uint8_t usbled = 0;

void led_set_kb( uint8_t usb_led )
{
	usbled = usb_led;
}


#define MOD_ACTIVE(bits) ( keyboard_report->mods & (bits) || (\
	(get_oneshot_mods() & (bits)) \
	&& !has_oneshot_mods_timed_out() \
	) )

static uint8_t led = 0;

#endif

// Runs constantly in the background, in a loop.
void matrix_scan_user(void)
{

    mytap_matrix_scan();

#ifdef BACKLIGHT_ENABLE
	uint8_t new = 0;

	// layer

	if( layer_state ){
		new |= 1UL<<7;
	}

	// modifier
	if( MOD_ACTIVE(
        MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)
        | MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)
        | MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT)
        | MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI)
    ) ){

		new |= 1UL<<4;
	}

	// finally: set led on/off/brightness

    if( led != new ){
        backlight_set( new );
        led = new;
	}
#endif

}


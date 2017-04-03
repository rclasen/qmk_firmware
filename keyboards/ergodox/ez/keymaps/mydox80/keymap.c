#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

/*

- dox is missing keys for:
  - esc
  - backspace
  - enter

- keys in bad places
  - ctrl

- extra keys:
  - SYM - layer symbol
  - NAV - layer nav/keypad
  - MSF - layer mouse/Fx
  - GHK - global hotkey

- mouse is used with right hand. This needs the following keys on left
  side:

  base:
  - alt, shift, ctrl - to modify mouse behaviour
  - shift-insert, ctrl-insert, alt-insert, shift-delete - for copy/paste 1 
    -> shift/ctrl and insert/delete need different fingers
  - alt-tab - to switch windows
    -> alt and tab need different fingers
  - ctrl-tab - to switch documents
  - ?enter on left hand
  - ?ctrl-pgup/down - to switch tabs

  nav:
  - navkeys: cursor, page-up/down, home, end - for extra navigation
    -> navlayer toggle on left hand
  - shift with navkeys: cursor, page-up/down, home, end - for selection
    -> shift and navkeys need different fingers
  - GHK-cursor - desktop/window switching - NOT ON WINDOWS
  - ctrl-x/c/v, ctrl-shift-v - for copy/paste 2
    -> ctrl and shift and x/c/v need different fingers

  mouse:
  - direction, buttons, accel on right hand, independent

- shift/ctrl/layer modifer must be available for each hand and allow
  one-handed operation

- on each hand for alternation:
  - shift
  - SYM - layer symbol
  - ctrl ?
 
- may use 2 hands together:
  - alt-enter
  - alt-f4
  - alt-space - window menu
  - ctrl-esc  - gui menu
  - GHK-cursor - window/desk navigation
  - GHK-h/j/k/l/number/space - window/desk navigation
  - GHK-m/z/r - window manipulation
  - GHK-alpha - portable os hotkeys
  - alt-anything - windows application hotkeys
  - altgr-anything - strange characters
  - altgr-shift-anything - even more strange characters
    -> altgr and shift need different fingers
  - alt-print/sysrq-X - linux sysrq

frequent/easy to use:
= space		tap	1hold	l,r?
+ shift			hold	l,r	layer 2
- SYM			hold	l,r	layer 3
- ctrl			hold	l,r?		modifier
- backspace	tap		one
+ enter		tap	hold	one
+ NAV		tap	hold	l	layer 4

often:
+ tab		tap		l
+ esc		tap		l
= alt			hold	l,r?		modifier
= GHK			hold	l,r?		modifier
+ MSF		tap		l,r	layer

rare:
+ insert	tap		l
= altgr			hold	r,l?	layer
= gui		tap	hold	l,r?		modifier
+ delete	tap
+ print		tap
+ menu		tap		l




left main:
- tab		tap		l
- shift			hold	l,r	layer 2
- caps: NAV		tap	hold	l	layer 4
- z: SYM		hold	l,r	layer 3
left bottom:
- MSF		tap		l,r	layer
- gui		tap	hold	l,r?		modifier
- GHK			hold	l,r?		modifier
- esc: alt		hold	l,r?		modifier
- alt: esc	tap		l
left center:
- delete	tap
- menu		tap		l
- insert	tap		l
left thumb:
- space		tap	1hold	l,r
- ctrl			hold	l,r?		modifier
- backspace	tap		one

right thumb
- ctrl			hold	l,r?		modifier
- enter		tap		one
- space		tap	1hold	l,r
right center:
- print		tap
- tab		tap		l
right bottom
- esc: alt		hold	l,r?		modifier
- alt: esc	tap		l
- altgr			hold	r,l?	layer
- gui		tap	hold	l,r?		modifier
- NAV		tap	hold	l	layer 4
- MSF		tap		l,r	layer
right main:
- shift			hold	l,r	layer 2
- /: SYM		hold	l,r	layer 3

*/

// this determins the order of layers:
enum my_layer {
	BASE = 0,	// default layer
	NAV,	// navkeys, numpad
	MOS,	// mouse, Fx, media
	SYM,	// symbols
};

// for keys with custom "actions" coded in matrix_scan_user
enum my_keycodes {
	KC_BASE	= SAFE_RANGE,
};

#define TL_NAV	TG(NAV)
#define TL_MOS	TG(MOS)
#define TL_SYM	TG(SYM)

#define ML_NAV	MO(NAV)
#define ML_MOS	MO(MOS)
#define ML_SYM	MO(SYM)

#define OL_NAV	OSL(NAV)
#define OL_MOS	OSL(MOS)
#define OL_SYM	OSL(SYM)

#define OM_LALT	OSM(MOD_LALT)
#define OM_RALT	OSM(MOD_RALT)

#define OM_LCTL	OSM(MOD_LCTL)

#define OM_LGUI	OSM(MOD_LGUI)

#define OM_LSFT	OSM(MOD_LSFT)

// known as LCAG .. but only available as LCAG() / LCAG_T()
//#define OM_GHK F(F_OM_GHK)
#define OM_GHK OSM( MOD_LCTL | MOD_LALT | MOD_LGUI )






// Layer:
//
// MO momentary layer
// TG toggle layer
// OSL oneshot layer
// LT momentary layer / keycode

// Modifier
//
// KC_xx momentary modifier
// ?? toggle modifier
// OSM oneshot modifier
// -- momentary / toggle modifuer
// xx_T() momentary modifier / keycode


#define KC_UUML RALT(KC_Y)
#define KC_OUML RALT(KC_P)
#define KC_AUML RALT(KC_Q)
#define KC_SUML RALT(KC_S)

#define KC_DEGR RALT(LSFT(KC_SCLN))
#define KC_PARA RALT(LSFT(KC_S))
#define KC_POUN RALT(LSFT(KC_4))
#define KC_LDTQ RALT(KC_LBRC)
#define KC_RDTQ RALT(KC_RBRC)
#define KC_EURO RALT(KC_5)
#define KC_LSQ RALT(KC_9)
#define KC_RSQ RALT(KC_0)
#define KC_LDQ RALT(LSFT(KC_LBRC))
#define KC_RDQ RALT(LSFT(KC_RBRC))
#define KC_MUL RALT(KC_EQL)
#define KC_DIV RALT(LSFT(KC_EQL))

#define KC_LSTQ KC_NO
#define KC_RSTQ KC_NO


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  |  Del |           | Print|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  | fMOS |           | fMOS |   Y  |   U  |   I  |   O  |   P  |   ö    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | fNAV   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ü  | fNAV   |
 * |--------+------+------+------+------+------|  Ins |           |      |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   ä  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | GHK  |      | LGUI | LALT | LCTL |                                       |LShift| LAlt | GUI  | RALT | GHK  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Menu | right|       |  up  |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | Space| fSYM | left |       | down | BSPC | Enter|
 *                                 +      +      +------+       +------+      +      +
 *                                 | Space| fSYM | ESC  |       | TAB  | BSPC | Enter|
 *                                 `--------------------'       `--------------------'
 */
[BASE] = KEYMAP_80(  // layer 0 : default
        // left hand
        KC_GRV,         KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_DEL,
        KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           OL_MOS,
        OL_NAV,         KC_A,           KC_S,           KC_D,           KC_F,           KC_G,
        KC_LSFT,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           LSFT(KC_INS),
        OM_GHK,         KC_NO,          OM_LGUI,        OM_LALT,        OM_LCTL,
                                                                        // left thumb
                                                                                        KC_APP,         KC_RIGHT,
                                                                        KC_SPC,         OL_SYM,         KC_LEFT,
                                                                        KC_SPC,         OL_SYM,         KC_ESC,

        // right hand
        KC_PSCR,        KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINS,
        OL_MOS,         KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_OUML,
                        KC_H,           KC_J,           KC_K,           KC_L,           KC_UUML,        OL_NAV,
        KC_BASE,        KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_AUML,        KC_LSFT,
                                        OM_LSFT,        OM_LALT,        OM_LGUI,        OM_RALT,        OM_GHK,
        // right thumb
        KC_UP,          KC_NO,
        KC_DOWN,        KC_BSPC,        KC_ENTER,
        KC_TAB,         KC_BSPC,        KC_ENTER
    ),
/* Keymap 1: Symbol Layer
 *
 * TODO: add more exotic characters
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   °    |  §   |  £   |  «   |  »   |  EUR |      |           |      |      |  “   |  ”   |  ‘   |  ’   |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  @   |  _   |  [   |  ]   |   ^  |      |           |      |  !   |  <   |  >   |  =   |  &   |   ß    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  \   |  /   |  {   |  }   |   *  |------|           |------|  ?   |  (   |  )   |  -   |  :   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  #   |  $   |  |   |  ~   |   `  |      |           |      |  +   |  %   |  "   |  '   |  ;   |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |------|------|------|       |------|------|------|
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[SYM] = KEYMAP_80(
       // left hand
       KC_DEGR, KC_PARA, KC_POUN, KC_RDTQ, KC_LDTQ, KC_EURO, KC_TRNS,
       KC_TRNS, KC_AT,   KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC, KC_TRNS,
       KC_TRNS, KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR,
       KC_TRNS, KC_HASH, KC_DLR,  KC_PIPE, KC_TILD, KC_GRV,  KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                    KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_LDQ,  KC_RDQ,  KC_LSQ,  KC_RSQ,  KC_TRNS,
       KC_TRNS, KC_EXLM, KC_LABK, KC_RABK, KC_EQL,  KC_AMPR, KC_SUML,
                KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_COLN, KC_TRNS,
       KC_TRNS, KC_PLUS, KC_PERC, KC_DQT,  KC_QUOT, KC_SCLN, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* keymap 2: navigation and keypad
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | CAPS   |      |      |  >   |   <  |      |      |           |      | Tab  |NumLck|  /   |  *   |  ÷   |   ×    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | PgUp | BSpac| up   | Del  | PgDn |      |           |      |  -   |  7   |  8   |  9   |  +   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Home | left | down | right| End  |------|           |------|  .   |  4   |  5   |  6   |  ,   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Esc  | Tab  | Ins  | Enter|      |      |           |      |  :   |  1   |  2   |  3   |  ;   |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |  0   |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+----------.
 *                                 |      |      |      |       |      |      |          |
 *                                 |------|------|------|       |------|------|----------|
 *                                 |      |      |      |       |      |      |          |
 *                                 `--------------------'       `------------------------'
 */
[NAV] = KEYMAP_80(
       KC_CAPS, KC_TRNS, KC_TRNS, KC_LSTQ, KC_RSTQ, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN, KC_TRNS,
       KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,KC_END,
       KC_TRNS, KC_ESC,  KC_TAB,  KC_INS,  KC_ENTER,KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                    KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       // TODO: use Keypad keys:
       KC_TRNS, KC_TAB,  KC_NLCK, KC_SLSH, KC_ASTR, KC_DIV,  KC_MUL,
       KC_TRNS, KC_MINS, KC_7,    KC_8,    KC_9,    KC_PLUS, KC_TRNS,
                KC_DOT,  KC_4,    KC_5,    KC_6,    KC_COMM, KC_TRNS,
       KC_TRNS, KC_COLN, KC_1,    KC_2,    KC_3,    KC_SCLN, KC_TRNS,
                         SFT_T(KC_0), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 3: Media and mouse keys
 *
 * TODO: more media keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 | VolD   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |  F11 |  F12 | Mup  |      | Mclk | VolUp  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      | Mleft| Mdown| Mrigh| Lclk |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      | mprev| mstop| mplay| mnext| Rclk |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+----------.
 *                                 |      |      |      |       |      |      |          |
 *                                 |------|------|------|       |------|------|----------|
 *                                 |      |      |      |       |      |      |          |
 *                                 `--------------------'       `------------------------'
 */
[MOS] = KEYMAP_80(
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                    KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_VOLD,
       KC_TRNS, KC_F11,  KC_F12,  KC_MS_U, KC_TRNS, KC_BTN3, KC_VOLU,
                KC_NO,   KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1, KC_TRNS,
       KC_TRNS, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_BTN2, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode){
        case KC_BASE:
            if( record->event.pressed ){
                clear_oneshot_mods();
                clear_oneshot_locked_mods();
                unregister_mods(get_mods());

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

void led_set_kb( uint8_t usb_led ){
	usbled = usb_led;
}


#define MOD_ACTIVE(bits) ( keyboard_report->mods & bits || (\
	(get_oneshot_mods() & bits) \
	&& !has_oneshot_mods_timed_out() \
	) )

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

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

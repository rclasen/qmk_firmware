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
  - ?enter on left hand

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

#define BASE 0 // default layer
#define SYM 1 // symbols
#define NAV 2 // navkeys, numpad
#define MOS 3 // mouse, Fx, media

#define CMG LCTL(LALT(KC_LGUI))

enum my_keycodes {
  LSYM = SAFE_RANGE,
  LNAV,
  LMOS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  |  Del |           | Print|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  | fMOS |           | fMOS |   Y  |   U  |   I  |   O  |   P  |   =    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | fNAV   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|  Ins |           | fNAV |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | hSYM | hSYM | GUI  | CMG  |Alt Esc|                                      | RAlt | LAlt | GUI  | hSYM | hSYM |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      | Menu |       | Tab  |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | Space| LCtrl|      |       |      | Enter| Space|
 *                                 +      +      +------+       +------+      +      +
 *                                 | Space| LCtrl| BSPC |       | BSPC | Enter|ctl/sp|
 *                                 `--------------------'       `--------------------'
 */
[BASE] = KEYMAP_80(  // layer 0 : default
        // left hand
        KC_GRV,         KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_DEL,
        KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           LMOS,
        LNAV,           KC_A,           KC_S,           KC_D,           KC_F,           KC_G,
        KC_LSFT,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_INS,
        MO(SYM),        MO(SYM),        KC_LGUI,        CMG,            ALT_T(KC_ESC),
                                                                        // left thumb
                                                                                        KC_NO,          KC_APP,
                                                                        KC_SPC,         KC_LCTL,        KC_NO,
                                                                        KC_SPC,         KC_LCTL,        KC_BSPC,

        // right hand
        KC_PSCR,        KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINS,
        LMOS,           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_EQL,
                        KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_QUOT,
        LNAV,           KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,        KC_RSFT,
                                        KC_RALT,        KC_LALT,        KC_LGUI,        MO(SYM),        MO(SYM),
        // right thumb
        KC_TAB,         KC_NO,
        KC_NO,          KC_ENTER,       KC_SPC,
        KC_BSPC,        KC_ENTER,       CTL_T(KC_SPC)
    ),
/* Keymap 1: Symbol Layer
 *
 * TODO: add more exotic characters
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |Version |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |  _   |  [   |  ]   |   ^  |      |           |      |  !   |  <   |  >   |  =   |  &   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  \   |  /   |  {   |  }   |   *  |------|           |------|  ?   |  (   |  )   |  -   |  :   |  @     |
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
       M(0),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC, KC_TRNS,
       KC_TRNS, KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR,
       KC_TRNS, KC_HASH, KC_DLR,  KC_PIPE, KC_TILD, KC_GRV,  KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                    KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_EXLM, KC_LABK, KC_RABK, KC_EQL,  KC_AMPR, KC_TRNS,
                KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_COLN, KC_AT,
       KC_TRNS, KC_PLUS, KC_PERC, KC_DQT,  KC_QUOT, KC_SCLN, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* keymap 2: navigation and keypad
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | CAPS   |      |      |      |      |      |      |           |      |      |      | Tab  |  /   |  *   |  -     |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | PgUp | BSpac| up   | Del  | PgDn |      |           |      |      |  7   |  8   |  9   |  +   |  -     |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Home | left | down | right| End  |------|           |------|      |  4   |  5   |  6   |  ,   |  .     |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Esc  | Tab  | Ins  | Enter|      |      |           |      |  :   |  1   |  2   |  3   |  ;   |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+----------.
 *                                 |      |      |      |       |      |      |     0    |
 *                                 |------|------|------|       |------|------|----------|
 *                                 |      |      |      |       |      |      |     0    |
 *                                 `--------------------'       `------------------------'
 */
[NAV] = KEYMAP_80(
       KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN, KC_TRNS,
       KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,KC_END,
       KC_TRNS, KC_ESC,  KC_TAB,  KC_INS,  KC_ENTER,KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                    KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       // TODO: use Keypad keys:
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TAB,  KC_SLSH, KC_ASTR, KC_MINS,
       KC_TRNS, KC_TRNS, KC_7,    KC_8,    KC_9,    KC_PLUS, KC_MINS,
                KC_TRNS, KC_4,    KC_5,    KC_6,    KC_COMM, KC_DOT,
       KC_TRNS, KC_COLN, KC_1,    KC_2,    KC_3,    KC_SCLN, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_0,
       KC_TRNS, KC_TRNS, KC_0
),
/* Keymap 3: Media and mouse keys
 *
 * TODO: more media keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 | VolD   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Mup  |      | Mclk | VolUp  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      | Mleft| Mdown| Mrigh| Lclk | Mute   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      | mprev| mstop| mplay| mnext|      |           |      |      |      |      |      | Rclk |        |
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
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                    KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_VOLD,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_BTN3, KC_VOLU,
                KC_NO,   KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN1, KC_MUTE,
       KC_TRNS, KC_WBAK, KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN2, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

/*
const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYM),                // FN1 - Momentary Layer 1 (Symbols)
    [2] = ACTION_LAYER_TAP_TOGGLE(NAV),                // FN2 - Momentary Layer 2 (Navigation)
    [3] = ACTION_LAYER_TAP_TOGGLE(MOS),                // FN3 - Momentary Layer 3 (Mouse/Fx/Media)
};
*/

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
    switch(id) {
      case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;

    }

    return MACRO_NONE;
};

static uint16_t lsym_timer;
static bool lsym_active;

static uint16_t lnav_timer;
static bool lnav_active;

static uint16_t lmos_timer;
static bool lmos_active;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode){
      case LSYM:
        if( record->event.pressed ){
            lsym_timer = timer_read();
            lsym_active = layer_state & 1UL<<SYM;
            layer_on(SYM);

        } else if( timer_elapsed(lsym_timer) > 150 ){
            layer_off(SYM);

        } else {
           if( lsym_active )
               layer_off(SYM);
        }
        break;

      case LNAV:
        if( record->event.pressed ){
            lnav_timer = timer_read();
            lnav_active = layer_state & 1UL<<NAV;
            layer_on(NAV);

        } else if( timer_elapsed(lnav_timer) > 150 ){
            layer_off(NAV);

        } else {
           if( lnav_active )
               layer_off(NAV);
        }
        break;

      case LMOS:
        if( record->event.pressed ){
            lmos_timer = timer_read();
            lmos_active = layer_state & 1UL<<MOS;
            layer_on(MOS);

        } else if( timer_elapsed(lmos_timer) > 150 ){
            layer_off(MOS);

        } else {
           if( lmos_active )
               layer_off(MOS);
        }
        break;

    }

    return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    if( layer_state & 1UL<<SYM ){
            ergodox_right_led_1_on();
    }

    if( layer_state & 1UL<<MOS ){
            ergodox_right_led_2_on();
    }

    if( layer_state & 1UL<<NAV ){
            ergodox_right_led_3_on();
    }

};

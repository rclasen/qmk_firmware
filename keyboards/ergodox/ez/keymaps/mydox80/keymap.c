#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

/*

- mouse is used with left hand. This needs the following keys on right
  side:

  base:
  - alt, shift, ctrl - to modify mouse behaviour
  - shift-insert, ctrl-insert, alt-insert, shift-delete - for copy/paste 1 
    -> shift/ctrl and insert/delete need different fingers
  - alt-tab - to switch windows
    -> alt and tab need different fingers

  nav:
  - navkeys: cursor, page-up/down, home, end - for extra navigation
    -> navlayer toggle on right hand
  - shift with navkeys: cursor, page-up/down, home, end - for selection
    -> shift and navkeys need different fingers
  - <something>-cursor - desktop/window switching - NOT ON WINDOWS
  - ctrl-x/c/v, ctrl-shift-v - for copy/paste 2
    -> ctrl and shift and x/c/v need different fingers

- shift/ctrl/layer modifer must be available for each hand and allow
  one-handed operation

- may use 2 hands:
  - alt-f4
  - alt-space - window menu
  - ctrl-esc  - gui menu
  - <something>-cursor - window/desk navigation
  - <something>-h/j/k/l/number/space - window/desk navigation
  - <something>-m/z/r - window manipulation
  - <something>-alpha - portable os hotkeys
  - alt-anything - windows application hotkeys
  - altgr-anything - strange characters
  - altgr-shift-anything - even more strange characters
    -> altgr and shift need different fingers

easy to use:
- space
- shift
- backspace
- tab
- ctrl
- enter
- esc
- symbol layer
- nav layer

rare:
- insert
- alt
- altgr
- delete
- print

right center:
 - delete
 - tab
 - insert
right main:
 - nav: xcv
 - nav: navkeys
 - shift
right bottom
 - symbol layer
 - nav layer
right thumb hot:
 - space (hot)
 - enter (hot)
 - ctrl (in reach of main/center)
 - alt

left center:
 - print
 - esc
left main:
 - shift
left bottom:
 - symbol layer
 - nav layer
left thumb:
 - space (hot)
 - backspace (hot)
 - ctrl (in reach of main/center)
 - altgr
*/

#define BASE 0 // default layer
#define SYM 1 // symbols
#define NAV 2 // media keys

#define CMG LCTL(LALT(KC_LGUI))

enum planck_keycodes {
  LSYM = SAFE_RANGE,
  LNAV,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  | Print|           | Del  |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  Esc |           | TAB  |   Y  |   U  |   I  |   O  |   P  |   =    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  \     |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           | Ins  |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LCtrl| LAlt | CMG  | LNAV | LSYM |                                       | LSYM | LNAV | CMG  | Menu | RCtrl|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | RAlt | LGui |       | RGui | RAlt |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | Space|BackSp| LAlt |       | LAlt | Enter| Space|
 *                                 |------|------|------|       |------|------|------|
 *                                 | Spave|BackSp| LCtrl|       | RCtrl| Enter| Space|
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP_80(  // layer 0 : default
        // left hand
        KC_GRV,         KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_PSCR,
        KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_ESC,
        KC_BSLS,        KC_A,           KC_S,           KC_D,           KC_F,           KC_G,
        KC_LSFT,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_NO,
        KC_LCTL,        KC_LALT,        CMG,            LNAV,           LSYM,
        // left thumb
                                                                                        KC_RALT,        KC_LGUI,
                                                                        KC_SPC,         KC_BSPC,        KC_LALT,
                                                                        KC_SPC,         KC_BSPC,        KC_LCTL,
        // right hand
        KC_DEL,         KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINS,
        KC_TAB,         KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_EQL,
                        KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_QUOT,
        KC_INS,         KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,        KC_RSFT,
                                        LSYM,           LNAV,           CMG,            KC_MENU,        KC_RCTL,
        // right thumb
        KC_RGUI,        KC_RALT,
        KC_LALT,        KC_ENTER,       KC_SPC,
        KC_RCTL,        KC_ENTER,       KC_SPC
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |Version |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |      |   &  |   *  |      |   :  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------|   -  |   +  |   =  |   \  |  #;  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   _  |   ?  |  #,  |  #.  |  #/  |        |
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
// SYMOLS
[SYM] = KEYMAP_80(
       // left hand
       M(0),   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  KC_TRNS,
       KC_TRNS, KC_TRNS, KC_AMPR,KC_ASTR, KC_TRNS, KC_TRNS, KC_TRNS,
                KC_MINUS,KC_PLUS,KC_EQL,  KC_BSLS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_UNDS, KC_QUES,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                         KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | Mclk |      | MsUp |      |      |      |           |      | HOME | PgDn | PgDn | End  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Lclk |MsLeft|MsDown|MsRght|      |------|           |------| LEFT | DOWN | UP   | RIGHT|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Rclk | mprev| mstop| mplay| mnext|      |           |      |      | cut  | copy | paste| ptext|        |
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
// MEDIA AND MOUSE
[NAV] = KEYMAP_80(
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
       KC_TRNS, KC_BTN3, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_BTN2, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS, KC_VOLU,
       KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS, KC_MUTE,
                KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_TRNS, KC_TRNS,
       KC_TRNS, KC_WBAK, LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LSFT(LCTL(KC_V)), KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYM),                // FN1 - Momentary Layer 1 (Symbols)
    [2] = ACTION_LAYER_TAP_TOGGLE(NAV),                // FN2 - Momentary Layer 2 (mmoving)
};

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

static uint16_t lsymb_timer;
bool lsymb_active;

static uint16_t lmove_timer;
bool lmove_active;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode){
      case LSYM:
        if( record->event.pressed ){
            lsymb_timer = timer_read();
            lsymb_active = layer_state & 1UL<<SYM;
            layer_on(SYM);

        } else if( timer_elapsed(lsymb_timer) > 150 ){
            layer_off(SYM);

        } else {
           if( lsymb_active )
               layer_off(SYM);
        }
        break;

      case LNAV:
        if( record->event.pressed ){
            lmove_timer = timer_read();
            lmove_active = layer_state & 1UL<<NAV;
            layer_on(NAV);

        } else if( timer_elapsed(lmove_timer) > 150 ){
            layer_off(NAV);

        } else {
           if( lmove_active )
               layer_off(NAV);
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

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
        case SYM:
            ergodox_right_led_1_on();
            break;
        case NAV:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};

#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MOVE 2 // media keys

/*
 - 2h		shift
 - ?h	2t	space
 - h	t	backspace
 -	t	tab
 - 2h		ctrl
 -	t	enter
 - 	t	esc

 - 2h	t	symbol layer
 - 2h	t	win/super

 - h		alt
 - h		altgr/l3shift

 - 1h	1t	motion layer

 - 	t	insert
 - 	t	delete
 - 	t	print

left:
 - ctrl/esc

 - space
 - tab

right:
 - space
 - ctrl
 - enter
 - backspace

*/
enum planck_keycodes {
  LSYMB = SAFE_RANGE,
  LMOVE,
};

// AltGr and GUI
#define RAG(kc) (kc | QK_RALT | QK_LGUI)
#define RAG_T(kc) MT(( MOD_RALT | MOD_LGUI), kc)
#define KC_RAG RAG(KC_NO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  | DOWN |           |  UP  |   Y  |   U  |   I  |   O  |   P  |   =    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |  \     |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |  L2  |           |  L2  |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LCtrl| LGui | Alt  | AltGr|  L1  |                                       |  L1  | AltGr| Alt  | RGui | RCtrl|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | Esc  | PRINT|       | DEL  | Ins  |
 *                                 ,------|------|------|       |------+------+------.
 *                                 | Space|BackSp| CAG  |       | LGui | Enter| Space|
 *                                 |------|------|------|       |------|------|------|
 *                             | Tab/LCtrl|LShift| AltGr|       | Alt  |Rshift/Tab| RCtrl|
 *                                 `--------------------'       `--------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP_80(  // layer 0 : default
        // left hand
        KC_GRV,         KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_LEFT,
        KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_DOWN,
        KC_BSLS,        KC_A,           KC_S,           KC_D,           KC_F,           KC_G,
        KC_LSFT,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           LMOVE,
        KC_LCTRL,       KC_LGUI,        KC_LALT,        KC_RALT,        LSYMB,
        // left thumb
                                                                                        KC_ESC,         KC_PSCR,
                                                                        KC_SPC,         KC_BSPC,        KC_FN3,
                                                                        KC_LCTL,        SFT_T(KC_TAB),  KC_RALT,
        // right hand
        KC_RGHT,        KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINS,
        KC_UP,          KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_EQL,
                        KC_H,           KC_J,           KC_K,           KC_L,           KC_SCLN,        KC_QUOT,
        LMOVE,          KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_SLSH,        KC_RSFT,
                                        LSYMB,          KC_RALT,        KC_LALT,        KC_RGUI,        KC_RCTRL,
        // right thumb
        KC_DEL,         KC_INS,
        KC_LGUI,        KC_ENTER,       KC_SPC,
        KC_LALT,        SFT_T(KC_TAB),  KC_RCTRL
    ),
/* Keymap 1: Symbol Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |Version |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   /  |   7  |   8  |   9  |   *  |   F12  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------|   -  |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ;  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |------|------|------|       |------|------|------|
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = KEYMAP_80(
       // left hand
       M(0),   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_SCLN,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_SLSH, KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_MINUS,KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_TRNS,KC_0,    KC_DOT,  KC_EQL,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        | prev | stop | play | next |      |      |           |      | MUTE | VolDn| VolUp|      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      | HOME | PgDn | PgDn | End  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Lclk |MsLeft|MsDown|MsRght|      |------|           |------| LEFT | DOWN | UP   | RIGHT|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Rclk |      |      |      |      |      |           |      | BBack|      |      | BFwd |      |        |
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
[MOVE] = KEYMAP_80(
       KC_TRNS, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_BTN1, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_BTN2, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_TRNS, KC_TRNS,
                 KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_WBAK, KC_TRNS, KC_TRNS, KC_WFWD, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB),                // FN1 - Momentary Layer 1 (Symbols)
    [2] = ACTION_LAYER_TAP_TOGGLE(MOVE),                // FN2 - Momentary Layer 2 (mmoving)
    [3] = ACTION_MODS( MOD_LCTL | MOD_LALT | MOD_LGUI )
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
      case LSYMB:
        if( record->event.pressed ){
            lsymb_timer = timer_read();
            lsymb_active = layer_state & 1UL<<SYMB;
            layer_on(SYMB);

        } else if( timer_elapsed(lsymb_timer) > 150 ){
            layer_off(SYMB);

        } else {
           if( lsymb_active )
               layer_off(SYMB);
        }
        break;

      case LMOVE:
        if( record->event.pressed ){
            lmove_timer = timer_read();
            lmove_active = layer_state & 1UL<<MOVE;
            layer_on(MOVE);

        } else if( timer_elapsed(lmove_timer) > 150 ){
            layer_off(MOVE);

        } else {
           if( lmove_active )
               layer_off(MOVE);
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
        case SYMB:
            ergodox_right_led_1_on();
            break;
        case MOVE:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};

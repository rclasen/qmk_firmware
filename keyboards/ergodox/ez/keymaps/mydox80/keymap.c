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

- TODO: rctrl for virtualbox/...

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

#define MYTAP_MAX  16

// for keys with custom "actions" coded in matrix_scan_user
enum my_keycodes {
	KC_BASE	= SAFE_RANGE,

    KC_MYTAP,
    KC_MYTAP_MAX = KC_MYTAP + MYTAP_MAX,
};

/************************************************************
 * mytap global
 */

enum mytap_state {
    MYTAP_STATE_OFF,
    MYTAP_STATE_TAPPING,
    MYTAP_STATE_HOLD,
    MYTAP_STATE_ONESHOT,
    MYTAP_STATE_LOCKED,
};

typedef struct {
    bool pressed;
    enum mytap_state state;
    enum mytap_state last;
    bool locked;
    uint8_t count;
    uint16_t timer;
} mytap_state_t;

typedef void (*mytap_fn_t)( mytap_state_t *state, void *data );

typedef struct {
    mytap_state_t state;
    struct {
        mytap_fn_t on_press;
        mytap_fn_t on_release;
    } fn;
    void *data;
} mytap_action_t;

#define XT(n) (KC_MYTAP + n)

extern mytap_action_t mytap_actions[];

// index of highest used mytap action:
static int8_t mytap_highest = -1;
// inext of action currently in tapping sequence:
static int8_t mytap_tapping = -1;

// other key was pressed, active oneshots are to be released:
static bool mytap_oneshot_cleanup = false;

// any state -> OFF
//
// - when a held mytap is released
// - after a oneshot key was sent
// - after ONESHOT_TIMEOUT
// - when locking was ended
void mytap_release( uint8_t idx )
{
    mytap_action_t *action = &mytap_actions[idx];

    dprintf("mytap_release idx=%d oldstate=%d\n", idx, action->state.state);
    if( action->fn.on_release )
        (*action->fn.on_release)( &action->state, action->data );

    action->state.state = MYTAP_STATE_OFF;
}

// any state -> TAPPING
//
// on first press of a tapping / hold sequence
void mytap_tapping_begin( uint8_t idx )
{
    mytap_action_t *action = &mytap_actions[idx];

    dprintf("mytap_begin idx=%d oldstate=%d\n", idx, action->state.state);
    if( action->fn.on_press )
        (*action->fn.on_press)( &action->state, action->data );

    action->state.count = 0;
    action->state.last = action->state.state;
    action->state.state = MYTAP_STATE_TAPPING;
    mytap_tapping = idx;
}

// TAPPING -> new state
//
// when tapping sequenced ended
// - by TAPPING_TERM timeout or
// - by other key
void mytap_tapping_end( uint8_t idx )
{
    mytap_action_t *action = &mytap_actions[idx];

    if( action->state.pressed ){
        // tapping ended by timeout or non-mytap key
        dprintf("mytap_tapping_end idx=%d oldstate=%d hold\n", idx, action->state.state );
        action->state.state = MYTAP_STATE_HOLD;

    } else if( action->state.count > ONESHOT_TAP_TOGGLE ){
        dprintf("mytap_tapping_end idx=%d oldstate=%d abort\n", idx, action->state.state );
        mytap_release( idx );

    } else if( action->state.count == ONESHOT_TAP_TOGGLE ){
        dprintf("mytap_tapping_end idx=%d oldstate=%d lock\n", idx, action->state.state );
        action->state.state = MYTAP_STATE_LOCKED;

    // count < ONESHOT_TAP_TOGGLE:

    } else if( action->state.last == MYTAP_STATE_LOCKED ){
        dprintf("mytap_tapping_end idx=%d oldstate=%d unlock\n", idx, action->state.state );
        mytap_release( idx );

    } else {
        dprintf("mytap_tapping_end oldstate=%d oneshot\n", idx, action->state.state );
        action->state.state = MYTAP_STATE_ONESHOT;
    }

    mytap_tapping = -1;
}

// set all to OFF ... to be called by user
void mytap_clear(void)
{
    dprintf("mytap_clear highest=%d\n", mytap_highest );

    for( int8_t i = 0; i <= mytap_highest; ++i ){
        mytap_action_t *action = &mytap_actions[i];

        if( action->state.state != MYTAP_STATE_OFF )
            mytap_release( i );
    }
    mytap_tapping = -1;
    mytap_oneshot_cleanup = false;
}

void mytap_matrix_scan(void)
{
    for( int8_t i = 0; i <= mytap_highest; ++i ){
        mytap_action_t *action = &mytap_actions[i];

        switch(action->state.state){
            case MYTAP_STATE_TAPPING:
                if( timer_elapsed(action->state.timer) > TAPPING_TERM ){
                    dprintf("mytap_scan idx=%d oldstate=%d tapping_term\n", i, action->state.state );
                    mytap_tapping_end( i );
                }
                break;

            case MYTAP_STATE_ONESHOT:
                if( mytap_oneshot_cleanup ){
                    dprintf("mytap_scan idx=%d oldstate=%d oneshot_cleanup\n", i, action->state.state );
                    mytap_release( i );

                } else if( timer_elapsed(action->state.timer) > ONESHOT_TIMEOUT ){
                    dprintf("mytap_scan idx=%d oldstate=%d oneshot_timeout\n", i, action->state.state );
                    mytap_release( i );
                }
                break;

            default:
                break;
        }
    }

    mytap_oneshot_cleanup = false;
}

bool mytap_process_record(uint16_t keycode, keyrecord_t *record)
{
    switch(keycode){
        case KC_MYTAP ... KC_MYTAP_MAX:
        {
            int8_t idx = keycode - KC_MYTAP;
            mytap_action_t *action = &mytap_actions[idx];

            if( idx > mytap_highest )
                mytap_highest = idx;

            action->state.pressed = record->event.pressed;

            if( record->event.pressed ){
                dprintf("mytap_record idx=%d oldstate=%d oldcount=%d tapping=%d pressed\n",
                    idx, action->state.state, action->state.count,
                    mytap_tapping );

                if( action->state.state != MYTAP_STATE_TAPPING )
                    mytap_tapping_begin( idx );

                action->state.timer = timer_read();
                ++(action->state.count);


            } else {
                dprintf("mytap_record idx=%d oldstate=%d release\n", idx, action->state.state);
                if( action->state.state == MYTAP_STATE_HOLD
                        || timer_elapsed(action->state.timer) > TAPPING_TERM )

                    mytap_release( idx );

            }

            break;

        }
        default:
            // TODO- ignore further special keys:
            // layer keys, space cadet, ...
            if( record->event.pressed && !IS_MOD(keycode) ){
                dprint("mytap other pressed\n" );

                if( mytap_tapping != -1 )
                    mytap_tapping_end( mytap_tapping );

                mytap_oneshot_cleanup = true;
            }
            break;
    }

    return true;
}

/************************************************************
 * mytap layer
 */

typedef struct {
    uint8_t layer;
} mytap_layer_data_t;


void mytap_layer_press ( mytap_state_t *state, void *data )
{
    mytap_layer_data_t *ldata = (mytap_layer_data_t *)data;

    layer_on(ldata->layer);
}

void mytap_layer_release ( mytap_state_t *state, void *data )
{
    mytap_layer_data_t *ldata = (mytap_layer_data_t *)data;

    layer_off(ldata->layer);
}

/************************************************************
 * mytap mod
 */

#define MYTAP_LAYER(layer) { \
        .fn = { mytap_layer_press, mytap_layer_release }, \
        .data = (void*)&( (mytap_layer_data_t) { layer } ), \
    }

typedef struct {
    uint8_t mod;
} mytap_mod_data_t;


void mytap_mod_press ( mytap_state_t *state, void *data )
{
    mytap_mod_data_t *mdata = (mytap_mod_data_t *)data;

    register_mods(mdata->mod);
}

void mytap_mod_release ( mytap_state_t *state, void *data )
{
    mytap_mod_data_t *mdata = (mytap_mod_data_t *)data;

    unregister_mods(mdata->mod);
}

#define MYTAP_MOD(mod) { \
        .fn = { mytap_mod_press, mytap_mod_release }, \
        .data = (void*)&( (mytap_mod_data_t) { mod } ), \
    }


/************************************************************
 * mytap user config
 */

enum mytap {
    TSYM,
    TNAV,
    TMOS,

    TLSFT,
    TLCTL,
    TRCTL,
    TLALT,
    TRALT,
    TLGUI,
    TGHK,

    TMAX,
};

// TODO& RSFT doesn't work: register_mods( KC_RSFT) registers lsft + rctrl

#if TMAX > MYTAP_MAX
#error not enough keycodes for mytap
#endif

static bool shift_enabled = false;

void mytap_sym_layer_press ( mytap_state_t *state, void *data )
{
    (void)data;

    unregister_mods(MOD_LSFT);
    layer_on(SYM);
}

void mytap_sym_layer_release ( mytap_state_t *state, void *data )
{
    (void)data;

    if(shift_enabled)
        register_mods(MOD_LSFT);

    layer_off(SYM);
}

void mytap_shift_mod_press ( mytap_state_t *state, void *data )
{
    (void)data;

    shift_enabled = true;
    register_mods(MOD_LSFT);
}

void mytap_shift_mod_release ( mytap_state_t *state, void *data )
{
    (void)data;

    shift_enabled = false;
    unregister_mods(MOD_LSFT);
}



mytap_action_t mytap_actions[] = {
    [TSYM] = {
        .fn = {
            .on_press = mytap_sym_layer_press,
            .on_release = mytap_sym_layer_release,
        },
        .data = NULL,
    },
    [TNAV] = MYTAP_LAYER( NAV ),
    [TMOS] = MYTAP_LAYER( MOS ),
    [TLSFT] = {
        .fn = {
            .on_press = mytap_shift_mod_press,
            .on_release = mytap_shift_mod_release,
        },
        .data = NULL,
    },
    [TLCTL] = MYTAP_MOD( MOD_LCTL ),
    [TRCTL] = MYTAP_MOD( MOD_RCTL ),
    [TLALT] = MYTAP_MOD( MOD_LALT ),
    [TRALT] = MYTAP_MOD( MOD_RALT ),
    [TLGUI] = MYTAP_MOD( MOD_LGUI ),
    [TGHK] = MYTAP_MOD( MOD_LCTL | MOD_LALT | MOD_LGUI ),
};

/************************************************************
 * macro user config
 */

enum {
    M_0,
    M_1,
    M_2,
    M_3,
    M_4,
    M_5,
    M_6,
    M_7,
    M_8,
    M_9,
    M_COLN,
    M_DOT,
    M_MINS,
    M_SCLN,
    M_COMM,
    M_PLUS,
};

void mod_tmp( uint16_t keycode, uint8_t suppress, uint8_t add )
{

    uint8_t mods = get_mods();
    uint8_t disable = mods & suppress;
    uint8_t enable = ~mods & add;

    if(disable)
        unregister_mods(disable);
    if(enable)
        register_mods(enable);

    register_code(keycode);
    unregister_code(keycode);

    if(enable)
        unregister_mods(enable);
    if(disable)
        register_mods(disable);
}

#define noshiftralt(code) mod_tmp(code, MOD_LSFT | MOD_RSFT | MOD_LSFT, 0 )

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch(id) {
        case M_0: // ACTION_MACRO_TAP(M_0),
            if (record->event.pressed) {
                register_mods(MOD_LSFT);
            } else {
                unregister_mods(MOD_LSFT);

                if (record->tap.count && !record->tap.interrupted) {
                    noshiftralt(KC_0);
                }
                record->tap.count = 0;
            }
            break;

        case M_1: // M(M_1),
            if(record->event.pressed)
                noshiftralt(KC_1);
            break;

        case M_2: // M(M_2),
            if(record->event.pressed)
                noshiftralt(KC_2);
            break;

        case M_3: // M(M_3),
            if(record->event.pressed)
                noshiftralt(KC_3);
            break;

        case M_4: // M(M_4),
            if(record->event.pressed)
                noshiftralt(KC_4);
            break;

        case M_5: // M(M_5),
            if(record->event.pressed)
                noshiftralt(KC_5);
            break;

        case M_6: // M(M_6),
            if(record->event.pressed)
                noshiftralt(KC_6);
            break;

        case M_7: // M(M_7),
            if(record->event.pressed)
                noshiftralt(KC_7);
            break;

        case M_8: // M(M_8),
            if(record->event.pressed)
                noshiftralt(KC_8);
            break;

        case M_9: // M(M_9),
            if(record->event.pressed)
                noshiftralt(KC_9);
            break;

        case M_COLN: // M(M_COLN),
            if(record->event.pressed)
                mod_tmp(KC_SCLN, MOD_RALT, MOD_LSFT);
            break;

        case M_DOT: // M(M_DOT),
            if(record->event.pressed)
                noshiftralt(KC_DOT);
            break;

        case M_MINS: // M(M_MINS),
            if(record->event.pressed)
                noshiftralt(KC_MINS);
            break;

        case M_SCLN: // M(M_SCLN),
            if(record->event.pressed)
                noshiftralt(KC_SCLN);
            break;

        case M_COMM: // M(M_COMM),
            if(record->event.pressed)
                noshiftralt(KC_COMM);
            break;

        case M_PLUS: // M(M_PLUS),
            if(record->event.pressed)
                mod_tmp(KC_EQL, MOD_RALT, MOD_LSFT);
            break;

    }
    return MACRO_NONE;
};

/************************************************************
 * action user config
 */

enum {
    F_0,
    F_MAX,
};

#if F_MAX > 31
#warn youo might have issues with too many fn_actions
#endif

const uint16_t PROGMEM fn_actions[] = {
    [F_0] = ACTION_MACRO_TAP(M_0),
};


/************************************************************
 * keymap user macros
 */

#define TL_NAV	TG(NAV)
#define TL_MOS	TG(MOS)
#define TL_SYM	TG(SYM)

#define ML_NAV	MO(NAV)
#define ML_MOS	MO(MOS)
#define ML_SYM	MO(SYM)

#define OL_NAV	OSL(NAV)
#define OL_MOS	OSL(MOS)
#define OL_SYM	OSL(SYM)

#define XL_NAV	XT(TNAV)
#define XL_MOS	XT(TMOS)
#define XL_SYM	XT(TSYM)

#define OM_LALT	OSM(MOD_LALT)
#define OM_RALT	OSM(MOD_RALT)

#define OM_LCTL	OSM(MOD_LCTL)
#define OM_RCTL	OSM(MOD_RCTL)

#define OM_LGUI	OSM(MOD_LGUI)

#define OM_LSFT	OSM(MOD_LSFT)

#define OM_GHK OSM( MOD_LCTL | MOD_LALT | MOD_LGUI )

#define XM_LALT	XT(TLALT)
#define XM_RALT	XT(TRALT)

#define XM_LCTL	XT(TLCTL)
#define XM_RCTL	XT(TRCTL)

#define XM_LGUI	XT(TLGUI)

#define XM_LSFT	XT(TLSFT)

#define XM_GHK XT(TGHK)

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


// https://tstarling.com/stuff/ComposeKeys.html

#define KC_UUML RALT(KC_Y)  // ü - compose "u
#define KC_OUML RALT(KC_P)  // ö - compose "o
#define KC_AUML RALT(KC_Q)  // ä - compose "a
#define KC_SUML RALT(KC_S)  // ß - compose ss

#define KC_DEGR RALT(LSFT(KC_SCLN)) // ° - compose oo
#define KC_PARA RALT(LSFT(KC_S))    // § - compose so
#define KC_POUN RALT(LSFT(KC_4))    // £ - compose -L
#define KC_LDTQ RALT(KC_LBRC)   // « - compose <<
#define KC_RDTQ RALT(KC_RBRC)   // » - compose >>
#define KC_EURO RALT(KC_5)  // € - compose =C
// open single quote ‚ - compose ,'
#define KC_LSQ RALT(KC_9)   // ‘ - compose <'
#define KC_RSQ RALT(KC_0)   // ’ - compose >'
// open double quote „ - compose ,"
#define KC_LDQ RALT(LSFT(KC_LBRC))  // “ - compose <"
#define KC_RDQ RALT(LSFT(KC_RBRC))  // ” - compose >"
#define KC_MUL RALT(KC_EQL) // × - compose xx
#define KC_DIV RALT(LSFT(KC_EQL))   // ÷ - compose -:
// quarter ¼ - compose 14
// high 4 ⁴ - compose ^4

#define KC_LSTQ KC_NO   // left single triangle quote - compose .>
#define KC_RSTQ KC_NO   // right single triangle quote - compose .<

// macros/functions that block modifiers:
#define MC_0        F(F_0)
#define MC_1        M(M_1)
#define MC_2        M(M_2)
#define MC_3        M(M_3)
#define MC_4        M(M_4)
#define MC_5        M(M_5)
#define MC_6        M(M_6)
#define MC_7        M(M_7)
#define MC_8        M(M_8)
#define MC_9        M(M_9)
#define MC_COLN     M(M_COLN)
#define MC_DOT      M(M_DOT)
#define MC_MINS     M(M_MINS)
#define MC_SCLN     M(M_SCLN)
#define MC_COMM     M(M_COMM)
#define MC_PLUS     M(M_PLUS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  |  Del |           | Print|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |  NO  |           |  NO  |   Y  |   U  |   I  |   O  |   P  |   ö    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | fNAV   |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ü  |   NO   |
 * |--------+------+------+------+------+------| sIns |           | BASE |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   ä  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | GHK  | LGUI | fMOS | LALT | LCTL |                                       |LShift| fNAV | RCTL | RALT | GHK  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | LSft | right|       |  up  | PAUSE|
 *                                 ,------|------|------|       |------+------+------.
 *                                 | Space| fSYM | left |       | down | BSPC | Enter|
 *                                 +      +      +------+       +------+      +      +
 *                                 | Space| fSYM | ESC  |       |  NO  | BSPC | Enter|
 *                                 `--------------------'       `--------------------'
 */
[BASE] = KEYMAP_80(  // layer 0 : default
        // left hand
        KC_GRV,         KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_DEL,
        KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_NO,
        XL_NAV,         KC_A,           KC_S,           KC_D,           KC_F,           KC_G,
        XM_LSFT,        KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           LSFT(KC_INS),
        XM_GHK,         XM_LGUI,        XL_MOS,         XM_LALT,        XM_LCTL,
                                                                        // left thumb
                                                                                        XM_LSFT,        KC_RIGHT,
                                                                        KC_SPC,         XL_SYM,         KC_LEFT,
                                                                        KC_SPC,         XL_SYM,         KC_ESC,

        // right hand
        KC_PSCR,        KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_MINS,
        KC_NO,          KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_OUML,
                        KC_H,           KC_J,           KC_K,           KC_L,           KC_UUML,        KC_NO,
        KC_BASE,        KC_N,           KC_M,           KC_COMM,        KC_DOT,         KC_AUML,        KC_RSFT,
                                        XM_LSFT,        XL_NAV,         XM_RCTL,        KC_RALT,        XM_GHK,
        // right thumb
        KC_UP,          KC_PAUS,
        KC_DOWN,        KC_BSPC,        KC_ENTER,
        KC_NO,          KC_BSPC,        KC_ENTER
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
 * |        |  \   |  /   |  {   |  }   |   *  |------|           |------|  ?   |  (   |  )   |  -   |  ;   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  #   |  $   |  |   |  ~   |   `  |      |           |      |  +   |  %   |  "   |  '   |  :   |        |
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
                KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_SCLN, KC_TRNS,
       KC_TRNS, KC_PLUS, KC_PERC, KC_DQT,  KC_QUOT, KC_COLN, KC_TRNS,
                         KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* keymap 2: navigation and keypad
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |  >   |   <  |      |      |           |      | Tab  |NumLck|  /   |  *   |  ÷   |   ×    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        | PgUp | BSpac| up   | Del  | PgDn |      |           |      |  -   |  7   |  8   |  9   |  +   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Home | left | down | right| End  |------|           |------|  .   |  4   |  5   |  6   |  ,   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        | Esc  | Tab  | Ins  | Enter| MENU |      |           |      |  0   |  1   |  2   |  3   |  :   |        |
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
[NAV] = KEYMAP_80(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_LSTQ, KC_RSTQ, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PGDN, KC_TRNS,
       KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT,KC_END,
       KC_TRNS, KC_ESC,  KC_TAB,  KC_INS,  KC_ENTER,KC_MENU, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                    KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       // TODO: use Keypad keys:
       KC_TRNS, KC_TAB,  KC_NLCK, KC_SLSH, KC_ASTR, KC_DIV,  KC_MUL,
       KC_TRNS, MC_MINS, MC_7,    MC_8,    MC_9,    MC_PLUS, KC_TRNS,
                MC_DOT,  MC_4,    MC_5,    MC_6,    MC_COMM, KC_TRNS,
       KC_TRNS, MC_0,    MC_1,    MC_2,    MC_3,    MC_COLN, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 3: Media and mouse keys
 *
 * TODO: more media keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      | VolD   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |      |      |      |      | Mclk | VolUp  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  F6  |  F7  |  F8  |  F9  |  F10 |------|           |------| Mleft| Mdown| Mup  | Mrigh| Lclk |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  F11 |  F12 |      |      | CAPS |      |           |      | mprev| mstop| mplay| mnext| Rclk |        |
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
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,
       KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
       KC_TRNS, KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_CAPS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                    KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_TRNS, KC_BTN3, KC_VOLU,
                KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1, KC_TRNS,
       KC_TRNS, KC_MPRV, KC_MSTP, KC_MPLY, KC_MNXT, KC_BTN2, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
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



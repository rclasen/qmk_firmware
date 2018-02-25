/*

use case:
- mostly unix: vim, fvwm (with custom key mappings)
- some windows: putty, excel, outlook (with autohotkey "fixes")

preamble:
- most application hotkeys are $modifiers+$alpha.
- ... or can be treated equivalent if you have keys like End/up/insert
  on a layer of the alphas
- this allows holding the modifiers with a thumb while all alphas are
  accessible by the remaining fingers... even on the same hand.
  Eliminating the need for modifiers on both sides.
- combination of modifiers can be achieved by oneshot/locking or
  chording 2 neighboring keys.
- for ergonomics you either need to have your hands floating while
  typing... or finger travel must be minimal to avoid the need to move
  your wrists. I'm unable to use floating, so I have to use least
  possible keys with $many layers.

total symbols:
  26      letters
+ 10 = 36 digits
+ 32 = 68 symbols
+ 12 = 80 F-keys
+ 11 to 15 = 91 nav


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

#include <process_mytap.c>

// this determins the order of layers:
enum my_layer {
	BASE = 0,	// default layer
	NAV,	// navkeys, numpad
	MOS,	// mouse, Fx, media
	SYM,	// symbols
};


// for keys with custom "actions" coded in matrix_scan_user
enum my_keycodes {
    KC_BASE = KC_MYTAP_SAFE,
};

// Compose keycode
//#define KC_COMP KC_PAUSE
#define KC_COMP KC_RALT


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
    M_CUML,
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

        case M_CUML: // M(M_CUML),
            if(record->event.pressed)
                return MACRO(T(COMP), D(LSFT), T(QUOT), U(LSFT), END);
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
#define MC_CUML     M(M_CUML)


#define _______ KC_TRNS
#define XXXXXXX KC_NO


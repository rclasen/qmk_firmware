#pragma once

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "print.h"
#include "action_layer.h"
#include "version.h"

#ifdef BACKLIGHT_ENABLE
#include "backlight.h"
extern backlight_config_t backlight_config;
#endif


/*

use case:
- mostly unix: vim, fvwm (with custom key mappings)
- some windows: putty, excel, outlook (with autohotkey "fixes")
- mostly programming or english text.
- sometimes german with it's diacrics.

preamble:
- most application hotkeys are $modifiers+$alpha.
- ... or can be treated equivalent if you have keys like End/up/insert
  on a layer of the alphas
- holding a key with a thumb barely impacts the movement of other
  fingers of the same hand. If you use thumbs for modifiers + layers,
  you have no need for alternating between left/right modifiers.
  Actually, there's no need for modifiers on both sides.
- combination of modifiers can be achieved by oneshot/locking or
  chording 2 neighboring keys.
- for ergonomics you either need to have your hands floating while
  typing... or finger travel must be minimal to avoid the need to move
  your wrists. I'm unable to use floating, so I have to use least
  possible keys with $many layers.

I started with OS set to DE or US-international keyboards... but DE is a
pain for programming (well, on regular keyboards) and US-international
on windows is unusable due to it's dead keys. Installing custom keyboard
mappings (msklc) is possible, but requires admin privileges.

I've now switched to plain US with compose (builtin on x11, portable
wincompose on windows). In the beginning I replaced my symbol/diacric
Macros with compose sequences. Though, the key mapping of rarely used
symbols was harder to remember than the quite intuitive compose
sequences. Getting rid of the macros freed a lot of keys and simplified
the layout massively.

I did consider an alternative alpha layout, too (adnw, neo2, dvorak,
colemak, ...) but decided, against this. It's already severly painful to
switch to a regular keyboard ... but it's kind of ok to be slow on
modifiers/symbols. For alphas the slowdown caused by swithching to a
"regular staggering" already is more as I can accept. Unless somebody
messed up an installation, all OSes have US layouts... while other
layouts might be a pain to get. BIOS usually are unable to do anything
else but US - making it the obvious choice to me.

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

- I got severely confused with multiple "shift" like operations on one
  thumb: i.e. regular shift (for upper case) and my symbol layer.

- most of the time you need symbols while typing (=both hands on
  keyboard). There's less use for symbols while mousing.

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

- shift/ctrl/layer modifer should be available for each hand and allow
  one-handed operation

- on each hand for alternation (if needed):
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
  - typing symbols

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


#define MOD_ACTIVE(bits) ( keyboard_report->mods & (bits) )

// for keys with custom "actions" coded in matrix_scan_user
//enum my_keycodes {
//    KC_TODO = KC_MYEVENT_SAFE,
//};

// Compose keycode
//#define KC_COMP KC_PAUSE
#define KC_COMP KC_RALT

#define MB_LSFT MOD_BIT(KC_LSFT)
#define MB_LCTL MOD_BIT(KC_LCTL)
#define MB_LALT MOD_BIT(KC_LALT)
#define MB_LGUI MOD_BIT(KC_LGUI)

#define MB_RSFT MOD_BIT(KC_RSFT)
#define MB_RCTL MOD_BIT(KC_RCTL)
#define MB_RALT MOD_BIT(KC_RALT)
#define MB_RGUI MOD_BIT(KC_RGUI)

#define MB_SFT (MB_LSFT | MB_RSFT)

#ifdef BACKLIGHT_ENABLE
void mybacklight_layer( void )
{
	uint8_t new = 0;

	// layer

	if( layer_state ){
		new = 2;

	// modifier
	} else if( MOD_ACTIVE(
        MB_LSFT | MB_RSFT
        | MB_LCTL | MB_RCTL
        | MB_LALT | MB_RALT
        | MB_LGUI | MB_RGUI
    ) ){

		new = 1;
	}

	// finally: set led on/off/brightness

    // avoid using backlight_level(new) as it updates the eeprom
    if( backlight_config.level != new ){
        backlight_set( new );
        backlight_config.level = new;
        backlight_config.enable = new > 0;
	}
}
#endif

/************************************************************
 * myevent user config
 */

#ifdef MYEVENT_ENABLE

enum myevent {
    TSYM,
    TNAV,
    TMOS,

    TLSFT,
    TRSFT,
    TLCTL,
    TRCTL,
    TLALT,
    TRALT,
    TLGUI,
    TGHK,

    TA,
    TS,
    TD,
    TF,
    //TV,

    TF6,
    TF7,
    TF8,
    TF9,

    T4,
    T5,
    T6,
    TCOMM,

    //TM,
    TJ,
    TK,
    TL,
    TCOMP,

    TMAX,
};

// TODO& RSFT doesn't work: register_mods( KC_RSFT) registers lsft + rctrl

_Static_assert(TMAX < MYEVENT_MAX, "not_enough_keycodes_for_myevent" );

static uint8_t shift_saved = 0;

void oneshot_layer_sym( myevent_oneshot_action_t action, void *odata )
{
    (void)odata;

    switch(action){
     case MYEVENT_ONESHOT_START:
        shift_saved = get_mods() & MB_SFT;
        unregister_mods(MB_SFT);
        layer_on(SYM);
        break;

     case MYEVENT_ONESHOT_STOP:
        if(shift_saved)
            register_mods(shift_saved);

        layer_off(SYM);
        break;
    }
}

void oneshot_mod( myevent_oneshot_action_t action, void *odata )
{
    myevent_oneshot_mod_data_t *mdata = (myevent_oneshot_mod_data_t*)odata;

    switch(action){
     case MYEVENT_ONESHOT_START: {
        uint8_t mod = layer_state_is(SYM)
            ? mdata->mod & ~MB_SFT
            : mdata->mod;

        shift_saved |= mdata->mod & MB_SFT;;

        register_mods(mod);

        break;
     }

     case MYEVENT_ONESHOT_STOP:
        shift_saved &= ~( mdata->mod & MB_SFT);
        unregister_mods(mdata->mod);
        break;
    }
}

#define ONESHOT_MOD(modifier) MYEVENT_ONESHOT( \
        oneshot_mod, \
        (void*)&( (myevent_oneshot_mod_data_t) { \
            .mod = modifier, \
            } ) )


typedef struct {
    uint16_t kc;
    uint8_t mod;
} taphold_mod_data_t;

void taphold_mod( myevent_taphold_action_t action, void *tdata )
{
    taphold_mod_data_t *mdata = (taphold_mod_data_t *)tdata;

    switch(action){
     case MYEVENT_TAPHOLD_TAP_START:
        register_code( mdata->kc );
        break;

     case MYEVENT_TAPHOLD_TAP_STOP:
        unregister_code( mdata->kc );
        break;

     case MYEVENT_TAPHOLD_HOLD_START: {
        uint8_t mod = layer_state_is(SYM)
            ? mdata->mod & ~MB_SFT
            : mdata->mod;

        shift_saved |= mdata->mod & MB_SFT;

        register_mods(mod);

        break;
     }

     case MYEVENT_TAPHOLD_HOLD_STOP:
        shift_saved &= ~(mdata->mod & MB_SFT);
        unregister_mods(mdata->mod);
        break;
    }
}

#define TAPHOLD_MOD(modifier,keycode) MYEVENT_TAPHOLD( \
        taphold_mod, \
        (void*)&( (taphold_mod_data_t) { \
            .kc = keycode, \
            .mod = modifier, \
            } ) )

typedef struct {
    uint16_t kc;
    uint8_t mod;
    uint8_t disable;
} taphold_mod_noshift_data_t;

void taphold_mod_noshift( myevent_taphold_action_t action, void *tdata )
{
    taphold_mod_noshift_data_t *mdata = (taphold_mod_noshift_data_t *)tdata;

    switch(action){
     case MYEVENT_TAPHOLD_TAP_START: {
         uint8_t mods = get_mods();
         mdata->disable = mods & MB_SFT;

         if(mdata->disable)
             unregister_mods(mdata->disable);

         register_code(mdata->kc);

         break;
     }

     case MYEVENT_TAPHOLD_TAP_STOP:
        unregister_code(mdata->kc);

        if(mdata->disable)
            register_mods(mdata->disable);

        break;

     case MYEVENT_TAPHOLD_HOLD_START: {
        uint8_t mod = layer_state_is(SYM)
            ? mdata->mod & ~MB_SFT
            : mdata->mod;

        shift_saved |= mdata->mod & MB_SFT;

        register_mods(mod);

        break;
     }

     case MYEVENT_TAPHOLD_HOLD_STOP:
        shift_saved &= ~(mdata->mod & MB_SFT);

        unregister_mods(mdata->mod);

        break;
    }
}

#define TAPHOLD_MOD_NOSHIFT(modifier, keycode) MYEVENT_TAPHOLD( \
        taphold_mod_noshift, \
        (void*)&( (taphold_mod_noshift_data_t) { \
            .kc = keycode, \
            .mod = modifier, \
            } ) )


myevent_action_t myevent_actions[] = {
    [TSYM] = MYEVENT_ONESHOT( oneshot_layer_sym, NULL ),
    [TNAV] = MYEVENT_ONESHOT_LAYER( NAV ),
    [TMOS] = MYEVENT_ONESHOT_LAYER( MOS ),
    [TLSFT] = ONESHOT_MOD( MB_LSFT ),
    [TRSFT] = ONESHOT_MOD( MB_RSFT ),
    [TLCTL] = MYEVENT_ONESHOT_MOD( MB_LCTL ),
    [TRCTL] = MYEVENT_ONESHOT_MOD( MB_RCTL ),
    [TLALT] = MYEVENT_ONESHOT_MOD( MB_LALT ),
    [TRALT] = MYEVENT_ONESHOT_MOD( MB_RALT ),
    [TLGUI] = MYEVENT_ONESHOT_MOD( MB_LGUI ),
    [TGHK] = MYEVENT_ONESHOT_MOD( MB_LCTL | MB_LALT | MB_LGUI ),

    [TA] = MYEVENT_TAPHOLD_MOD( MB_LGUI, KC_A ),
    [TS] = MYEVENT_TAPHOLD_MOD( MB_LCTL, KC_S ),
    [TD] = MYEVENT_TAPHOLD_MOD( MB_LALT, KC_D ),
    [TF] = TAPHOLD_MOD( MB_LSFT, KC_F ),

    [TF6] = MYEVENT_TAPHOLD_MOD( MB_LGUI, KC_F6 ),
    [TF7] = MYEVENT_TAPHOLD_MOD( MB_LCTL, KC_F7 ),
    [TF8] = MYEVENT_TAPHOLD_MOD( MB_LALT, KC_F8 ),
    [TF9] = TAPHOLD_MOD( MB_LSFT, KC_F9 ),

    [TJ] = TAPHOLD_MOD( MB_RSFT, KC_J ),
    [TK] = MYEVENT_TAPHOLD_MOD( MB_LALT, KC_K ),
    [TL] = MYEVENT_TAPHOLD_MOD( MB_RCTL, KC_L ),
    [TCOMP] = MYEVENT_TAPHOLD_MOD( MB_LGUI, KC_COMP),

    [T4] = TAPHOLD_MOD_NOSHIFT( MB_RSFT, KC_4 ),
    [T5] = TAPHOLD_MOD_NOSHIFT( MB_LALT, KC_5 ),
    [T6] = TAPHOLD_MOD_NOSHIFT( MB_RCTL, KC_6 ),
    [TCOMM] = MYEVENT_TAPHOLD_MOD( MB_LGUI, KC_COMM),
};

#endif

/************************************************************
 * macro user config
 */

void mod_tmp( uint16_t keycode, uint8_t suppress, uint8_t add )
{

    uint8_t mods = get_mods();
    uint8_t disable = mods & suppress;
    uint8_t enable = ~mods & add;

    if(disable)
        unregister_mods(disable);
    if(enable)
        register_mods(enable);

    tap_code(keycode);

    if(enable)
        unregister_mods(enable);
    if(disable)
        register_mods(disable);
}

#define noshiftralt(code) mod_tmp(code, MB_SFT , 0 )

// macros/functions that block modifiers:
enum my_keycodes {
    MY_0 = SAFE_RANGE,
    MY_1,
    MY_2,
    MY_3,
    MY_4,
    MY_5,
    MY_6,
    MY_7,
    MY_8,
    MY_9,
    MY_COLN,
    MY_DOT,
    MY_MINS,
    MY_SCLN,
    MY_COMM,
    MY_PLUS,
    MY_BASE,
    MY_VER,

    MY_SAFE,
};


bool mymacro_process_record(uint16_t keycode, keyrecord_t *record)
{
    switch(keycode) {
        case MY_0:
            if (record->event.pressed) {
                register_mods(MB_LSFT);
            } else {
                unregister_mods(MB_LSFT);

                if (record->tap.count && !record->tap.interrupted) {
                    noshiftralt(KC_0);
                }
                record->tap.count = 0;
            }
            return false;

        case MY_1:
            if(record->event.pressed)
                noshiftralt(KC_1);
            return false;

        case MY_2:
            if(record->event.pressed)
                noshiftralt(KC_2);
            return false;

        case MY_3:
            if(record->event.pressed)
                noshiftralt(KC_3);
            return false;

        case MY_4:
            if(record->event.pressed)
                noshiftralt(KC_4);
            return false;

        case MY_5:
            if(record->event.pressed)
                noshiftralt(KC_5);
            return false;

        case MY_6:
            if(record->event.pressed)
                noshiftralt(KC_6);
            return false;

        case MY_7:
            if(record->event.pressed)
                noshiftralt(KC_7);
            return false;

        case MY_8:
            if(record->event.pressed)
                noshiftralt(KC_8);
            return false;

        case MY_9:
            if(record->event.pressed)
                noshiftralt(KC_9);
            return false;

        case MY_COLN:
            if(record->event.pressed)
                mod_tmp(KC_SCLN, MB_RALT, MB_LSFT);
            return false;

        case MY_DOT:
            if(record->event.pressed)
                noshiftralt(KC_DOT);
            return false;

        case MY_MINS:
            if(record->event.pressed)
                noshiftralt(KC_MINS);
            return false;

        case MY_SCLN:
            if(record->event.pressed)
                noshiftralt(KC_SCLN);
            return false;

        case MY_COMM:
            if(record->event.pressed)
                noshiftralt(KC_COMM);
            return false;

        case MY_PLUS:
            if(record->event.pressed)
                mod_tmp(KC_EQL, MB_RALT, MB_LSFT);
            return false;

        case MY_BASE:
            if( record->event.pressed ){
#ifdef MYEVENT_ENABLE
                myevent_clear();
#endif

                layer_clear();

                unregister_mods(get_mods());

                // TODO: caps lock
                // TODO: num lock

            }
            return false;

        case MY_VER:
            if( record->event.pressed ){
                SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION ", Built on: " QMK_BUILDDATE);
            }
            return false;

    }

    return true; // keep going
};


/************************************************************
 * keymap user macros
 */

#define S_INS   LSFT(KC_INS)

#ifdef MYEVENT_ENABLE

#define XL_NAV	XE(TNAV)
#define XL_MOS	XE(TMOS)
#define XL_SYM	XE(TSYM)

#define XM_LALT	XE(TLALT)
#define XM_RALT	XE(TRALT)

#define XM_LCTL	XE(TLCTL)
#define XM_RCTL	XE(TRCTL)

#define XM_LGUI	XE(TLGUI)

#define XM_LSFT	XE(TLSFT)
#define XM_RSFT	XE(TRSFT)

#define XM_GHK XE(TGHK)

#define TX_A    XE(TA)
#define TX_S    XE(TS)
#define TX_D    XE(TD)
#define TX_F    XE(TF)

#define TX_F6   XE(TF6)
#define TX_F7   XE(TF7)
#define TX_F8   XE(TF8)
#define TX_F9   XE(TF9)

#define TX_J    XE(TJ)
#define TX_K    XE(TK)
#define TX_L    XE(TL)
#define TX_COMP XE(TCOMP)

#define TX_4    XE(T4)
#define TX_5    XE(T5)
#define TX_6    XE(T6)
#define TX_COMM XE(TCOMM)

#else

#define XL_NAV	TT(NAV)
#define XL_MOS	TT(MOS)
#define XL_SYM	TT(SYM)

#define XM_LALT	MOD_LALT
#define XM_RALT	MOD_RALT

#define XM_LCTL	MOD_LCTL
#define XM_RCTL	MOD_RCTL

#define XM_LGUI	MOD_LGUI

#define XM_LSFT	MOD_LSFT
#define XM_RSFT	MOD_RSFT

#define MOD_GHK ( MOD_LCTL | MOD_LALT | MOD_LGUI )
#define XM_GHK  OSM(MOD_GHK)

#define TX_A    MT(MOD_LGUI, KC_A)
#define TX_S    MT(MOD_LCTL, KC_S)
#define TX_D    MT(MOD_LALT, KC_D)
#define TX_F    MT(MOD_LSFT, KC_F)

#define TX_F6   MT(MOD_LGUI, KC_F6)
#define TX_F7   MT(MOD_LCTL, KC_F7)
#define TX_F8   MT(MOD_LALT, KC_F8)
#define TX_F9   MT(MOD_LSFT, KC_F9)

#define TX_J    MT(MOD_RSFT, KC_J)
#define TX_K    MT(MOD_LALT, KC_K)
#define TX_L    MT(MOD_RCTL, KC_L)
#define TX_COMP MT(MOD_LGUI, KC_COMP)

#define TX_4    MT(MOD_RSFT, KC_4)
#define TX_5    MT(MOD_LALT, KC_5)
#define TX_6    MT(MOD_RCTL, KC_6)
#define TX_COMM MT(MOD_LGUI, KC_COMM)


#endif

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
// MY_* - see macro stuff above

#define _______ KC_TRNS
#define XXXXXXX KC_NO


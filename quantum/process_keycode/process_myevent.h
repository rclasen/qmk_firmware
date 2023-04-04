#ifndef PROCESS_MYEVENT_H
#define PROCESS_MYEVENT_H

/************************************************************
 * summary
 *
 * backend for:
 *   - oneshot with hold + lock
 *   - hold/tap tap: kc1 hold: kc2
 *   - tapdance: different kc based on # of taps
 *   - ... whatever
 *
 * events:
 *   - eventkey pressed
 *   - tapping timeout (=hold, stop tapping)
 *   - other eventkey pressed (=stop tapping)
 *   - foreign key pressed (=hold, stop tapping)
 *
 *   - eventkey released
 *   - tapping timeout (=stop tapping)
 *   - custom timeout - eg. for oneshot (=stop tapping)
 *   - other eventkey pressed (=stop tapping)
 *   - other key pressed (=stop tapping)
 *
 *   - idle (=cleanup)
 *
 * check end of file for an example.
 */


#ifndef MYEVENT_TAPPING_TIMEOUT
#ifdef TAPPING_TERM
#define MYEVENT_TAPPING_TIMEOUT TAPPING_TERM
#else
#define MYEVENT_TAPPING_TIMEOUT 200
#endif
#endif

#ifndef MYEVENT_ONESHOT_TIMEOUT
#ifdef ONESHOT_TIMEOUT
#define MYEVENT_ONESHOT_TIMEOUT ONESHOT_TIMEOUT
#else
#define MYEVENT_ONESHOT_TIMEOUT 2000
#endif
#endif

#ifndef MYEVENT_ONESHOT_TOGGLE
#ifdef ONESHOT_TAP_TOGGLE
#define MYEVENT_ONESHOT_TOGGLE ONESHOT_TAP_TOGGLE
#else
#define MYEVENT_ONESHOT_TOGGLE 2
#endif
#endif


#include "quantum.h"

#define MYEVENT_MAX (QK_MYEVENT_MAX - QK_MYEVENT)

/************************************************************
 * globals hooks
 *
 * call them from your keymap.
 */

bool myevent_process_record(uint16_t keycode, keyrecord_t *record);
void myevent_task(void);

/************************************************************
 * internal structures
 */

// key state:
typedef enum {
    myevent_pos_down   = 0,
    myevent_pos_up     = 1
} myevent_position_t;

// foreign key relation:
typedef enum {
    myevent_other_none    = 0,
    myevent_other_pre     = 1,
    myevent_other_post    = 2,
    myevent_other_src     = 3
} myevent_other_t;

// what changed:
typedef enum {
    myevent_change_active,
    myevent_change_position,
    myevent_change_tap_done,
    myevent_change_up_done,
    myevent_change_other,
    myevent_change_clear,
} myevent_change_t;

typedef union {
        uint8_t raw;
        // all flags are reset on down event
        struct {
            bool active:1;      // tapping/handling ongoing
            myevent_position_t position:1;   // up/down
            bool tap_done:1;    // ran into tapping timeout
            bool up_done:1;     // ran into uptimeout
            myevent_other_t  other:2;
            bool holding:1;     // ran into DOWN_END/_OTHER
            bool complete:1;    // taping completed
        };
} myevent_flags_t;

typedef struct {
    myevent_flags_t flags;
    uint16_t pressed;   // time off last press
    uint8_t count;
    uint16_t uptimer;
    uint16_t uptimeout;
} myevent_state_t;


/************************************************************
 * actions / keymap
 *
 * fn_state is called on each state transistion (in state->state).
 */

struct myevent_action_s;
typedef struct myevent_action_s myevent_action_t;

typedef void (*myevent_fn_state_t)( myevent_action_t *action, myevent_change_t change );

struct myevent_action_s {
    myevent_state_t state;
    myevent_fn_state_t fn_state;
    void *data;
};

extern myevent_action_t myevent_actions[];

#define XE(n) (QK_MYEVENT + n)

/************************************************************
 * user api
 */

// abort and cleanup all actions:
void myevent_clear(void);

// for custom actions: tell the backend that a foreign key was pressed
void myevent_foreign_pre( myevent_action_t *current );
void myevent_foreign_post( myevent_action_t *current );

/************************************************************
 *
 * oneshot
 *
 * in addition to chording multiple modifier/layer keys, allow to type
 * them in sequence.
 *
 * - activate layer/modifier on first press
 * - keep layer/modifier activated for MYEVENT_ONESHOT_TIMEOUT after first
 *   release
 * - lock layer/modifier after MYEVENT_ONESHOT_TOGGLE number of presses
 * - unlock/deactivat layer/modifier on long press
 */

typedef enum {
    MYEVENT_ONESHOT_START,
    MYEVENT_ONESHOT_STOP,
} myevent_oneshot_action_t;

typedef void (*myevent_oneshot_fn_t)( myevent_oneshot_action_t action, void *odata );

typedef struct {
    myevent_oneshot_fn_t fn;
    void *data;
    bool active;
} myevent_oneshot_data_t;

void myevent_oneshot_event ( myevent_action_t *action, myevent_change_t change );

#define MYEVENT_ONESHOT(fname, odata) { \
    .fn_state       = myevent_oneshot_event, \
    .data           = (void*)&( (myevent_oneshot_data_t) { \
            .fn = fname, \
            .data = odata, \
            .active = false, \
            } ), \
}

bool myevent_oneshot_active( myevent_action_t *action );
#define myevent_oneshot_active_id(id) myevent_oneshot_active(&myevent_actions[id])

/************************************************************
 * oneshot layer
 */

typedef struct {
    uint8_t layer;
} myevent_oneshot_layer_data_t;

void myevent_oneshot_layer( myevent_oneshot_action_t action, void *odata );

#define MYEVENT_ONESHOT_LAYER(layer) MYEVENT_ONESHOT( \
        myevent_oneshot_layer, \
        (void*)&( (myevent_oneshot_layer_data_t) { layer } ) )

/************************************************************
 * oneshot modifier
 */

typedef struct {
    uint8_t mod;
} myevent_oneshot_mod_data_t;

void myevent_oneshot_mod( myevent_oneshot_action_t action, void *odata );

#define MYEVENT_ONESHOT_MOD(mod) MYEVENT_ONESHOT( \
        myevent_oneshot_mod, \
        (void*)&( (myevent_oneshot_mod_data_t) { mod } ) )


/************************************************************
 *
 * taphold
 *
 * send different keycodes when a key is quickly tapped or if it's hold
 * down. Commonly this is used have a character (on tap) and a modifier
 * (on hold) on one key.
 *
 * - if taphold key is pressed/released quickly once, send tap keycode
 * - if a foreign key is pressed while taphold key is pressed for less
 *   than MYEVENT_TAPPING_TIMEOUT, send tap keycode. This allows
 *   fluent/fast typing.
 * - if taphold key is tapped once and then hold down, send the tap
 *   keycode while key is pressed.
 * - if taphold key is hold down for MYEVENT_TAPPING_TIMEOUT, send hold
 *   keycode while it's pressed.
 */

typedef enum {
    MYEVENT_TAPHOLD_TAP_START,
    MYEVENT_TAPHOLD_TAP_STOP,
    MYEVENT_TAPHOLD_HOLD_START,
    MYEVENT_TAPHOLD_HOLD_STOP,
} myevent_taphold_action_t;

typedef void (*myevent_taphold_fn_t)( myevent_taphold_action_t action, void *tdata );

enum myevent_taphold_state {
    MYEVENT_TAPHOLD_NONE,
    MYEVENT_TAPHOLD_TAP,
    MYEVENT_TAPHOLD_HOLD,
};

typedef struct {
    enum myevent_taphold_state state;
    myevent_taphold_fn_t fn;
    void *data;
} myevent_taphold_data_t;

void myevent_taphold_event ( myevent_action_t *action, myevent_change_t change );

#define MYEVENT_TAPHOLD(fname, tdata) { \
    .fn_state       = myevent_taphold_event, \
    .data           = (void*)&( (myevent_taphold_data_t) { \
            .fn = fname, \
            .data = tdata, \
            } ), \
}

/************************************************************
 * taphold layer
 */

typedef struct {
    uint8_t layer;
    uint8_t kc;
} myevent_taphold_layer_data_t;

void myevent_taphold_layer( myevent_taphold_action_t action, void *tdata );

#define MYEVENT_TAPHOLD_LAYER(l, keycode) MYEVENT_TAPHOLD( \
        myevent_taphold_layer, \
        (void*)&( (myevent_taphold_layer_data_t) { \
            .layer = l, \
            .kc = keycode, \
            } ) )

/************************************************************
 * taphold modifier
 */

typedef struct {
    uint8_t mod;
    uint8_t kc;
} myevent_taphold_mod_data_t;

void myevent_taphold_mod( myevent_taphold_action_t action, void *tdata );

#define MYEVENT_TAPHOLD_MOD(modifier, keycode) MYEVENT_TAPHOLD( \
        myevent_taphold_mod, \
        (void*)&( (myevent_taphold_mod_data_t) { \
            .mod = modifier, \
            .kc = keycode, \
            } ) )

/************************************************************
 * example

myevent_action_t myevent_actions[] = {
    [ESYM] = {
        // custom tapping function:
        .fn_state = myevent_sym_layer_event,
        .data = NULL,
    },
    [ENAV] = MYEVENT_ONESHOT_LAYER( NAV ),
    [EGHK] = MYEVENT_ONESHOT_MOD( MOD_LCTL | MOD_LALT | MOD_LGUI ),
    [EF] = MYEVENT_TAPHOLD_MOD( MOD_LSFT, KC_F ),
};

// use XT(ESYM) in keymap

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if( ! myevent_process_record( keycode, record ) )
        return false;

    // ...
}

void matrix_scan_user(void) {
    myevent_matrix_scan();

    // ...
}

*/

#endif

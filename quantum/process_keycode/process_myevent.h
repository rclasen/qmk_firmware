#ifndef PROCESS_MYEVENT_H
#define PROCESS_MYEVENT_H

#ifndef MYEVENT_MAX
#define MYEVENT_MAX 32
#endif

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


/************************************************************
 * summary
 *
 * backend for:
 *   - oneshot with hold + lock
 *   - mod-tap tap: kc1 hold: kc2
 *   - tapdance: different kc based on # of taps
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
 */

/************************************************************
 * globals hooks
 */

bool myevent_process_record(uint16_t keycode, keyrecord_t *record);
void myevent_matrix_scan(void);

/************************************************************
 * user api
 */

// abort and cleanup all actions:
void myevent_clear(void);

/************************************************************
 * internal structures
 */

enum myevent_keycodes {
    KC_MYEVENT_FIRST = SAFE_RANGE,
    KC_MYEVENT_LAST = KC_MYEVENT_FIRST + MYEVENT_MAX,
    KC_MYEVENT_SAFE,
};

enum myevent_state {
    MYEVENT_STATE_IDLE = 0,     // next: DOWN
    MYEVENT_STATE_DOWN,         // next: _OTHER/_END
    MYEVENT_STATE_DOWN_OTHER,   // next: UP
    MYEVENT_STATE_DOWN_END,     // next: UP
    MYEVENT_STATE_UP,           // next: _OTHER/_END/_TIMER
    MYEVENT_STATE_UP_OTHER,     // next: IDLE
    MYEVENT_STATE_UP_END,       // next: IDLE/_TIMER
    MYEVENT_STATE_UP_TIMER,     // next: IDLE
};

typedef struct {
    enum myevent_state state;
    bool holding;   // ran into DOWN_END/_OTHER
    bool complete;  // taping completed
    uint8_t count;
    uint16_t taptimer;
    uint16_t uptimer;
    uint16_t uptimeout;
} myevent_state_t;


/************************************************************
 * actions / keymap
 *
 * fn_state is called on each state transistion (in state->state).
 */

typedef void (*myevent_fn_state_t)( myevent_state_t *state, void *data );

typedef struct {
    myevent_state_t state;
    myevent_fn_state_t fn_state;
    void *data;
} myevent_action_t;

extern myevent_action_t myevent_actions[];

#define XE(n) (KC_MYEVENT_FIRST + n)

/************************************************************
 * oneshot
 */

typedef void (*myevent_oneshot_fn_t)( bool start, void *data );

typedef struct {
    myevent_oneshot_fn_t fn;
    void *data;
} myevent_oneshot_data_t;

void myevent_oneshot_event ( myevent_state_t *state, void *data );

#define MYEVENT_ONESHOT(fname, odata) { \
    .fn_state       = myevent_oneshot_event, \
    .data           = (void*)&( (myevent_oneshot_data_t) { \
            .fn = fname, \
            .data = odata, \
            } ), \
}

/************************************************************
 * oneshot layer
 *
 * - activate layer on first press
 * - keep layer activated for MYEVENT_ONESHOT_TIMEOUT after first release
 * - lock layer after MYEVENT_ONESHOT_TOGGLE number of presses
 * - unlock/deactivat layer on long 
 */

typedef struct {
    uint8_t layer;
} myevent_oneshot_layer_data_t;

void myevent_oneshot_layer( bool start, void *data );

#define MYEVENT_ONESHOT_LAYER(layer) MYEVENT_ONESHOT( \
        myevent_oneshot_layer, \
        (void*)&( (myevent_oneshot_layer_data_t) { layer } ) )

/************************************************************
 * oneshot modifier
 */

typedef struct {
    uint8_t mod;
} myevent_oneshot_mod_data_t;

void myevent_oneshot_mod( bool start, void *data );

#define MYEVENT_ONESHOT_MOD(mod) MYEVENT_ONESHOT( \
        myevent_oneshot_mod, \
        (void*)&( (myevent_oneshot_mod_data_t) { mod } ) )


/************************************************************
 * taphold
 */

typedef void (*myevent_taphold_fn_t)( bool tap, bool start, void *data );

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

void myevent_taphold_event ( myevent_state_t *state, void *data );

#define MYEVENT_TAPHOLD(fname, odata) { \
    .fn_state       = myevent_taphold_event, \
    .data           = (void*)&( (myevent_taphold_data_t) { \
            .fn = fname, \
            .data = odata, \
            } ), \
}

/************************************************************
 * taphold layer
 */

typedef struct {
    uint8_t layer;
    uint8_t kc;
} myevent_taphold_layer_data_t;

void myevent_taphold_layer( bool tap, bool start, void *data );

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

void myevent_taphold_mod( bool tap, bool start, void *data );

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
        .fn_state = myevent_sym_layer_event,
        .data = NULL,
    },
    [ENAV] = MYEVENT_ONESHOT_LAYER( NAV ),
    [EGHK] = MYEVENT_ONESHOT_MOD( MOD_LCTL | MOD_LALT | MOD_LGUI ),
    [EF] = MYEVENT_TAPHOLD_MOD( MOD_LSFT, KC_F ),
};

// use XT(TSYM) in keymap

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

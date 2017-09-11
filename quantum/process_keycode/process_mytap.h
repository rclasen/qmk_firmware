#ifndef PROCESS_MYTAP_H
#define PROCESS_MYTAP_H

#ifndef MYTAP_MAX
#define MYTAP_MAX  16
#endif

/************************************************************
 * internal structures
 */

enum myap_keycodes {
    KC_MYTAP_FIRST = SAFE_RANGE,
    KC_MYTAP_LAST = KC_MYTAP_FIRST + MYTAP_MAX,
    KC_MYTAP_SAFE,
};

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

/************************************************************
 * globals hooks
 */

void mytap_matrix_scan(void);
bool mytap_process_record(uint16_t keycode, keyrecord_t *record);

/************************************************************
 * user api
 */

void mytap_clear(void);

/************************************************************
 * actions / keymap
 */

typedef void (*mytap_fn_t)( mytap_state_t *state, void *data );

typedef struct {
    mytap_state_t state;
    struct {
        mytap_fn_t on_press;
        mytap_fn_t on_release;
    } fn;
    void *data;
} mytap_action_t;

extern mytap_action_t mytap_actions[];

#define XT(n) (KC_MYTAP_FIRST + n)

/************************************************************
 * mytap layer
 */

typedef struct {
    uint8_t layer;
} mytap_layer_data_t;

void mytap_layer_press ( mytap_state_t *state, void *data );
void mytap_layer_release ( mytap_state_t *state, void *data );

#define MYTAP_LAYER(layer) { \
        .fn = { mytap_layer_press, mytap_layer_release }, \
        .data = (void*)&( (mytap_layer_data_t) { layer } ), \
    }

/************************************************************
 * mytap mod
 */

typedef struct {
    uint8_t mod;
} mytap_mod_data_t;

void mytap_mod_press ( mytap_state_t *state, void *data );
void mytap_mod_release ( mytap_state_t *state, void *data );

#define MYTAP_MOD(mod) { \
        .fn = { mytap_mod_press, mytap_mod_release }, \
        .data = (void*)&( (mytap_mod_data_t) { mod } ), \
    }


/************************************************************
 * example

mytap_action_t mytap_actions[] = {
    [TSYM] = {
        .fn = {
            .on_press = mytap_sym_layer_press,
            .on_release = mytap_sym_layer_release,
        },
        .data = NULL,
    },
    [TNAV] = MYTAP_LAYER( NAV ),
    [TGHK] = MYTAP_MOD( MOD_LCTL | MOD_LALT | MOD_LGUI ),
};

// use XT(TSYM) in keymap

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if( ! mytap_process_record( keycode, record ) )
        return false;

    // ...
}

void matrix_scan_user(void) {
    mytap_matrix_scan();

    // ...
}

*/

#endif // PROCESS_MYTAP_H


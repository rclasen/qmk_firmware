#include "process_mytap.h"

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
static void mytap_release( uint8_t idx )
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
static void mytap_tapping_begin( uint8_t idx )
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
static void mytap_tapping_end( uint8_t idx )
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

/************************************************************
 * mytap layer
 */

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



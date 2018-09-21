#include "process_myevent.h"

#define MYEVENT_NONE    (-1)

#define IS_MYEVENT(kc)  ( (kc >= KC_MYEVENT_FIRST) \
            && (kc <= KC_MYEVENT_LAST ) )

#define EMIT(action) if(action->fn_state){ \
    dprintf("myevent: state=%d holding=%d count=%d\n", action->state.state, action->state.holding, action->state.count); \
    (*action->fn_state)( &action->state, action->data ); \
}

// index of highest used myevent action:
static int8_t _myevent_highest = MYEVENT_NONE;

// index of ongoing myevent tapping action:
static int8_t _myevent_current = MYEVENT_NONE;

// return to idle state, cleanup everything
static void _myevent_idle( myevent_action_t *action )
{
    action->state.state = MYEVENT_STATE_IDLE;
    EMIT(action);

    action->state.holding = false;
    action->state.complete = false;
    action->state.count = 0;
}

// set all to idle ... to be called by user
void myevent_clear(void)
{
    dprintf("myevent_clear highest=%d\n", _myevent_highest );

    for( int8_t i = 0; i <= _myevent_highest; ++i ){
        myevent_action_t *action = &myevent_actions[i];

        if( action->state.state == MYEVENT_STATE_IDLE )
            continue;

        dprintf("myevent_clear i=%d\n", i );
        _myevent_idle( action );
    }

    _myevent_highest = MYEVENT_NONE;
}

// end tapping when foreign key is pressed
// foreign = no modifier, no tapping. 
void myevent_end_foreign ( void )
{
    // TODO: avoid recursion
    for( int8_t i = 0; i <= _myevent_highest; ++i ){
        myevent_action_t *action = &myevent_actions[i];

        if( _myevent_current == i )
            continue;

        switch( action->state.state ){
         case MYEVENT_STATE_DOWN:
            action->state.holding = true;
            action->state.state = MYEVENT_STATE_DOWN_OTHER;
            break;

         case MYEVENT_STATE_UP:
         case MYEVENT_STATE_UP_END:
            action->state.state = MYEVENT_STATE_UP_OTHER;
            break;

         default:
            continue;
        }

        action->state.complete = true;
        dprintf("myevent_end_foreign i=%d\n", i );

        EMIT(action);
    }
}

bool myevent_process_record(uint16_t keycode, keyrecord_t *record)
{
    if( IS_MYEVENT(keycode) ){
        int8_t idx = keycode - KC_MYEVENT_FIRST;
        myevent_action_t *action = &myevent_actions[idx];

        if( idx > _myevent_highest )
            _myevent_highest = idx;

        if( _myevent_current != MYEVENT_NONE &&
                _myevent_current != idx ){
                myevent_actions[idx].state.complete = true;
        }

        _myevent_current = idx;

        if( record->event.pressed ){
            dprintf("myevent_record idx=%d oldstate=%d oldcount=%d down\n",
                    idx, action->state.state, action->state.count );

            if( action->state.complete )
                _myevent_idle( action );

            ++(action->state.count);
            action->state.state = MYEVENT_STATE_DOWN;
            action->state.uptimeout = 0;

            EMIT(action);

            action->state.taptimer = timer_read();

        } else if( action->state.state != MYEVENT_STATE_IDLE ){
            bool done = true;

            dprintf("myevent_record idx=%d oldstate=%d up\n",
                    idx, action->state.state);

            action->state.state = MYEVENT_STATE_UP;

            EMIT(action);

            if( action->state.uptimeout > 0 ){
                action->state.uptimer = timer_read();
                done = false;
            }

            if( ! action->state.holding ){
                action->state.taptimer = timer_read();
                done = false;
            }

            if( done )
                _myevent_idle( action );
        }

    } else { // not MYEVENT
        if( record->event.pressed && !IS_MOD(keycode) ){

            if( _myevent_highest != MYEVENT_NONE ){
                _myevent_current = MYEVENT_NONE;
                myevent_end_foreign();
            }
        }
    }

    return true;
}

void myevent_matrix_scan(void)
{
    int8_t max = MYEVENT_NONE;

    for( int8_t i = 0; i <= _myevent_highest; ++i ){
        myevent_action_t *action = &myevent_actions[i];

        switch(action->state.state){
         case MYEVENT_STATE_IDLE:
            continue;

         case MYEVENT_STATE_DOWN:
            if( timer_elapsed(action->state.taptimer) > MYEVENT_TAPPING_TIMEOUT ){
                dprintf("myevent_scan idx=%d oldstate=%d tap timeout\n",
                        i, action->state.state );

                action->state.holding = true;
                action->state.complete = true;
                action->state.state = MYEVENT_STATE_DOWN_END;
                EMIT( action );
            }

            break;

         case MYEVENT_STATE_UP:
            if( timer_elapsed(action->state.taptimer) > MYEVENT_TAPPING_TIMEOUT ){
                dprintf("myevent_scan idx=%d oldstate=%d tap timeout\n",
                        i, action->state.state );

                action->state.complete = true;
                action->state.state = MYEVENT_STATE_UP_END;
                EMIT( action );
            }
            break;

         case MYEVENT_STATE_UP_END:
            if( action->state.uptimeout ){
                if( timer_elapsed(action->state.uptimer) > action->state.uptimeout ){
                    dprintf("myevent_scan idx=%d oldstate=%d uptimeout=%d\n",
                            i, action->state.state, action->state.uptimeout );

                    action->state.state = MYEVENT_STATE_UP_TIMER;
                    EMIT(action);
                }

            } else {
                _myevent_idle( action );
            }

            break;

         case MYEVENT_STATE_UP_TIMER:
         case MYEVENT_STATE_UP_OTHER:
            _myevent_idle( action );
            break;

         default:
            break;
        }

        max = i;
    }

    _myevent_highest = max;
}

/************************************************************
 * oneshot
 */

void myevent_oneshot_event ( myevent_state_t *state, void *edata )
{
    myevent_oneshot_data_t *odata = (myevent_oneshot_data_t *)edata;

    switch(state->state){
     case MYEVENT_STATE_DOWN:
        if( state->count == 1 ){
            dprintf("myevent_oneshot start\n");
            (*odata->fn)( MYEVENT_ONESHOT_START, odata->data );
        }

        break;

     case MYEVENT_STATE_UP:
        if( state->holding )
            break;

        if( state->count == 1 ){
            dprintf("myevent_oneshot oneshot\n");
            state->uptimeout = MYEVENT_ONESHOT_TIMEOUT;
        }

        break;

     case MYEVENT_STATE_IDLE:
        if( state->count == MYEVENT_ONESHOT_TOGGLE ){
            dprintf("myevent_oneshot locked\n");

        } else {
            dprintf("myevent_oneshot clear\n");
            (*odata->fn)( MYEVENT_ONESHOT_STOP, odata->data );
        }

        break;

     default:
        break;
    }
}


/************************************************************
 * oneshot layer
 */

void myevent_oneshot_layer ( myevent_oneshot_action_t action, void *odata )
{
    myevent_oneshot_layer_data_t *ldata = (myevent_oneshot_layer_data_t *)odata;

    switch(action){
     case MYEVENT_ONESHOT_START:
        dprintf("myevent_oneshot_layer start\n");
        layer_on( ldata-> layer );
        break;

     case MYEVENT_ONESHOT_STOP:
        dprintf("myevent_oneshot_layer clear\n");
        layer_off( ldata->layer );
        break;
    }
}


/************************************************************
 * oneshot modifier
 */

void myevent_oneshot_mod ( myevent_oneshot_action_t action, void *odata )
{
    myevent_oneshot_mod_data_t *mdata = (myevent_oneshot_mod_data_t *)odata;

    switch(action){
     case MYEVENT_ONESHOT_START:
        dprintf("myevent_oneshot_mod start\n");
        register_mods( mdata-> mod );
        break;

     case MYEVENT_ONESHOT_STOP:
        dprintf("myevent_oneshot_mod clear\n");
        unregister_mods( mdata->mod );
        break;
    }
}

/************************************************************
 * taphold
 */

void myevent_taphold_event ( myevent_state_t *state, void *edata )
{
    myevent_taphold_data_t *tdata = (myevent_taphold_data_t *)edata;

    switch(state->state){
     case MYEVENT_STATE_DOWN:
        if( state->count > 1 ){
            dprintf("myevent_taphold tap/hold\n");
            (*tdata->fn)( MYEVENT_TAPHOLD_TAP_STOP, tdata->data );
            myevent_end_foreign();
            (*tdata->fn)( MYEVENT_TAPHOLD_TAP_START, tdata->data );
            tdata->state = MYEVENT_TAPHOLD_TAP;
        }

        break;

     case MYEVENT_STATE_DOWN_END:
        if( state->count == 1 ){
            dprintf("myevent_taphold hold\n");
            (*tdata->fn)( MYEVENT_TAPHOLD_HOLD_START, tdata->data );
            tdata->state = MYEVENT_TAPHOLD_HOLD;
        }

        break;

     case MYEVENT_STATE_DOWN_OTHER:
        if( tdata->state != MYEVENT_TAPHOLD_HOLD ){
            dprintf("myevent_taphold tap/other\n");
            myevent_end_foreign();
            (*tdata->fn)( MYEVENT_TAPHOLD_TAP_START, tdata->data );
            tdata->state = MYEVENT_TAPHOLD_TAP;
        }

        break;

     case MYEVENT_STATE_UP:
        if( tdata->state == MYEVENT_TAPHOLD_NONE ){
            dprintf("myevent_taphold tap/tap\n");
            (*tdata->fn)( MYEVENT_TAPHOLD_TAP_START, tdata->data );
            myevent_end_foreign();
            tdata->state = MYEVENT_TAPHOLD_TAP;
        }

        break;

     case MYEVENT_STATE_IDLE:
        switch( tdata->state ){
         case MYEVENT_TAPHOLD_TAP:
            dprintf("myevent_taphold tap/clear\n");
            (*tdata->fn)( MYEVENT_TAPHOLD_TAP_STOP, tdata->data );
            break;

         case MYEVENT_TAPHOLD_HOLD:
            dprintf("myevent_taphold hold/clear\n");
            (*tdata->fn)( MYEVENT_TAPHOLD_HOLD_STOP, tdata->data );
            break;

         default:
            break;
        }
        tdata->state = MYEVENT_TAPHOLD_NONE;

        break;

     default:
        break;
    }
}

/************************************************************
 * taphold layer
 */


void myevent_taphold_layer( myevent_taphold_action_t action, void *tdata )
{
    myevent_taphold_layer_data_t *ldata = (myevent_taphold_layer_data_t *)tdata;

    switch(action){
     case MYEVENT_TAPHOLD_TAP_START:
        dprintf("myevent_taphold_layer tap/start %d\n", ldata->kc);
        register_code( ldata->kc );
        break;

     case MYEVENT_TAPHOLD_TAP_STOP:
        dprintf("myevent_taphold_layer tap/clear %d\n", ldata->kc);
        unregister_code( ldata->kc );
        break;

     case MYEVENT_TAPHOLD_HOLD_START:
        dprintf("myevent_taphold_layer hold/start %d\n", ldata->layer);
        layer_on( ldata->layer );
        break;

     case MYEVENT_TAPHOLD_HOLD_STOP:
        dprintf("myevent_taphold_layer hold/clear %d\n", ldata->layer);
        layer_off( ldata->layer );
        break;
    }
}

/************************************************************
 * taphold modifier
 */


void myevent_taphold_mod( myevent_taphold_action_t action, void *tdata )
{
    myevent_taphold_mod_data_t *mdata = (myevent_taphold_mod_data_t *)tdata;

    switch(action){
     case MYEVENT_TAPHOLD_TAP_START:
        dprintf("myevent_taphold_mod tap/start %d\n", mdata->kc);
        register_code( mdata->kc );
        break;

     case MYEVENT_TAPHOLD_TAP_STOP:
        dprintf("myevent_taphold_mod tap/clear %d\n", mdata->kc);
        unregister_code( mdata->kc );
        break;

     case MYEVENT_TAPHOLD_HOLD_START:
        dprintf("myevent_taphold_mod hold/start %d\n", mdata->mod);
        register_mods( mdata->mod );
        break;

     case MYEVENT_TAPHOLD_HOLD_STOP:
        dprintf("myevent_taphold_mod hold/clear %d\n", mdata->mod);
        unregister_mods( mdata->mod );
        break;
    }
}


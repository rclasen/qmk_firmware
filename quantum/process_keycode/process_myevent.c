#include "process_myevent.h"

#define MYEVENT_NONE    (-1)

#define EMIT(action, change) if(action->fn_state){ \
    dprintf("myevent: edata=%u change=%d count=%d h=%d c=%d a=%d p=%d t=%d u=%d o=%d\n", \
            action->data, \
            change, \
            action->state.count, \
            action->state.flags.holding, \
            action->state.flags.complete, \
            action->state.flags.active, \
            action->state.flags.position, \
            action->state.flags.tap_done, \
            action->state.flags.up_done, \
            action->state.flags.other); \
    (*action->fn_state)( action, change ); \
}

// index of highest active myevent action:
static int8_t _myevent_highest = MYEVENT_NONE;
// index of highest myevent action ever seen:
static int8_t _myevent_last = MYEVENT_NONE;

// index of ongoing myevent tapping action:
static int8_t _myevent_current = MYEVENT_NONE;
static uint16_t _myevent_taptimer;

// return to idle state, cleanup everything
static void _myevent_idle( myevent_action_t *action )
{
    action->state.flags.raw = 0;
    EMIT(action, myevent_change_active );

    action->state.flags.holding = false;
    action->state.flags.complete = false;
    action->state.count = 0;
}

// set all to idle ... to be called by user
void myevent_clear(void)
{
    dprintf("myevent_clear last=%d\n", _myevent_last );

    for( int8_t i = 0; i <= _myevent_last; ++i ){
        myevent_action_t *action = &myevent_actions[i];

        if( action->state.flags.active ){
            dprintf("myevent_clear edata=%u\n", action->data );
            _myevent_idle( action );
        }

        EMIT(action, myevent_change_clear );
    }

    _myevent_highest = MYEVENT_NONE;
    _myevent_last = MYEVENT_NONE;
    _myevent_current = MYEVENT_NONE;
}

// end tapping when foreign key is pressed
// foreign = no modifier, no tapping.
static bool _in_foreign_pre = false;
void myevent_foreign_pre( myevent_action_t *current )
{
    if( _in_foreign_pre )
        return;
    _in_foreign_pre = true;

    uint16_t now = timer_read();

    while(1){
        uint16_t maxage = 0;
        myevent_action_t *action = NULL;

        // find oldest down event
        for( int8_t i = 0; i <= _myevent_highest; ++i ){
            myevent_action_t *this = &myevent_actions[i];

            if( this->state.flags.active
                    && this->state.flags.other == myevent_other_none ){

                uint16_t age = now - this->state.pressed;

                if( age > maxage ){
                    maxage = age;
                    action = this;
                }
            }
        }

        if( action ){
            dprintf("myevent_foreign_pre edata=%u\n", action->data );

            if( action == current ){
                action->state.flags.other = myevent_other_src;

            } else {
                action->state.flags.complete = true;
                if( action->state.flags.position == myevent_pos_down )
                    action->state.flags.holding = true;
                action->state.flags.other = myevent_other_pre;

            }

            EMIT(action, myevent_change_other);

        } else { // no events left, exit loop
            break;
        }
    }

    _in_foreign_pre = false;
}

static bool _in_foreign_post = false;
void myevent_foreign_post( myevent_action_t *current )
{
    if( _in_foreign_post )
        return;
    _in_foreign_post = true;

    // TODO: process action sorted by time of down event
    for( int8_t i = 0; i <= _myevent_highest; ++i ){
        myevent_action_t *action = &myevent_actions[i];

        if( current == action )
            continue;

        if( action->state.flags.other == myevent_other_pre ){
            action->state.flags.other = myevent_other_post;

            dprintf("myevent_foreign_post edata=%u idx=%d\n", action->data, i );

            EMIT(action, myevent_change_other);
        }
    }

    _in_foreign_post = false;
}


bool myevent_process_record(uint16_t keycode, keyrecord_t *record)
{
    //dprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);

    if( IS_QK_MYEVENT(keycode) ){
        int8_t idx = keycode - QK_MYEVENT;
        myevent_action_t *action = &myevent_actions[idx];

        if( idx > _myevent_highest )
            _myevent_highest = idx;
        if( idx > _myevent_last )
            _myevent_last = idx;

        if( record->event.pressed ){
            dprintf("myevent_record edata=%u idx=%d oldcount=%d down\n",
                    action->data, idx, action->state.count );

            if( _myevent_current != MYEVENT_NONE &&
                    _myevent_current != idx ){

                myevent_action_t *old = &myevent_actions[_myevent_current];

                if( ! old->state.flags.complete && old->state.count ){

                    dprintf("myevent_record edata=%u idx=%d tap other\n",
                            old->data, _myevent_current );

                    old->state.flags.complete = true;
                }
            }
            _myevent_current = idx;

            if( action->state.flags.complete ){
                dprintf("myevent_record edata=%u idx=%d tap restart\n",
                        action->data, idx );
                // TODO: verify
                _myevent_idle( action );
            }

            action->state.flags.raw = 0;
            action->state.flags.active = true;
            action->state.pressed = timer_read();
            ++(action->state.count);
            action->state.uptimeout = 0;

            EMIT(action, myevent_change_position);

            _myevent_taptimer = timer_read();

        } else if( action->state.flags.active ){
            bool done = true;

            dprintf("myevent_record edata=%u idx=%d up\n",
                    action->data, idx);

            action->state.flags.position = myevent_pos_up;
            action->state.flags.other = myevent_other_none;

            EMIT(action, myevent_change_position);

            if( action->state.uptimeout > 0 ){
                action->state.uptimer = timer_read();
                done = false;
            }

            if( ! action->state.flags.holding ){
                done = false;
            }

            if( done )
                _myevent_idle( action );
        }

    } else { // not MYEVENT
        if( record->event.pressed && !IS_MODIFIER_KEYCODE(keycode) ){

            if( _myevent_highest != MYEVENT_NONE ){
                _myevent_current = MYEVENT_NONE;
                myevent_foreign_pre( NULL );
            }
        }

        // tell QMK to run other hooks:
        return true;
    }

    // myevent key was processed:
    return false;
}

void myevent_task(void)
{
    int8_t max = MYEVENT_NONE;

    for( int8_t i = 0; i <= _myevent_highest; ++i ){
        myevent_action_t *action = &myevent_actions[i];

        if( ! action->state.flags.active )
            continue;

        max = i;

        if( action->state.flags.other == myevent_other_pre ){
            dprintf("myevent_scan edata=%u idx=%d other_post\n",
                    action->data, i );
            action->state.flags.other = myevent_other_post;
            EMIT(action, myevent_change_other );
        }

        if( ! action->state.flags.tap_done
                && ( action->state.flags.other == myevent_other_none
                    || action->state.flags.other == myevent_other_src )
                && timer_elapsed(_myevent_taptimer) > MYEVENT_TAPPING_TIMEOUT ){

            dprintf("myevent_scan edata=%u idx=%d tap timeout\n",
                    action->data, i);

            action->state.flags.tap_done = true;
            action->state.flags.complete = true;
            if( action->state.flags.position == myevent_pos_down )
                action->state.flags.holding = true;

            EMIT( action, myevent_change_tap_done );

        }

        if( action->state.flags.position == myevent_pos_up ){
            bool cleanup = false;

            if( action->state.flags.other == myevent_other_post
                    || ( action->state.flags.other == myevent_other_src
                        && action->state.flags.tap_done )){

                cleanup = true;

            } else if( action->state.uptimeout ){
                    if( timer_elapsed(action->state.uptimer) > action->state.uptimeout ){

                        dprintf("myevent_scan edata=%u idx=%d uptimeout=%d\n",
                                action->data, i, action->state.uptimeout );

                        action->state.flags.up_done = true;
                        EMIT(action, myevent_change_up_done);

                        cleanup = true;
                    }

            } else if( action->state.flags.tap_done ){
                cleanup = true;
            }

            if( cleanup ){
                dprintf("myevent_scan edata=%u idx=%d idle\n",
                        action->data, i);
                _myevent_idle( action );
            }
        }


    }

    _myevent_highest = max;
}

/************************************************************
 * oneshot
 */

void myevent_oneshot_event ( myevent_action_t *action, myevent_change_t change )
{
    myevent_oneshot_data_t *odata = (myevent_oneshot_data_t *)action->data;
    bool cleanup = false;

    switch( change ){
     case myevent_change_position:
        if( action->state.flags.position == myevent_pos_down ){
            if( action->state.flags.other == myevent_other_none
                    && ! action->state.flags.tap_done
                    && action->state.count == 1 ){

                dprintf("myevent_oneshot edata=%u start\n", action->data );
                (*odata->fn)( MYEVENT_ONESHOT_START, odata->data );
                odata->active = true;
            }

        } else { // up
            if( action->state.flags.holding ){
                dprintf("myevent_oneshot edata=%u clear/hold\n", action->data );
                (*odata->fn)( MYEVENT_ONESHOT_STOP, odata->data );
                odata->active = false;

            } else if( action->state.count == 1 ){
                dprintf("myevent_oneshot edata=%u oneshot\n", action->data );
                action->state.uptimeout = MYEVENT_ONESHOT_TIMEOUT;
            }
        }

        break;

     case myevent_change_other:
        if( action->state.flags.position == myevent_pos_up
                && action->state.flags.other == myevent_other_post ){

            cleanup = true;
        }

        break;

     case myevent_change_up_done:
        cleanup = true;

        break;

     case myevent_change_clear:
        cleanup = true;

        break;

     default:
        break;

    }

    if( cleanup ){
        if( action->state.count == MYEVENT_ONESHOT_TOGGLE ){
            dprintf("myevent_oneshot edata=%u locked\n", action->data );

        } else if( odata->active ){
            dprintf("myevent_oneshot edata=%u clear/oneshot\n", action->data );
            (*odata->fn)( MYEVENT_ONESHOT_STOP, odata->data );
            odata->active = false;
        }
    }
}


bool myevent_oneshot_active( myevent_action_t *action )
{
    myevent_oneshot_data_t *odata = (myevent_oneshot_data_t *)action->data;

    return odata->active;
}

/************************************************************
 * oneshot layer
 */

void myevent_oneshot_layer ( myevent_oneshot_action_t action, void *odata )
{
    myevent_oneshot_layer_data_t *ldata = (myevent_oneshot_layer_data_t *)odata;

    // TODO: layer might get applied to multiple myevent keys pressed in quick sequence
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
 * Taphold
 */

// TODO: move myevent_foreign calls to layer/mod implementations

void myevent_taphold_event ( myevent_action_t *action, myevent_change_t change )
{
    myevent_taphold_data_t *tdata = (myevent_taphold_data_t *)action->data;

    switch( change ){
     case myevent_change_position:
        if( action->state.flags.position == myevent_pos_down ){

            if( action->state.count > 1 ){
                dprintf("myevent_taphold edata=%u tap/next\n", action->data );
                // release key that was send previously
                (*tdata->fn)( MYEVENT_TAPHOLD_TAP_STOP, tdata->data );
                // 'hold' the tap key:
                (*tdata->fn)( MYEVENT_TAPHOLD_TAP_START, tdata->data );
                tdata->state = MYEVENT_TAPHOLD_TAP;
            }

        } else { // up

            switch( tdata->state ){
             case MYEVENT_TAPHOLD_HOLD:
                dprintf("myevent_taphold edata=%u hold/clear\n", action->data );
                (*tdata->fn)( MYEVENT_TAPHOLD_HOLD_STOP, tdata->data );
                tdata->state = MYEVENT_TAPHOLD_NONE;
                break;

             case MYEVENT_TAPHOLD_TAP:
                dprintf("myevent_taphold edata=%u tap/clear\n", action->data );
                (*tdata->fn)( MYEVENT_TAPHOLD_TAP_STOP, tdata->data );
                tdata->state = MYEVENT_TAPHOLD_NONE;
                break;

             case MYEVENT_TAPHOLD_NONE:
                if( action->state.count == 1 ){

                    dprintf("myevent_taphold edata=%u tap/tap\n", action->data );
                    myevent_foreign_pre(action);
                }
                break;

             default:
                break;
            }
        }

        break;

     case myevent_change_tap_done:
        if( action->state.flags.position == myevent_pos_down ){
            if( action->state.count == 1 ){
                dprintf("myevent_taphold edata=%u hold\n", action->data );
                (*tdata->fn)( MYEVENT_TAPHOLD_HOLD_START, tdata->data );
                tdata->state = MYEVENT_TAPHOLD_HOLD;
            }
        }

        break;

     case myevent_change_other:
        if( action->state.flags.position == myevent_pos_down ){
            if( action->state.flags.other ==  myevent_other_pre
                    && tdata->state == MYEVENT_TAPHOLD_NONE ){

                dprintf("myevent_taphold edata=%u tap/other\n", action->data );
                myevent_foreign_pre(action);
                (*tdata->fn)( MYEVENT_TAPHOLD_TAP_START, tdata->data );
                tdata->state = MYEVENT_TAPHOLD_TAP;
                myevent_foreign_post(action);
            }

        } else { // up
            if( action->state.flags.other ==  myevent_other_src ){
                if( tdata->state == MYEVENT_TAPHOLD_NONE ){
                    dprintf("myevent_taphold edata=%u tap/tap2\n", action->data );
                    (*tdata->fn)( MYEVENT_TAPHOLD_TAP_START, tdata->data );
                    (*tdata->fn)( MYEVENT_TAPHOLD_TAP_STOP, tdata->data );
                    myevent_foreign_post(action);
                    tdata->state = MYEVENT_TAPHOLD_NONE;
                }
            }
        }


        break;

     case myevent_change_clear:
        switch( tdata->state ){
         case MYEVENT_TAPHOLD_HOLD:
            dprintf("myevent_taphold edata=%u clear\n", action->data );
            (*tdata->fn)( MYEVENT_TAPHOLD_HOLD_STOP, tdata->data );
            tdata->state = MYEVENT_TAPHOLD_NONE;
            break;

         case MYEVENT_TAPHOLD_TAP:
            dprintf("myevent_taphold edata=%u clear\n", action->data );
            (*tdata->fn)( MYEVENT_TAPHOLD_TAP_STOP, tdata->data );
            tdata->state = MYEVENT_TAPHOLD_NONE;
            break;

         default:
            break;
        }

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


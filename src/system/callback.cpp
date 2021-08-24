/****************************************************************************
 *   Sep 14 08:11:10 2020
 *   Copyright  2020  Dirk Brosswick
 *   Email: dirk.brosswick@googlemail.com
 ****************************************************************************/
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#include "config.h"

#include "callback.h"
#include "alloc.h"

callback_t *callback_head = NULL;
static bool display_event_logging = false;

callback_t *callback_init( const char *name ) {
    /**
     * allocate an callback table
     */
    callback_t* callback = (callback_t*)CALLOC( sizeof( callback_t ), 1 );
    /**
     * was allocating successful
     */
    if ( callback == NULL ) {
        log_e("callback_t structure calloc faild for: %s", name );
    }
    else {
        /**
         * if this the first callback table, set it as head table
         */
        if ( callback_head == NULL ) {
            callback_head = callback;
        }
        /**
         * clear callback table
         */
        callback->entrys = 0;
        callback->debug = false;
        callback->table = NULL;
        callback->name = name;
        callback->next_callback_t = NULL;
        /**
         * add the callback table to the callback table chain
         */
        callback_t *callback_counter = callback_head;
        if ( callback_head != callback ) {
            while( callback_counter->next_callback_t ) {
                callback_counter = callback_counter->next_callback_t;
            }
            callback_counter->next_callback_t = callback;
        }
        log_i("init callback_t structure success for: %s", name );
    }
    return( callback );
}

bool callback_register( callback_t *callback, EventBits_t event, CALLBACK_FUNC callback_func, const char *id ) {
    bool retval = false;
    /**
     * check if callback table not NULL
     */
    if ( callback == NULL ) {
        log_w("no callback_t structure found for: %s", id );
        return( retval );
    }
    /**
     * increment callback entry counter
     */
    callback->entrys++;
    /**
     * check if this entry is the first one for allocation or reallocate
     */
    if ( callback->table == NULL ) {
        callback->table = ( callback_table_t * )CALLOC( sizeof( callback_table_t ) * callback->entrys, 1 );
        if ( callback->table == NULL ) {
            log_e("callback_table_t calloc faild for: %s", id );
            return( retval );
        }
        retval = true;
    }
    else {
        callback_table_t *new_callback_table = NULL;
        new_callback_table = ( callback_table_t * )REALLOC( callback->table, sizeof( callback_table_t ) * callback->entrys );
        if ( new_callback_table == NULL ) {
            log_e("callback_table_t realloc faild for: %s", id );
            return( retval );
        }
        callback->table = new_callback_table;
        retval = true;
    }
    /**
     * set new entry
     */
    callback->table[ callback->entrys - 1 ].event = event;
    callback->table[ callback->entrys - 1 ].callback_func = callback_func;
    callback->table[ callback->entrys - 1 ].id = id;
    callback->table[ callback->entrys - 1 ].counter = 0;
    
    return( retval );
}


bool callback_send( callback_t *callback, EventBits_t event, void *arg ) {
    bool retval = false;
    /**
     * if callback table set?
     */
    if ( callback == NULL ) {
        log_e("no callback structure found");
        return( retval );
    }
    /**
     * has callback table entrys?
     */
    if ( callback->entrys == 0 ) {
        log_w("no callback found");
        return( retval );
    }

    retval = true;
    /**
     * crowl all callback entrys with their right mask
     */
    for ( int entry = 0 ; entry < callback->entrys ; entry++ ) {
        yield();
        if ( event & callback->table[ entry ].event ) {
            /**
             * print out callback event
             */
            if ( callback->debug ) {
                log_i("call %s cb (%p:%04x:%s)", callback->name, callback->table[ entry ].callback_func, event, callback->table[ entry ].id );
            }
            /**
             * increment callback counter
             */
            callback->table[ entry ].counter++;
            /**
             * call callback an check the returnvalue
             */
            if ( !callback->table[ entry ].callback_func( event, arg ) ) {
                retval = false;
            }
        }
    }
    return( retval );
}

bool callback_send_no_log( callback_t *callback, EventBits_t event, void *arg ) {
    bool retval = false;
    /**
     * if callback table set?
     */
    if ( callback == NULL ) {
        return( retval );
    }
    /**
     * has callback table entrys?
     */
    if ( callback->entrys == 0 ) {
        return( retval );
    }

    retval = true;
    /**
     * crowl all callback entrys with their right mask
     */
    for ( int entry = 0 ; entry < callback->entrys ; entry++ ) {
        yield();
        if ( event & callback->table[ entry ].event ) {
            /**
             * increment callback counter
             */
            callback->table[ entry ].counter++;
            /**
             * call callback an check the returnvalue
             */
            if ( !callback->table[ entry ].callback_func( event, arg ) ) {
                retval = false;
            }
        }
    }
    return( retval );
}

void display_event_logging_enable( bool enable ) {
    display_event_logging = enable;
}

void callback_enable_debuging( callback_t *callback, bool debuging ) {
    callback->debug = debuging;
}
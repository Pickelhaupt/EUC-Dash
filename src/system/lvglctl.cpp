#include "config.h"
#include <stdio.h>
#include <lvgl.h>
#include "lvglctl.h"
#include "hardware/display.h"

#include "gui/gui.h"
#include "gui/keyboard.h"

#include "gui/main/mainscreen.h"
#include "gui/dashboard/dashboard.h"
#include "gui/setup/setup.h"

#include "system/eventmgm.h"
#include "hardware/display.h"
//#include "hardware/motor.h"
//#include "hardware/touch.h"

static volatile bool force_redraw = false;

bool lvglctl_eventmgm_event_cb( EventBits_t event, void *arg );
bool lvglctl_eventmgm_loop_event_cb( EventBits_t event, void *arg );

void lvglctl_init( void ) {
 
    gui_init();
    mainscreen_init();
    dashboard_init();
    setup_init();
    
    keyboard_setup();
    num_keyboard_setup();
    
    lv_disp_trig_activity( NULL );
    
    eventmgm_register_cb( EVENTMGM_STANDBY | EVENTMGM_WAKEUP | EVENTMGM_SILENCE_WAKEUP, lvglctl_eventmgm_event_cb, "lvglctl" );
    eventmgm_register_loop_cb( EVENTMGM_WAKEUP | EVENTMGM_SILENCE_WAKEUP, lvglctl_eventmgm_loop_event_cb, "lvglctl loop" );
}

bool lvglctl_eventmgm_event_cb( EventBits_t event, void *arg ) {
    //TTGOClass *ttgo = TTGOClass::getWatch();

    switch ( event ) {
        case EVENTMGM_STANDBY:          /*
                                         * get back to maintile if configure and
                                         * stop all LVGL activitys and tasks
                                         */
                                        log_i("go standby");                             
                                        stopLvglTick();
                                        break;
        case EVENTMGM_WAKEUP:           /*
                                         * resume all LVGL activitys and tasks
                                         */
                                        log_i("go wakeup");
                                        startLvglTick();
                                        lv_disp_trig_activity( NULL );
                                        break;
        case EVENTMGM_SILENCE_WAKEUP:   /*
                                         * resume all LVGL activitys and tasks
                                         */
                                        log_i("go silence wakeup");
                                        startLvglTick();
                                        lv_disp_trig_activity( NULL );
                                        break;
        case EVENTMGM_DISABLE_INTERRUPTS:
                                        /*
                                         * stop LVGL ticks
                                         */
                                        stopLvglTick();
                                        break;
        case EVENTMGM_ENABLE_INTERRUPTS:
                                        /*
                                         * stop LVGL ticks
                                         */
                                        startLvglTick();
                                        break;                                        
    }
    return( true );
}


void lvglctl_force_redraw( bool force ) {
    force_redraw = force;
}


bool lvglctl_eventmgm_loop_event_cb( EventBits_t event, void *arg ) {
    switch ( event ) {
        case EVENTMGM_WAKEUP:           if ( lv_disp_get_inactive_time( NULL ) < display_get_timeout() * 1000  || display_get_timeout() == DISPLAY_MAX_TIMEOUT ) {
                                            lv_task_handler();
                                        }
                                        else {
                                            eventmgm_set_event( EVENTMGM_STANDBY_REQUEST );
                                            //lv_task_handler();
                                        }

                                        break;
        case EVENTMGM_SILENCE_WAKEUP:   if ( lv_disp_get_inactive_time( NULL ) < display_get_timeout() * 1000 ) {
                                            lv_task_handler();
                                        }
                                        else {
                                           eventmgm_set_event( EVENTMGM_STANDBY_REQUEST );
                                           //lv_task_handler();
                                        }
                                        break;
    }
    if ( force_redraw ) {
        force_redraw = !force_redraw;
        lv_obj_invalidate( lv_scr_act() );
        // lv_refr_now( NULL );
    }
    return( true );
}

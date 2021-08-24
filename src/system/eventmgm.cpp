#include "config.h"
#include <Arduino.h>

#include "eventmgm.h"
#include "eventmgm.h"

EventGroupHandle_t eventmgm_status = NULL;
portMUX_TYPE DRAM_ATTR eventmgmMux = portMUX_INITIALIZER_UNLOCKED;

callback_t *eventmgm_callback = NULL;
callback_t *eventmgm_loop_callback = NULL;

bool eventmgm_send_event_cb( EventBits_t event );
bool eventmgm_send_loop_event_cb( EventBits_t event );

void eventmgm_init(void){
    eventmgm_status = xEventGroupCreate();
}

void eventmgm_loop(void){
    static bool lighsleep = true;
    /*
     * check if power button was release
     */
    if( eventmgm_get_event( EVENTMGM_POWER_BUTTON ) ) {
        if ( eventmgm_get_event( EVENTMGM_STANDBY | EVENTMGM_SILENCE_WAKEUP ) ) {
            eventmgm_set_event( EVENTMGM_WAKEUP_REQUEST );
        }
        else {
            eventmgm_set_event( EVENTMGM_STANDBY_REQUEST );
        }
        eventmgm_clear_event( EVENTMGM_POWER_BUTTON );
    }
    /*
     * when we are in wakeup and get an wakeup request, reset activity timer
     */
    if ( eventmgm_get_event( EVENTMGM_WAKEUP_REQUEST ) && eventmgm_get_event( EVENTMGM_WAKEUP ) ) {
        lv_disp_trig_activity( NULL );
        eventmgm_clear_event( EVENTMGM_WAKEUP_REQUEST );
    }

    /*
     * handle eventmgm request
     */
    if ( eventmgm_get_event( EVENTMGM_SILENCE_WAKEUP_REQUEST | EVENTMGM_WAKEUP_REQUEST ) ) {
        /*
         * clear eventmgm state
         */
        eventmgm_clear_event( EVENTMGM_STANDBY | EVENTMGM_SILENCE_WAKEUP | EVENTMGM_WAKEUP );

        if ( eventmgm_get_event( EVENTMGM_SILENCE_WAKEUP_REQUEST ) ) {
            log_i("go silence wakeup");
            /*
             * set silence wakeup status/request and send events
             */
            eventmgm_clear_event( EVENTMGM_SILENCE_WAKEUP_REQUEST );
            eventmgm_set_event( EVENTMGM_SILENCE_WAKEUP );
            eventmgm_send_event_cb( EVENTMGM_SILENCE_WAKEUP );
            /*
             * set cpu speed
             * 
             * note:    CONFIG_PM_ENABLE comes from the arduino IDF and is only use when
             *          an custom arduino in platformio.ini is set. Is CONFIG_PM_ENABLE is set, it enabled
             *          extra features like dynamic frequency scaling. Otherwise normal arduino function
             *          will be used.
             */
            #if CONFIG_PM_ENABLE
                pm_config.max_freq_mhz = 160;
                pm_config.min_freq_mhz = 80;
                pm_config.light_sleep_enable = true;
                ESP_ERROR_CHECK( esp_pm_configure(&pm_config) );
                log_i("custom arduino-esp32 framework detected, enable PM/DFS support, 160/80MHz with light sleep");
            #else
                setCpuFrequencyMhz(80);
                log_i("CPU speed = 80MHz");
            #endif
        }
        else {
            log_i("go wakeup");
            /**
             * set wakeup status/request and send events
             */
            eventmgm_clear_event( EVENTMGM_WAKEUP_REQUEST );
            eventmgm_set_event( EVENTMGM_WAKEUP );
            eventmgm_send_event_cb( EVENTMGM_WAKEUP );
            /**
             * set cpu speed
             * 
             * note:    CONFIG_PM_ENABLE comes from the arduino IDF and is only use when
             *          an custom arduino in platformio.ini is set. Is CONFIG_PM_ENABLE is set, it enabled
             *          extra features like dynamic frequency scaling. Otherwise normal arduino function
             *          will be used.
             */
            #if CONFIG_PM_ENABLE
                pm_config.max_freq_mhz = 240;
                pm_config.min_freq_mhz = 80;
                pm_config.light_sleep_enable = false;
                ESP_ERROR_CHECK( esp_pm_configure(&pm_config) );
                log_i("custom arduino-esp32 framework detected, enable PM/DFS support, 240/80MHz with light sleep");
            #else
                setCpuFrequencyMhz(240);
                log_i("CPU speed = 240MHz");
            #endif
        }

        log_i("Free heap: %d", ESP.getFreeHeap());
        log_i("Free PSRAM heap: %d", ESP.getFreePsram());
        log_i("uptime: %d", millis() / 1000 );

    }        
    else if( eventmgm_get_event( EVENTMGM_STANDBY_REQUEST ) ) {
        /*
         * avoid buzz when standby after silent wake
         */
        if ( eventmgm_get_event( EVENTMGM_SILENCE_WAKEUP ) ) {
            delay( 100 );
        }
        /*
         * clear eventmgm state/request and send standby event
         */
        eventmgm_clear_event( EVENTMGM_STANDBY_REQUEST );
        eventmgm_clear_event( EVENTMGM_STANDBY | EVENTMGM_SILENCE_WAKEUP | EVENTMGM_WAKEUP );
        eventmgm_set_event( EVENTMGM_STANDBY );
        /*
         * send EVENTMGM_STANDBY to all registered callback functions and
         * check if an standby callback block lightsleep in standby
         */
        lighsleep = eventmgm_send_event_cb( EVENTMGM_STANDBY );
        /*
         * print some memory stats
         */
        log_i("Free heap: %d", ESP.getFreeHeap());
        log_i("Free PSRAM heap: %d", ESP.getFreePsram());
        log_i("uptime: %d", millis() / 1000 );

        if ( lighsleep ) {
            log_i("go standby");
            /*
             * set cpu speed
             * 
             * note:    direct after change the CPU clock, we go to light sleep.
             *          it is no difference in light sleep we have 80Mhz or 10Mhz
             *          CPU clock. Current is the same.
             */
            setCpuFrequencyMhz( 80 );
            log_i("CPU speed = 80MHz, start light sleep");
            /*
             * from here, the consumption is round about 2.5mA
             * total standby time is 152h (6days) without use?
             */
            esp_light_sleep_start();
        }
        else {
            log_i("go standby blocked");
            /*
             * set cpu speed
             * 
             * note:    CONFIG_PM_ENABLE comes from the arduino IDF and is only use when
             *          an custom arduino in platformio.ini is set. Is CONFIG_PM_ENABLE is set, it enabled
             *          extra features like dynamic frequency scaling. Otherwise normal arduino function
             *          will be used.
             */
            #if CONFIG_PM_ENABLE
                /*
                 * from here, the consumption is round about 20mA with ble
                 * total standby time is 15h with a 350mAh battery
                 */
                pm_config.max_freq_mhz = 80;
                pm_config.min_freq_mhz = 40;
                pm_config.light_sleep_enable = true;
                ESP_ERROR_CHECK( esp_pm_configure(&pm_config) );
                log_i("custom arduino-esp32 framework detected, enable PM/DFS support, 80/40MHz with light sleep");
            #else
                /*
                 * from here, the consumption is round about 28mA with ble
                 * total standby time is 10h with a 350mAh battery
                 */
                setCpuFrequencyMhz(80);
                log_i("CPU speed = 80MHz");
            #endif
        }
    }
    /*
     * send loop event depending on powermem state
     */
    if ( eventmgm_get_event( EVENTMGM_STANDBY ) ) {
        /*
         * Idle when lightsleep in standby not allowed
         * It make it possible for the IDLE task to trottle
         * down CPU clock or go into light sleep.
         * 
         * note:    When change vTaskDelay to an higher value, please
         *          note that the reaction time to wake up increase.
         */
        if ( !lighsleep )
            vTaskDelay( 250 );
        eventmgm_send_loop_event_cb( EVENTMGM_STANDBY );
    }
    else if ( eventmgm_get_event( EVENTMGM_WAKEUP ) ) {
        eventmgm_send_loop_event_cb( EVENTMGM_WAKEUP );
    }
    else if ( eventmgm_get_event( EVENTMGM_SILENCE_WAKEUP ) ) {
        eventmgm_send_loop_event_cb( EVENTMGM_SILENCE_WAKEUP );
    }
}

void eventmgm_shutdown( void ) {
    eventmgm_send_event_cb( EVENTMGM_SHUTDOWN );
    //pmu_shutdown();
}

void eventmgm_reset( void ) {
    eventmgm_send_event_cb( EVENTMGM_RESET );
    ESP.restart();
}

void eventmgm_set_perf_mode( void ) {
    #if CONFIG_PM_ENABLE
        pm_config.max_freq_mhz = 240;
        pm_config.min_freq_mhz = 240;
        pm_config.light_sleep_enable = false;
        ESP_ERROR_CHECK( esp_pm_configure(&pm_config) );
    #else
        setCpuFrequencyMhz(240);
    #endif
}

void eventmgm_set_normal_mode( void ) {
    #if CONFIG_PM_ENABLE
        pm_config.max_freq_mhz = 240;
        pm_config.min_freq_mhz = 80;
        pm_config.light_sleep_enable = false;
        ESP_ERROR_CHECK( esp_pm_configure(&pm_config) );
    #else
        setCpuFrequencyMhz(240);
    #endif
}

void eventmgm_set_event( EventBits_t bits ) {
    portENTER_CRITICAL(&eventmgmMux);
    xEventGroupSetBits( eventmgm_status, bits );
    portEXIT_CRITICAL(&eventmgmMux);
}

void eventmgm_clear_event( EventBits_t bits ) {
    portENTER_CRITICAL(&eventmgmMux);
    xEventGroupClearBits( eventmgm_status, bits );
    portEXIT_CRITICAL(&eventmgmMux);
}

EventBits_t eventmgm_get_event( EventBits_t bits ) {
    portENTER_CRITICAL(&eventmgmMux);
    EventBits_t temp = xEventGroupGetBits( eventmgm_status ) & bits;
    portEXIT_CRITICAL(&eventmgmMux);
    return( temp );
}

bool eventmgm_register_cb( EventBits_t event, CALLBACK_FUNC callback_func, const char *id ) {
    if ( eventmgm_callback == NULL ) {
        eventmgm_callback = callback_init( "eventmgm" );
        if ( eventmgm_callback == NULL ) {
            log_e("eventmgm callback alloc failed");
            while(true);
        }
    }  
    log_i("registering event_cb %s", id);  
    return( callback_register( eventmgm_callback, event, callback_func, id ) );
}

bool eventmgm_register_loop_cb( EventBits_t event, CALLBACK_FUNC callback_func, const char *id ) {
    if ( eventmgm_loop_callback == NULL ) {
        eventmgm_loop_callback = callback_init( "eventmgm loop" );
        if ( eventmgm_loop_callback == NULL ) {
            log_e("eventmgm loop callback alloc failed");
            while(true);
        }
    }
    log_i("registering event_loop_cb %s", id);    
    return( callback_register( eventmgm_loop_callback, event, callback_func, id ) );
}

bool eventmgm_send_event_cb( EventBits_t event ) {
    return( callback_send( eventmgm_callback, event, (void*)NULL ) );
}

bool eventmgm_send_loop_event_cb( EventBits_t event ) {
    return( callback_send_no_log( eventmgm_loop_callback, event, (void*)NULL ) );
}

void eventmgm_disable_interrupts( void ) {
    eventmgm_send_event_cb( EVENTMGM_DISABLE_INTERRUPTS );
}

void eventmgm_enable_interrupts( void ) {
    eventmgm_send_event_cb( EVENTMGM_ENABLE_INTERRUPTS );
}

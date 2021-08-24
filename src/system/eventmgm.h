#ifndef _EVENTMGM_H
    #define _EVENTMGM_H

    #include "config.h"
    #include "callback.h"

    #define EVENTMGM_STANDBY                    _BV(0)         /** @brief event mask for eventmgm standby */
    #define EVENTMGM_STANDBY_REQUEST            _BV(1)         /** @brief event mask for eventmgm standby request */
    #define EVENTMGM_SILENCE_WAKEUP             _BV(2)         /** @brief event mask for eventmgm silence wakeup */
    #define EVENTMGM_SILENCE_WAKEUP_REQUEST     _BV(3)         /** @brief event mask for eventmgm wakeup silence request */
    #define EVENTMGM_WAKEUP                     _BV(4)         /** @brief event mask for eventmgm wakeup */
    #define EVENTMGM_WAKEUP_REQUEST             _BV(5)         /** @brief event mask for eventmgm wakeup request */
    #define EVENTMGM_POWER_BUTTON               _BV(6)         /** @brief event mask for eventmgm pmu button is pressed */
    #define EVENTMGM_SHUTDOWN                   _BV(12)        /** @brief event mask for eventmgm shutdown */
    #define EVENTMGM_RESET                      _BV(13)        /** @brief event mask for eventmgm reset */
    #define EVENTMGM_SAVE_CONFIG                _BV(14)        /** @brief event mask for eventmgm save config */
    #define EVENTMGM_DISABLE_INTERRUPTS         _BV(15)        
    #define EVENTMGM_ENABLE_INTERRUPTS          _BV(16)    

    /**
     * @brief setp event managment, coordinate managment beween CPU, wifictl, pmu, bma, display, backlight and lvgl
     */
    void eventmgm_init( void );
    /**
     * @brief event managment loop routine, main loop for the program
     */
    void eventmgm_loop(void);
    /**
     * @brief trigger a power managemt event
     * 
     * @param   bits    event to trigger, example: EVENTMGM_WIFI_ON_REQUEST for switch an WiFi
     */
    void eventmgm_set_event( EventBits_t bits );
    /**
     * @brief clear a power managemt event
     * 
     * @param   bits    event to trigger, example: EVENTMGM_WIFI_ON_REQUEST for switch an WiFi
     */
    void eventmgm_clear_event( EventBits_t bits );
    /**
     * @brief get a power managemt event state
     * 
     * @param   bits    event state, example: EVENTMGM_STANDBY to evaluate if the system in standby
     * 
     * @return  EventBits_t    event state
     */
    EventBits_t eventmgm_get_event( EventBits_t bits );
    /**
     * @brief registers a callback function which is called on a corresponding event
     * 
     * @param   event               possible values: EVENTMGM_STANDBY, EVENTMGM_SILENCE_WAKEUP, EVENTMGM_WAKEUP and EVENTMGM_RTC_ALARM
     * @param   callback_func       pointer to the callback function 
     * @param   id                  pointer to an string
     * 
     * @return  TRUE if successful, FALSE if not successful
     * 
     * @note  Your callback function return TRUE if all fine, FALSE when you want break, by example into to standby.
     */
    bool eventmgm_register_cb( EventBits_t event, CALLBACK_FUNC callback_func, const char *id );
    /**
     * @brief registers a callback function which is called on a corresponding loop event
     * 
     * @param   event               possible values: EVENTMGM_STANDBY, EVENTMGM_SILENCE_WAKEUP, EVENTMGM_WAKEUP
     * @param   callback_func       pointer to the callback function 
     * @param   id                  pointer to an string
     */
    bool eventmgm_register_loop_cb( EventBits_t event, CALLBACK_FUNC callback_func, const char *id );
    /**
     * @brief send an interrupt disable request
     */
    void eventmgm_disable_interrupts( void );
    /**
     * @brief send an interrupt enable request
     */
    void eventmgm_enable_interrupts( void );
    /**
     * @bried set performace mode 240/240Mhz (only custom framework)
     */
    void eventmgm_set_perf_mode( void );
    /**
     * @brief set normal mode 240/80Mhz (only custom framework)
     */
    void eventmgm_set_normal_mode( void );

#endif
#ifndef _POWER_H
    #define _POWER_H
    #include "hardware.h"

    #ifdef HAS_AXP202
        #include "axp20x.h"    
    #endif

    uint8_t power_get_battpct( void );
    
    float power_get_battvolt( void );

    bool power_get_charging( void );

    uint16_t power_batt_analog_read( void );

    void power_init( void );

#endif
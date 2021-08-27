#ifndef _RTC_H
    #define _RTC_H
    #include "RTClib.h"
    
    /**
    * @brief set the rtc time
    * 
    * @param   year YYYY
    * @param   month MM
    * @param   day   DD
    * @param   hour  HH
    * @param   minute mm
    * @param   second SS
    */
    void rtc_set_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
    /**
    * @brief get current time from rtc
    * 
    * @return   time_t unixtime
    */
    time_t rtc_get_time();
    /**
    * @brief init the RTC
    */
    void rtc_init( void );

    char* rtc_get_clockstring();

    char* rtc_get_datestring();

#endif
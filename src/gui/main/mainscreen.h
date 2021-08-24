#ifndef _MAINSCREEN_H_
    #define _MAINSCREEN_H_
    #include "lvgl.h"

    void mainscreen_init(void);
    //Functions
    /**
    * @brief reload the full main screen
    */
    void mainscreen_tile_reload(void);
    /**
    * @brief update time and date
    * 
    * @param ctime current unixtime
    */
    void mainscreen_update_time(time_t ctime);
    /**
    * @brief update outside temperature label
    * 
    * @param ctemp temperature in celsius
    * @param fahrenheit set to true to display temperature as fahrenheit
    */
    void mainscreen_update_out_temp(int ctemp, bool fahrenheit);
    /**
    * @brief update inside temperature label
    * 
    * @param ctemp temperature in celsius
    * @param fahrenheit set to true to display temperature as fahrenheit
    */
    void mainscreen_update_in_temp(int ctemp, bool fahrenheit);
    /**
    * @brief update relative humidity label
    * 
    * @param crh relative humidity in percent
    */
    void mainscreen_update_rh(int crh);
    /**
    * @brief update barometer label
    * 
    * @param cbaro barometric pressure in hPa/mbar
    */
    void mainscreen_update_baro(int cbaro);

    uint32_t mainscreen_get_tile_num(void);

#endif
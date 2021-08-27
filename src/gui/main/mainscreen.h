#ifndef _MAINSCREEN_H_
    #define _MAINSCREEN_H_
    #include "lvgl.h"

    #define MAINSCREEN_UPDATE_INTERVAL 15 //update time every 15 seconds

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
    
    uint32_t mainscreen_get_tile_num(void);

#endif
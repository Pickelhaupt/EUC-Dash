#ifndef _CONFIG_H
    #define _CONFIG_H

    #include <FreeRTOS.h>
    #include "esp_task_wdt.h"
    #include <lvgl.h>
    #include <SPI.h>
    #include <Wire.h>
    #include <Ticker.h>
    #include <Arduino.h>
    //#include "hardware/hardware.h"

    #define _FIRMWARE_  2021042301
    //define environment in platformio.ini
    #ifndef ENV_DEFINED
        //#define TTGO_T4
        #define OSW
        //#define TWATCH_2020V1 //incomplete, complete in hardware.h before using
    #endif

    #define LV_LVGL_H_INCLUDE_SIMPLE
    
    #define TIME_UPDATE_DELAY 10000 //update time every 10 seconds
#endif //CONFIG_H
#ifndef _HARDWARE_H
    #define _HARDWARE_H
    #include "config.h"
    #include <TFT_eSPI.h>

    #ifdef TTGO_T4
        #define HAS_PWM_BL
        #define HAS_BUTTONS
        #define HAS_SD
        #define HAS_AMBLS
        #define HAS_DS1307
        //#define HAS_DS3231
        
        #define TFT_BL    4  // Dispaly backlight control pin

        #define SD_MISO     2
        #define SD_MOSI     15
        #define SD_SCLK     14
        #define SD_CS       13

        #define BUTTON_1    37
        #define BUTTON_2    38
        #define BUTTON_3    39
        #define BUTTONS_MAP {BUTTON_1,BUTTON_2,BUTTON_3}

        #define SPEAKER_PWD 19
        #define SPEAKER_OUT 25
        #define ADC_IN      35

        #ifdef HAS_MOTOR
            #define MOTOR_PIN               4 //change to the pin controlling the motor
        #endif
    #endif //TTGO_T4

    #ifdef OSW
        #define HAS_BUTTONS
        #define HAS_PWM_BL
        #define HAS_BMA
        #define HAS_BMA400
        #define HAS_RTC
        #define HAS_DS3231
        #define NO_PMU

        #define TFT_BL    9  // Dispaly backlight control pin
        
        #ifdef SPI_READ_FREQUENCY
            #undef SPI_READ_FREQUENCY
            #define SPI_READ_FREQUENCY 20000000
        #endif
        #define RTC_INT 32

        #define BMA_INT_1 34
        #define BMA_INT_2 35

        #define BUTTON_1    0
        #define BUTTON_2    13
        #define BUTTON_3    10
        #define BUTTONS_MAP {BUTTON_1,BUTTON_2,BUTTON_3}

        #define EXT_PWR_PIN 15
        #define BATT_MON_PIN 25

        #ifdef HAS_MOTOR
            #define MOTOR_PIN               4 //change to the pin controlling the motor
        #endif

    #endif //OSW_BOARD

    #ifdef TWATCH_2020V1
        //incomplete, complete before using
        #define HAS_PWM_BL
        #define HAS_TOUCH
        #define HAS_MOTOR
        #define HAS_AXP202
        #define HAS_BMA
        #define HAS_BMA423
        #define HAS_RTC
        #define HAS_PFC8563
        
        #define TFT_BL              12

        #define TOUCH_SDA           23
        #define TOUCH_SCL           32
        #define TOUCH_INT           38

        #define RTC_INT             37
        #define AXP202_INT          35
        #define BMA423_INT1         39

        #ifdef HAS_MOTOR
            #define MOTOR_PIN       4
        #endif

    #endif //T_WATCH_2020V1

    #define I2C_SDA     21
    #define I2C_SCL     22

    #define CHANNEL_0   0

#endif
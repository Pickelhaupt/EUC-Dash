#ifndef _HARDWARE_H
    #define _HARDWARE_H
    #include "config.h"

    #ifdef T4_BOARD
        #define HAS_PWM_BL
        #define HAS_BUTTONS
        #define HAS_SD
        #define HAS_AMBLS
        #define HAS_DS1307
        //#define HAS_DS3231
        
        //TFT_eSPI configuration
        #define ILI9341_DRIVER      
        #define TFT_WIDTH  240
        #define TFT_HEIGHT 320
        

        #define TFT_MISO 12
        #define TFT_MOSI 23
        #define TFT_SCLK 18
        #define TFT_CS   27  // Chip select control pin
        #define TFT_DC   32  // Data Command control pin
        #define TFT_RST   5  // Reset pin (could connect to RST pin)
        #define TFT_BL    4  // Dispaly backlight control pin

        #define SPI_FREQUENCY  80000000
        #define USER_SETUP_LOADED

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
    #endif //T4_BOARD

    #ifdef OSW_BOARD
        #define HAS_BUTTONS
        #define HAS_PWM_BL
        #define HAS_BMA
        #define HAS_BMA400
        #define HAS_RTC
        #define HAS_DS3231
        #define NO_PMU

        //TFT_eSPI configuration
        
        #define GC9A01_DRIVER
        #define TFT_WIDTH  240
        #define TFT_HEIGHT 240

        #define TFT_MISO -1
        #define TFT_MOSI 23
        #define TFT_SCLK 18
        #define TFT_CS    5  // Chip select control pin
        #define TFT_DC   12  // Data Command control pin
        #define TFT_RST  33  // Reset pin (could connect to RST pin)
        #define TFT_BL    9  // Dispaly backlight control pin

        #define SPI_FREQUENCY  40000000
        #define SPI_READ_FREQUENCY  20000000
        #define SPI_TOUCH_FREQUENCY  2500000
        #define USER_SETUP_LOADED
        // #define SUPPORT_TRANSACTIONS

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

    #ifdef T_WATCH_2020V1
        //incomplete, complete before using
        #define HAS_PWM_BL
        #define HAS_TOUCH
        #define HAS_MOTOR
        #define HAS_AXP202
        #define HAS_BMA
        #define HAS_BMA423
        #define HAS_RTC
        #define HAS_PFC8563
        
        #define ST7789_DRIVER
        #define TFT_WIDTH           240
        #define TFT_HEIGHT          240

        #define TFT_MISO            0
        #define FT_MOSI             19
        #define TFT_SCLK            18
        #define FT_CS               5
        #define FT_DC               27
        #define TFT_RST             -1
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
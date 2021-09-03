#ifndef _DISPLAY_H
  #define _DISPLAY_H
    //#include <lvgl.h>
  #include "hardware/hardware.h"
  #include "config/displayconfig.h"

  #ifdef HAS_AMBLS //if the board has an ambient light sensor
    #define LIGHTSENSE_PIN      35  //
    #define DISPLAY_GAIN        15  //increase to make the display start getting brighter at a lower light level
    #define BRIGHTNESS_UPDATE_DELAY 200 //update display brightness every 200ms
  #endif

  #ifdef HAS_PWM_BL
    //Configuration for dimming the backlight
    #define LEDFREQ             12000 //PWM frequency
    #define LEDCHAN             4   //PWM control channel
    #define LEDRES              16  //led PWM resolution
    #define FADETIME            300 //300ms second fade when changing brightness
  
    #define DISPLAY_MINLEVEL    40  //brightness level in darkness
    //very little visible increase above 200
    //dutycycle = DISPLAY_MAXLEVEL ^2, so 225 is equivalent to approx 75 percent 
    //this will will appear to be approx 90% brightness to the eye and the display runs much cooler
    #define DISPLAY_MAXLEVEL    225
    //end LED dimming config
  #endif

  #define DISPLAY_DEFAULT_TIMEOUT   15

  //LVGL defines
  #ifdef TTGO_T4
    #define DISPLAY_HORRES      320
    #define DISPLAY_VERTRES     240
    #define DISPLAY_BUFSIZE     (320*80)
    #define LVGL_DBL_BUFFER
  #endif
  #ifdef OSW
    #define DISPLAY_HORRES      240
    #define DISPLAY_VERTRES     240
    #define DISPLAY_BUFSIZE     (240*80)
    //#define LVGL_DBL_BUFFER
  #endif
  #ifdef TWATCH_2020V2
    #define DISPLAY_HORRES      240
    #define DISPLAY_VERTRES     240
    #define DISPLAY_BUFSIZE     (240*80)
    //#define LVGL_DBL_BUFFER
  #endif
  //End LVGL defines

  enum {
    DISPLAY_ROT_0,
    DISPLAY_ROT_90,
    DISPLAY_ROT_180,
    DISPLAY_ROT_270,
  };

  /** @brief init the display TFT_eSPI @return  true if init successful*/ 
  bool display_init(void);
  /** @brief set display brightness @param level 0-255 brightness level @return brightness level*/
  int display_set_brightness(int level, int fadetime);
  /** @brief get display brightness @return brightness level 0-255 */    
  int display_get_brightness(void);
  /** @brief get ambient light level */
  int display_get_amb_light(void);
  /** @brief automatically set screen brightness based on ambient light */
  int display_auto_set_brightness(void);
  /** @brief set display rotation @param rotation  DISPLAY_ROT_0,  DISPLAY_ROT_90, DISPLAY_ROT_180 or DISPLAY_ROT_270,*/
  void display_set_rotation(int rotation);
  //void startLvglTick();
  //void stopLvglTick();

  void display_set_timeout(uint32_t value);
  uint32_t display_get_timeout( void );
  

#endif
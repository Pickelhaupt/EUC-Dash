#include "display.h"
#include "config.h"
#include "hardware.h"
#include "driver/ledc.h"
#include "system/eventmgm.h"

//#include <TFT_eSPI.h>


display_config_t display_config;
byte display_brightness;
Ticker *tickTicker = nullptr;

TFT_eSPI disp_tft = TFT_eSPI(); // Invoke library

static lv_disp_buf_t disp_buf;
static lv_color_t buf1[DISPLAY_BUFSIZE];
#ifdef LVGL_DBL_BUFFER
    static lv_color_t buf2[DISPLAY_BUFSIZE];
#endif

bool display_eventmgm_event_cb( EventBits_t event, void *arg );

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    disp_tft.startWrite();
    disp_tft.setAddrWindow(area->x1, area->y1, w, h);
    //disp_tft.pushColors(&color_p->full, w * h, true);
    //disp_tft.pushColors(( uint16_t *) &color_p->full, w * h, false);
    //disp_tft.pushColors(( uint16_t *)color_p, w * h, true);
    //disp_tft.pushPixels(( uint16_t *)color_p, w * h);
    disp_tft.pushPixelsDMA(( uint16_t *)color_p, w * h);
    disp_tft.endWrite();

    lv_disp_flush_ready(disp);
}

void startLvglTick()
{
    Serial.println("starting lvgl tick");
    tickTicker->attach_ms(5, []() {
        lv_tick_inc(5);
    });
}

void stopLvglTick()
{  
    Serial.println("stopping lvgl tick");
    tickTicker->detach();
}

void display_load_config(void){
    display_config.load();
}

void display_save_config(void){
    display_config.save();
}


bool display_init() {
    bool init_success;

    //setup backlight PWM control see display.h
    pinMode(TFT_BL, OUTPUT);
    ledcSetup(LEDCHAN, LEDFREQ, LEDRES);
    ledcAttachPin(TFT_BL, LEDCHAN);
    ledc_fade_func_install(ESP_INTR_FLAG_IRAM);

    //setup initial display
    lv_init();

    disp_tft.init();
    display_set_rotation(DISPLAY_ROT_180);
    disp_tft.initDMA();
    disp_tft.fillScreen(0);
    
    #ifdef LVGL_DBL_BUFFER
        lv_disp_buf_init(&disp_buf, buf1, buf2, DISPLAY_BUFSIZE);
    #else
        lv_disp_buf_init(&disp_buf, buf1, NULL, DISPLAY_BUFSIZE);
    #endif   
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    
    disp_drv.hor_res = DISPLAY_HORRES;
    disp_drv.ver_res = DISPLAY_VERTRES;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);

    display_load_config();
    display_set_timeout(30);

    tickTicker = new Ticker();
    startLvglTick();

    eventmgm_register_cb( EVENTMGM_STANDBY | EVENTMGM_WAKEUP | EVENTMGM_SILENCE_WAKEUP, display_eventmgm_event_cb, "display events" );

    init_success = true;
    return init_success;
}

void display_bl_off( void ) {
    display_set_brightness(0, 10);
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_4, 0);
}

void display_bl_on(void){
    display_set_brightness(220, 100);
}

void display_sleep(){
    disp_tft.writecommand(0x10);
}

void display_wakeup(){
    disp_tft.writecommand(0x11);
}

bool display_eventmgm_event_cb( EventBits_t event, void *arg ) {
    //TTGOClass *ttgo = TTGOClass::getWatch();

    switch ( event ) {
        case EVENTMGM_STANDBY:          /*
                                         * turn off backlight
                                         */
                                        log_i("go standby");
                                        display_sleep();                             
                                        display_bl_off();

                                        break;
        case EVENTMGM_WAKEUP:           /*
                                         * turn on backlight
                                         */
                                        log_i("go wakeup");
                                        display_wakeup();
                                        display_bl_on();
                                        break;
        case EVENTMGM_SILENCE_WAKEUP:   /*
                                         * do not turn on backlight
                                         */
                                        log_i("go silence wakeup");
                                        break;                                       
    }
    return( true );
}

void display_set_rotation(int rotation) {
    disp_tft.setRotation(rotation);
    disp_tft.resetViewport();
}

int display_set_brightness(int level, int fadetime) {
    uint32_t dc = level * level;
    ledc_set_fade_time_and_start(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_4, dc, fadetime, LEDC_FADE_NO_WAIT);
    display_brightness = level;
    return level;
}

int display_get_brightness() {
    return display_brightness;
}

#ifdef HAS_AMBLS
int display_get_amb_light() {
    int lightlevel = 0; 
    analogReadResolution(12); //to enable enough resolution at low light levels
    analogSetPinAttenuation(LIGHTSENSE_PIN, ADC_11db);
    lightlevel = analogRead(LIGHTSENSE_PIN);
    //Serial.println(lightlevel);
    lightlevel = 2700 - lightlevel;

    lightlevel = (lightlevel * 256 / 3000); //convert to 8 bit value
    return lightlevel;
}

int display_auto_set_brightness(void) {
    static int old_lghtlvl = 0;
    int lghtlvl = display_get_amb_light() + DISPLAY_GAIN;
    if (lghtlvl > DISPLAY_MAXLEVEL) lghtlvl = DISPLAY_MAXLEVEL;
    if (lghtlvl < DISPLAY_MINLEVEL) lghtlvl = DISPLAY_MINLEVEL;
    int lvldiff = lghtlvl - old_lghtlvl;
    //Serial.println(lvldiff);
    //light has to change by at least 10 units before new level is set to reduce pulsating effect
    if (lvldiff > 10 || lvldiff < -10 || old_lghtlvl == 0) {
        display_set_brightness(lghtlvl, FADETIME);
        old_lghtlvl = lghtlvl;
        Serial.print("setting level to: ");
        Serial.println(lghtlvl);
    }
    
    return lghtlvl;
}
#endif

void display_set_timeout(uint32_t value) {
    display_config.timeout = value;
    display_save_config();
}

uint32_t display_get_timeout( void ) {
    if (display_config.timeout < DISPLAY_MIN_TIMEOUT) display_config.timeout = DISPLAY_MIN_TIMEOUT;
    return( display_config.timeout );
}

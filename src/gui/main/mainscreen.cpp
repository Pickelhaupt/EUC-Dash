#include <Arduino.h>
#include <Ticker.h>
#include <lvgl.h>
#include "gui/gui.h"
#include "gui/setup/setup.h"
#include "gui/dashboard/dashboard.h"
#include "mainscreen.h"
#include "hardware/button.h"
#include "hardware/rtc.h"
#include "hardware/power.h"
#include "system/eventmgm.h"

uint32_t mainscreen_tile_num;
bool mainscreen_active = true;
unsigned long oldmillis = 0;

static lv_obj_t *mainscreen_cont = NULL;
static lv_obj_t *time_label;
static lv_obj_t *date_label;
static lv_obj_t *batt_label;

static lv_obj_t *time_cont;

static lv_style_t mainscreen_style;
static lv_style_t mainscreen_timestyle;
static lv_style_t mainscreen_datestyle;
static lv_style_t mainscreen_battstyle;
static lv_style_t mainscreen_valuestyle;
static lv_style_t mainscreen_unitstyle;
static lv_style_t mainscreen_labelstyle;
static lv_style_t mainscreen_linestyle;
static lv_style_t mainscreen_barstyle;

void mainscreen_init_styles() {
    lv_style_copy(&mainscreen_style, gui_get_style());

    lv_style_copy(&mainscreen_timestyle, gui_get_textstyle());
    lv_style_set_text_font(&mainscreen_timestyle, LV_STATE_DEFAULT, &DIN1451_m_cond_100);
    lv_style_set_text_color(&mainscreen_timestyle, LV_STATE_DEFAULT, watch_colour);

    lv_style_copy(&mainscreen_datestyle, gui_get_textstyle());
    lv_style_set_text_font(&mainscreen_datestyle, LV_STATE_DEFAULT, &DIN1451_m_cond_36);
    lv_style_set_text_color(&mainscreen_datestyle, LV_STATE_DEFAULT, LV_COLOR_RED);

    lv_style_copy(&mainscreen_battstyle, gui_get_textstyle());
    lv_style_set_text_font(&mainscreen_battstyle, LV_STATE_DEFAULT, &DIN1451_m_cond_28);
    lv_style_set_text_color(&mainscreen_battstyle, LV_STATE_DEFAULT, LV_COLOR_RED);


    lv_style_copy(&mainscreen_valuestyle, gui_get_textstyle());
    lv_style_set_text_font(&mainscreen_valuestyle, LV_STATE_DEFAULT, &DIN1451_m_cond_44);

    lv_style_copy(&mainscreen_unitstyle, gui_get_textstyle());
    lv_style_set_text_font(&mainscreen_unitstyle, LV_STATE_DEFAULT, &DIN1451_m_cond_24);

    lv_style_copy(&mainscreen_labelstyle, gui_get_textstyle());
    lv_style_set_text_font(&mainscreen_labelstyle, LV_STATE_DEFAULT, &DIN1451_m_cond_28);
    lv_style_set_text_color(&mainscreen_labelstyle, LV_STATE_DEFAULT, gui_color_dark_pajero_green);
    lv_style_set_pad_all(&mainscreen_labelstyle, LV_STATE_DEFAULT, 2);

    lv_style_copy(&mainscreen_linestyle, gui_get_linestyle());
    lv_style_set_line_width(&mainscreen_linestyle, LV_STATE_DEFAULT, 2);
    lv_style_set_line_color(&mainscreen_linestyle, LV_STATE_DEFAULT, default_color);

    lv_style_copy(&mainscreen_barstyle, gui_get_linestyle());
    lv_style_set_outline_width(&mainscreen_barstyle, LV_STATE_DEFAULT, 2);
    lv_style_set_outline_color(&mainscreen_barstyle, LV_STATE_DEFAULT, gui_color_dark_pajero_green);
    lv_style_set_bg_color(&mainscreen_barstyle, LV_STATE_DEFAULT, gui_color_black);

}

void mainscreen_activate_cb(void)
{
    //lv_group_focus_obj(mainscreen_cont);
    mainscreen_active = true;
    mainscreen_update_time(rtc_get_time());
}

void mainscreen_hibernate_cb(void)
{
    mainscreen_active = false;
}

void mainscreen_create_conts(void){
    time_cont = lv_cont_create(mainscreen_cont, NULL);
    lv_obj_set_size(time_cont, lv_disp_get_hor_res( NULL ) , lv_disp_get_ver_res( NULL ));
    lv_obj_reset_style_list(time_cont, LV_CONT_PART_MAIN);
    lv_obj_add_style(time_cont, LV_LABEL_PART_MAIN, &mainscreen_style);
    lv_obj_align(time_cont, NULL, LV_ALIGN_CENTER, 0, 0);
}

void mainscreen_create_time_label(void){
    time_label = lv_label_create(time_cont, NULL);
    lv_obj_add_style(time_label, LV_LABEL_PART_MAIN, &mainscreen_timestyle);
    lv_label_set_text(time_label, "00:00");
    lv_obj_align(time_label, NULL, LV_ALIGN_CENTER, 0, -10);
}

void mainscreen_create_date_label(void){
    date_label = lv_label_create(time_cont, NULL);
    lv_obj_add_style(date_label, LV_LABEL_PART_MAIN, &mainscreen_datestyle);
    lv_label_set_text(date_label, "Fri Apr 16 2021");
    lv_obj_align(date_label, NULL, LV_ALIGN_CENTER, 0, 45);
}

void mainscreen_create_batt_label(void){
    batt_label = lv_label_create( time_cont , NULL);
    lv_label_set_text(batt_label, "99%");
    lv_obj_reset_style_list( batt_label, LV_OBJ_PART_MAIN );
    lv_obj_add_style( batt_label, LV_OBJ_PART_MAIN, &mainscreen_battstyle );
    lv_obj_align( batt_label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -5 );
}

void mainscreen_update_time(time_t ctime){
    char timebuf[8];
    char datebuf[16];
    struct tm time_tm;
    localtime_r(&ctime, &time_tm);
    //localtime_r(&now, &time_tm);
    strftime(timebuf, sizeof(timebuf), "%H:%M", &time_tm);
    strftime(datebuf, sizeof(datebuf), "%a %d %b %Y", &time_tm);
    lv_label_set_text(time_label, timebuf);
    lv_obj_realign(time_label);
    lv_label_set_text(date_label, datebuf);
    lv_obj_realign(date_label);
}

void mainscreen_update_batt(void){
    float voltage = power_get_battvolt();
    uint16_t analogue_value = power_batt_analog_read();

    char pctst[2] = "%";
    char anastr[4] = {0};
    dtostrf(analogue_value, 3, 0, anastr);
    lv_label_set_text(batt_label, anastr);
    lv_obj_align( batt_label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -5 );
}

uint32_t mainscreen_get_tile_num(void) {
    return mainscreen_tile_num;
}


void mainscreen_tile_reload(void)
{
    log_i("reloading main screen");
    lv_obj_clean(mainscreen_cont);
    mainscreen_init_styles();
    mainscreen_create_conts();
    mainscreen_create_time_label();
    mainscreen_create_date_label();
    mainscreen_create_batt_label();
}

bool mainscreen_event_loop_cb(EventBits_t event, void *arg){
    switch ( event ) {
        case EVENTMGM_WAKEUP:           if(millis() >= oldmillis + (MAINSCREEN_UPDATE_INTERVAL * 1000) && mainscreen_active){
                                            mainscreen_update_time(rtc_get_time());
                                            mainscreen_update_batt();
                                            oldmillis = millis();
                                            log_i("updating time");
                                        }
                                        break;
        case EVENTMGM_SILENCE_WAKEUP:   
                                        break;
        case EVENTMGM_STANDBY:   
                                        break;
    }
    
    return true;
}

void mainscreen_init(){
    mainscreen_tile_num = gui_add_tile(0, 0, "mainscreen tile");
    mainscreen_cont = gui_get_tile_obj(mainscreen_tile_num);
 
    lv_obj_set_size(mainscreen_cont, lv_disp_get_hor_res( NULL ) , lv_disp_get_ver_res( NULL ));
    log_i("setting up main screen");
    mainscreen_tile_reload();
    mainscreen_update_time(rtc_get_time());
    gui_add_tile_activate_cb(mainscreen_tile_num, mainscreen_activate_cb);
    gui_add_tile_hibernate_cb(mainscreen_tile_num, mainscreen_hibernate_cb);
    eventmgm_register_loop_cb(EVENTMGM_WAKEUP | EVENTMGM_SILENCE_WAKEUP | EVENTMGM_STANDBY, mainscreen_event_loop_cb, "mainscreen event loop");
    mainscreen_active = true;
}
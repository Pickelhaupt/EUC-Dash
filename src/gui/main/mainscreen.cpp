#include <Arduino.h>
#include <Ticker.h>
#include <lvgl.h>
#include "gui/gui.h"
#include "gui/setup/setup.h"
#include "gui/dashboard/dashboard.h"
#include "mainscreen.h"
#include "hardware/button.h"

uint32_t mainscreen_tile_num;
bool mainscreen_active = false;

static lv_obj_t *mainscreen_cont = NULL;
static lv_obj_t *time_label;
static lv_obj_t *date_label;

static lv_obj_t *time_cont;

static lv_style_t mainscreen_style;
static lv_style_t mainscreen_timestyle;
static lv_style_t mainscreen_datestyle;
static lv_style_t mainscreen_valuestyle;
static lv_style_t mainscreen_unitstyle;
static lv_style_t mainscreen_labelstyle;
static lv_style_t mainscreen_linestyle;
static lv_style_t mainscreen_barstyle;

void mainscreen_init_styles() {
    lv_style_copy(&mainscreen_style, gui_get_style());

    lv_style_copy(&mainscreen_timestyle, gui_get_textstyle());
    lv_style_set_text_font(&mainscreen_timestyle, LV_STATE_DEFAULT, &DIN1451_m_cond_120);
    lv_style_set_text_color(&mainscreen_timestyle, LV_STATE_DEFAULT, watch_colour);

    lv_style_copy(&mainscreen_datestyle, gui_get_textstyle());
    lv_style_set_text_font(&mainscreen_datestyle, LV_STATE_DEFAULT, &DIN1451_m_cond_36);
    lv_style_set_text_color(&mainscreen_datestyle, LV_STATE_DEFAULT, LV_COLOR_RED);

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
    lv_label_set_text(time_label, "04:22");
    lv_obj_align(time_label, NULL, LV_ALIGN_CENTER, 0, -15);
}

void mainscreen_create_date_label(void){
    date_label = lv_label_create(time_cont, NULL);
    lv_obj_add_style(date_label, LV_LABEL_PART_MAIN, &mainscreen_datestyle);
    lv_label_set_text(date_label, "Fri Apr 16 2021");
    lv_obj_align(date_label, NULL, LV_ALIGN_CENTER, 0, 52);
}

void mainscreen_update_time(time_t ctime){
    char timebuf[8];
    char datebuf[16];
    struct tm time_tm;
    localtime_r(&ctime, &time_tm);
    strftime(timebuf, sizeof(timebuf), "%H:%M", &time_tm);
    strftime(datebuf, sizeof(datebuf), "%a %d %b %Y", &time_tm);
    lv_label_set_text(time_label, timebuf);
    lv_obj_realign(time_label);
    lv_label_set_text(date_label, datebuf);
    lv_obj_realign(date_label);
}


uint32_t mainscreen_get_tile_num(void) {
    return mainscreen_tile_num;
}

void mainscreen_cont_cb(lv_obj_t * obj, lv_event_t event) {
    Serial.printf("mainscreen_cont_cb event: %d \n", event);
    /*
    if(event == LV_EVENT_KEY) {
        uint32_t key_pressed = *((uint32_t *)lv_event_get_data ());
        Serial.printf("event pressed %d \n", key_pressed);
        if (key_pressed == LV_KEY_ENTER) {
            gui_jump_to_tilenumber(setup_get_tile_num(), LV_ANIM_OFF);
        }
        if (key_pressed == LV_KEY_LEFT) {
             gui_jump_to_tilenumber(dashboard_get_tile(), LV_ANIM_ON);
        }
        if (key_pressed == LV_KEY_RIGHT) {
             gui_jump_to_tilenumber(mainscreen_get_tile_num(), LV_ANIM_ON);
        }  
    }
    */
}

void mainscreen_tile_reload(void)
{
    log_i("reloading main screen");
    lv_obj_clean(mainscreen_cont);
    mainscreen_init_styles();
    mainscreen_create_conts();
    mainscreen_create_time_label();
    mainscreen_create_date_label();
}

void mainscreen_init(){
    mainscreen_tile_num = gui_add_tile(0, 0, "mainscreen tile");
    mainscreen_cont = gui_get_tile_obj(mainscreen_tile_num);
 
    lv_obj_set_size(mainscreen_cont, lv_disp_get_hor_res( NULL ) , lv_disp_get_ver_res( NULL ));
    log_i("setting up main screen");
    mainscreen_tile_reload();
    //lv_group_add_obj(button_group, mainscreen_cont);
    //lv_obj_set_event_cb( mainscreen_cont, mainscreen_cont_cb);
    gui_add_tile_activate_cb(mainscreen_tile_num, mainscreen_activate_cb);
    gui_add_tile_hibernate_cb(mainscreen_tile_num, mainscreen_hibernate_cb);
}
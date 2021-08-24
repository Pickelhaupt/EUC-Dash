#include "setup.h"
#include "gui/gui.h"
#include <lvgl.h>
#include <Arduino.h>

uint32_t setup_time_tile_num;

lv_obj_t *setup_time_tile=NULL;
lv_obj_t *setup_time_hours=NULL;
lv_obj_t *setup_time_minutes=NULL;
lv_obj_t *setup_time_divider=NULL;
lv_obj_t *setup_time_ok=NULL;
lv_obj_t *setup_time_cancel=NULL;

lv_style_t setup_time_style;
lv_style_t setup_time_label_style;
lv_style_t setup_time_button_style;

static void enter_time_setup_event_cb( lv_obj_t * obj, lv_event_t event );

void setup_time_setup_styles(){
    lv_style_copy( &setup_time_style, gui_get_style());
    lv_style_copy( &setup_time_label_style, &setup_time_style);
    lv_style_copy( &setup_time_button_style, &setup_time_style);
}

void setup_time_create_obj(){
    setup_time_divider = lv_label_create(setup_time_tile, NULL);
    lv_obj_add_style(setup_time_divider, LV_STATE_DEFAULT, &setup_time_label_style);
    lv_label_set_text(setup_time_divider, ":");
    lv_obj_align(setup_time_divider, NULL, LV_ALIGN_CENTER, 0, 0);

    setup_time_hours = lv_label_create(setup_time_tile, NULL);
    lv_obj_add_style(setup_time_hours, LV_STATE_DEFAULT, &setup_time_label_style);
    lv_label_set_text(setup_time_hours, "00");
    lv_obj_align(setup_time_hours, setup_time_divider, LV_ALIGN_OUT_LEFT_MID, -5, 0);

    setup_time_minutes = lv_label_create(setup_time_tile, NULL);
    lv_obj_add_style(setup_time_minutes, LV_STATE_DEFAULT, &setup_time_label_style);
    lv_label_set_text(setup_time_minutes, "00");
    lv_obj_align(setup_time_minutes, setup_time_divider, LV_ALIGN_OUT_RIGHT_MID, 5, 0);

    setup_time_ok = lv_btn_create(setup_time_tile, NULL);
    setup_time_cancel = lv_btn_create(setup_time_tile, NULL);
}

void setup_time_preinit(){
    setup_register_menu_item(&time_32px, enter_time_setup_event_cb, "time settings");
    //setup_timezone_data( timesync_get_timezone_name() );
}

void setup_time_tile_setup( void ) {
    setup_time_tile_num = setup_get_ubmenu_tile_num();
    setup_time_tile = gui_get_tile_obj(setup_time_tile_num);
    lv_obj_clean(setup_time_tile);
    setup_time_setup_styles();
    setup_time_create_obj();
}

static void enter_time_setup_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       setup_time_tile_setup();
                                        gui_jump_to_tilenumber( setup_time_tile_num, LV_ANIM_OFF );
                                        break;
    }
}
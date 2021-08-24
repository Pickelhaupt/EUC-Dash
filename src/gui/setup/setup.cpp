#include "setup.h"
#include "gui/gui.h"
#include <lvgl.h>
#include <Arduino.h>
#include "hardware/button.h"

uint32_t setup_tile_num;
uint32_t setup_submenu_tile_num;
int setup_cont_height = MENU_CONT_HEIGHT;
setup_item_t *menu_item[MAX_MENU_ITEMS];

lv_obj_t *setup_tile=NULL;
lv_obj_t *setup_submenu_tile=NULL;
lv_obj_t *setup_page=NULL;

static lv_style_t setup_style;
static lv_style_t setup_textstyle;
static lv_style_t setup_linestyle;
static lv_style_t setup_pagestyle;
static lv_style_t setup_edgestyle;

LV_IMG_DECLARE(right_32px);
LV_IMG_DECLARE(left_32px);
LV_IMG_DECLARE(setup_32px);

LV_FONT_DECLARE(DIN1451_m_cond_28);
LV_FONT_DECLARE(DIN1451_m_cond_24);

void setup_init_styles() {
    lv_style_copy(&setup_style, gui_get_style());
    
    lv_style_copy(&setup_pagestyle, gui_get_pagestyle());

    lv_style_copy(&setup_edgestyle, gui_get_edgestyle());
    
    lv_style_copy(&setup_textstyle, gui_get_textstyle());
    lv_style_set_text_font( &setup_textstyle, LV_STATE_DEFAULT, &DIN1451_m_cond_28);
    
    lv_style_copy(&setup_linestyle, gui_get_linestyle());
}

void setup_add_tile(void){
    setup_tile_num = gui_add_app_tile(1, 1, "setup");
    setup_tile = gui_get_tile_obj( setup_tile_num );
}

void setup_add_submenu_tile(void){
    setup_submenu_tile_num = gui_add_app_tile(1, 2, "submenu");
    setup_submenu_tile = gui_get_tile_obj( setup_submenu_tile_num );
}

void setup_create_heading(){
    lv_obj_t *setup_heading = lv_label_create( setup_tile, NULL);
    lv_obj_add_style( setup_heading, LV_OBJ_PART_MAIN, &setup_textstyle  );
    lv_label_set_text( setup_heading, "setup");
    lv_obj_align( setup_heading, setup_tile, LV_ALIGN_IN_TOP_MID, 0, 15 );
}

void setup_create_page(){
    setup_page = lv_page_create( setup_tile, NULL);
    lv_obj_set_size(setup_page, lv_disp_get_hor_res( NULL ), 195);
    lv_page_set_edge_flash(setup_page, true);
    lv_obj_add_style(setup_page, LV_OBJ_PART_MAIN, &setup_pagestyle );
    lv_obj_add_style(setup_page, LV_PAGE_PART_EDGE_FLASH, &setup_edgestyle );
    lv_obj_add_style(setup_page, LV_PAGE_PART_SCROLLBAR, &setup_edgestyle );
    lv_obj_align( setup_page, setup_tile, LV_ALIGN_IN_TOP_MID, 0, 45 );
}

uint32_t setup_get_tile_num(){
    return setup_tile_num;
}
uint32_t setup_get_ubmenu_tile_num(){
    return setup_submenu_tile_num;
}

uint32_t setup_register_menu_item(const lv_img_dsc_t *icon, lv_event_cb_t event_cb, const char *item_label) {
    
    static int item_entries = 0;
    item_entries++;

    log_i("add item");
    setup_item_t menu_item[ item_entries - 1 ];
    log_i("create menu cont");
    menu_item[ item_entries - 1 ].cont = lv_cont_create( setup_page, NULL);
    lv_page_glue_obj(menu_item[ item_entries - 1 ].cont, true);
    lv_group_add_obj(button_group, menu_item[ item_entries - 1 ].cont);
    lv_obj_set_size(menu_item[ item_entries - 1 ].cont, lv_disp_get_hor_res( NULL ) - 10, setup_cont_height);
    lv_obj_add_style( menu_item[ item_entries - 1 ].cont, LV_OBJ_PART_MAIN, &setup_style  );
    log_i("align menu cont");
    lv_obj_align( menu_item[ item_entries - 1 ].cont, NULL, LV_ALIGN_IN_TOP_MID, 0, setup_cont_height * (item_entries - 1) );
    log_i("set event cb");
    lv_obj_set_event_cb( menu_item[ item_entries - 1 ].cont, event_cb );

    menu_item[ item_entries - 1 ].icon_cont = lv_cont_create(menu_item[ item_entries - 1 ].cont, NULL);
    lv_obj_set_size(menu_item[ item_entries - 1 ].icon_cont, 32, 32);
    lv_obj_add_style( menu_item[ item_entries - 1 ].icon_cont, LV_OBJ_PART_MAIN, &setup_style  );
    lv_obj_align( menu_item[ item_entries - 1 ].icon_cont, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0 );

    menu_item[ item_entries - 1 ].icon = lv_img_create(menu_item[ item_entries - 1 ].icon_cont, NULL);
    lv_img_set_src(menu_item[ item_entries - 1 ].icon, icon);
    lv_obj_align( menu_item[ item_entries - 1 ].icon, NULL, LV_ALIGN_CENTER, 0, 0 );
    
    menu_item[ item_entries - 1 ].arrow = lv_img_create(menu_item[ item_entries - 1 ].cont, NULL);
    lv_img_set_src(menu_item[ item_entries - 1 ].arrow, &right_32px);
    lv_obj_align( menu_item[ item_entries - 1 ].arrow, NULL, LV_ALIGN_IN_RIGHT_MID, 0, 0 );
    
    log_i("create menu label");
    menu_item[ item_entries - 1 ].label = lv_label_create( menu_item[ item_entries - 1 ].cont, NULL);
    lv_obj_add_style( menu_item[ item_entries - 1 ].label, LV_OBJ_PART_MAIN, &setup_textstyle );
    lv_label_set_text( menu_item[ item_entries - 1 ].label, item_label);
    lv_obj_align( menu_item[ item_entries - 1 ].label, NULL, LV_ALIGN_IN_LEFT_MID, 40, 0 );
    lv_obj_add_protect( menu_item[ item_entries - 1 ].label, LV_PROTECT_CLICK_FOCUS);
    return item_entries - 1;
}

void enter_setup_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       gui_jump_to_tilenumber( setup_tile_num, LV_ANIM_OFF );
                                        break;
    }
}

static void exit_setup_event_cb( lv_obj_t * obj, lv_event_t event ) {
    switch( event ) {
        case( LV_EVENT_CLICKED ):       gui_jump_to_maintile(LV_ANIM_OFF);
                                        break;
    }
}

void setup_init(){
    setup_init_styles();
    setup_add_tile();
    setup_create_heading();
    setup_create_page();
    setup_register_menu_item(&left_32px, exit_setup_event_cb, "exit");
    setup_time_preinit();

    //submenu1_setup_init();
    //submenu2_setup_init();
}
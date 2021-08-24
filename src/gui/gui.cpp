#include <Arduino.h>
#include <Ticker.h>
#include <lvgl.h>
#include "gui.h"
#include "main/mainscreen.h"
#include "dashboard/dashboard.h"
#include "hardware/button.h"
#include "setup/setup.h"

static lv_tile_t *tile = NULL;
static lv_point_t *tile_pos_table = NULL;
static uint32_t current_tile = 0;
static uint32_t tile_entrys = 0;
uint32_t main_tile_nr = 0;
static uint32_t app_tile_pos = GUI_APP_TILE_X_START;

//declare objects
static lv_obj_t *gui_tileview;
static lv_obj_t *bg_bar;

//declare styles 
lv_style_t gui_style; 
lv_style_t gui_liststyle;
lv_style_t gui_buttonstyle;
lv_style_t gui_tilestyle;
lv_style_t gui_textstyle;
lv_style_t gui_linestyle;
lv_style_t gui_pagestyle;
lv_style_t gui_edgestyle;

void gui_event_cb(lv_obj_t * obj, lv_event_t event);

void gui_define_styles(void){
    lv_style_init(&gui_style);
    lv_style_set_bg_color(&gui_style, LV_STATE_DEFAULT, gui_color_black);
    lv_style_set_bg_opa(&gui_style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_radius(&gui_style, LV_STATE_DEFAULT, 0);
    lv_style_set_border_width( &gui_style, LV_OBJ_PART_MAIN, 0 );
    
    lv_style_copy(&gui_buttonstyle, &gui_style);
    lv_style_set_outline_color(&gui_buttonstyle, LV_STATE_DEFAULT, default_color);
    lv_style_set_bg_color(&gui_buttonstyle, LV_STATE_PRESSED, default_color);
    lv_style_set_bg_color(&gui_buttonstyle, LV_STATE_CHECKED, default_color);
    lv_style_set_bg_color(&gui_buttonstyle, LV_STATE_DEFAULT, gui_color_black);
    lv_style_set_text_color(&gui_buttonstyle, LV_STATE_CHECKED, gui_color_black);
    lv_style_set_text_color(&gui_buttonstyle, LV_STATE_DEFAULT, default_color);

    lv_style_copy(&gui_linestyle, &gui_style);
    lv_style_set_line_color(&gui_linestyle, LV_STATE_DEFAULT, default_color);
    lv_style_set_line_rounded(&gui_linestyle, LV_STATE_DEFAULT, false);
    lv_style_set_line_width(&gui_linestyle, LV_STATE_DEFAULT, 4);

    lv_style_copy(&gui_textstyle, &gui_style);
    lv_style_set_text_color(&gui_textstyle, LV_STATE_DEFAULT, default_color);
    lv_style_set_text_font(&gui_textstyle, LV_STATE_DEFAULT, &DIN1451_m_cond_72);

    lv_style_copy(&gui_pagestyle, &gui_style);
    lv_style_set_pad_all(&gui_pagestyle, LV_STATE_DEFAULT, 0);

    lv_style_copy(&gui_edgestyle, &gui_style);
    lv_style_set_bg_color(&gui_edgestyle, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_style_set_bg_opa(&gui_edgestyle, LV_STATE_DEFAULT, 30);

}

lv_style_t *gui_get_style(void) {
    return( &gui_style );
}

lv_style_t *gui_get_linestyle(void) {
    return( &gui_linestyle );
}

lv_style_t *gui_get_textstyle(void) {
    return( &gui_textstyle );
}

lv_style_t *gui_get_buttonstyle(void) {
    return( &gui_buttonstyle );
}

lv_style_t *gui_get_pagestyle(void) {
    return( &gui_buttonstyle );
}

lv_style_t *gui_get_edgestyle(void) {
    return( &gui_buttonstyle );
}

void gui_setup_tileview() {
    gui_tileview = lv_tileview_create(lv_scr_act(), NULL);
    lv_tileview_set_edge_flash( gui_tileview, false);
    lv_obj_add_style( gui_tileview, LV_OBJ_PART_MAIN, &gui_style );
    lv_page_set_scrlbar_mode( gui_tileview, LV_SCRLBAR_MODE_OFF);
    lv_obj_set_event_cb( gui_tileview, gui_event_cb );
    //lv_tileview_add_element( gui_tileview, gui_tileview );
    lv_group_add_obj(button_group, gui_tileview);
}

void gui_set_bg(void) {
    bg_bar = lv_bar_create(lv_scr_act(), NULL);
    lv_obj_set_size(bg_bar, 320, 240);
    lv_obj_reset_style_list(bg_bar, LV_OBJ_PART_MAIN);
    lv_obj_add_style(bg_bar, LV_BAR_PART_BG, &gui_style);
}

uint32_t gui_add_tile( uint16_t x, uint16_t y, const char *id ) {
    
    tile_entrys++;
    log_i("gui setup tile %d", tile_entrys);

    if ( tile_pos_table == NULL ) {
        tile_pos_table = ( lv_point_t * )malloc( sizeof( lv_point_t ) * tile_entrys );
        if ( tile_pos_table == NULL ) {
            log_e("tile_pos_table malloc faild");
            while(true);
        }
        tile = ( lv_tile_t * )malloc( sizeof( lv_tile_t ) * tile_entrys );
        if ( tile == NULL ) {
            log_e("tile malloc faild");
            while(true);
        }
    }
    else {
        lv_point_t *new_tile_pos_table;
        lv_tile_t *new_tile;

        new_tile_pos_table = ( lv_point_t * )realloc( tile_pos_table, sizeof( lv_point_t ) * tile_entrys );
        if ( new_tile_pos_table == NULL ) {
            log_e("tile_pos_table realloc faild");
            while(true);
        }
        tile_pos_table = new_tile_pos_table;
        
        new_tile = ( lv_tile_t * )realloc( tile, sizeof( lv_tile_t ) * tile_entrys );
        if ( new_tile == NULL ) {
            log_e("tile realloc faild");
            while(true);
        }
        tile = new_tile;
    }
    log_e("setting up tile pos table");
    tile_pos_table[ tile_entrys - 1 ].x = x;
    tile_pos_table[ tile_entrys - 1 ].y = y;
    log_e("setting up tile obj");
    lv_obj_t *my_tile = lv_cont_create( gui_tileview, NULL);  
    tile[ tile_entrys - 1 ].tile = my_tile;
    tile[ tile_entrys - 1 ].activate_cb = NULL;
    tile[ tile_entrys - 1 ].hibernate_cb = NULL;
    tile[ tile_entrys - 1 ].x = x;
    tile[ tile_entrys - 1 ].y = y;
    tile[ tile_entrys - 1 ].id = id;
    log_e("setting up tile size");
    lv_obj_set_size( tile[ tile_entrys - 1 ].tile, lv_disp_get_hor_res( NULL ), LV_VER_RES);
    //lv_obj_reset_style_list( tile[ tile_entrys - 1 ].tile, LV_OBJ_PART_MAIN );
    log_e("adding styles");
    lv_obj_add_style( tile[ tile_entrys - 1 ].tile, LV_OBJ_PART_MAIN, &gui_style );
    log_e("setting tile pos");
    lv_obj_set_pos( tile[ tile_entrys - 1 ].tile, tile_pos_table[ tile_entrys - 1 ].x * lv_disp_get_hor_res( NULL ) , tile_pos_table[ tile_entrys - 1 ].y * LV_VER_RES );
    log_e("Adding elment");
    lv_tileview_add_element( gui_tileview, tile[ tile_entrys - 1 ].tile );
    log_e("setting valid pos");
    lv_tileview_set_valid_positions( gui_tileview, tile_pos_table, tile_entrys );
    log_i("add tile: x=%d, y=%d, id=%s", tile_pos_table[ tile_entrys - 1 ].x, tile_pos_table[ tile_entrys - 1 ].y, tile[ tile_entrys - 1 ].id );
    return( tile_entrys - 1 );
}

uint32_t gui_get_active_tile( void ){
    uint32_t active_tile = *((uint32_t *)lv_event_get_data ());
    return active_tile;
}

void gui_event_cb(lv_obj_t * obj, lv_event_t event) {
    Serial.printf("gui_event_cb event: %d \n", event);
    //int16_t encdiff = *((int16_t *)lv_event_get_data ());
    //Serial.printf("encdiff: %d \n", encdiff);
    if(event == LV_EVENT_KEY) {
        uint32_t key_pressed = *((uint32_t *)lv_event_get_data ());
        Serial.printf("event pressed %d \n", key_pressed);
        if (key_pressed == LV_KEY_ENTER) {
            Serial.println("enter key pressed---");
            if (current_tile != setup_get_tile_num()) gui_jump_to_tilenumber(setup_get_tile_num(), LV_ANIM_OFF);
        }
        if (key_pressed == LV_KEY_LEFT) {
            Serial.println("left key pressed---");
            if (current_tile == mainscreen_get_tile_num()) gui_jump_to_tilenumber(dashboard_get_tile(), LV_ANIM_ON);
            else if (current_tile == dashboard_get_tile()) gui_jump_to_tilenumber(mainscreen_get_tile_num(), LV_ANIM_ON);
            else if (current_tile == setup_get_tile_num()) gui_jump_to_tilenumber(mainscreen_get_tile_num(), LV_ANIM_OFF);
        }
        if (key_pressed == LV_KEY_RIGHT) {
            Serial.println("right key pressed---");
            if (current_tile == mainscreen_get_tile_num()) gui_jump_to_tilenumber(dashboard_get_tile(), LV_ANIM_ON);
            else if (current_tile == dashboard_get_tile()) gui_jump_to_tilenumber(mainscreen_get_tile_num(), LV_ANIM_ON);
            else if (current_tile == setup_get_tile_num()) gui_jump_to_tilenumber(dashboard_get_tile(), LV_ANIM_OFF);
        }        
    }

    if(event == LV_EVENT_VALUE_CHANGED)
    { 
        Serial.printf("event value changed %d \n", event);
        uint32_t tile_number = *((uint32_t *)lv_event_get_data ());
        // call hibernate callback for the old tile if exist
        if ( tile[ current_tile ].hibernate_cb != NULL ) {
            log_i("call hibernate cb for tile: %d", current_tile );
            tile[ current_tile ].hibernate_cb();
        }
        // call activate callback for the new tile if exist
        if ( tile[ tile_number ].activate_cb != NULL ) { 
            log_i("call activate cb for tile: %d", tile_number );
            tile[ tile_number ].activate_cb();
        }
        current_tile = tile_number;
        Serial.printf("current_tile = %d \n", current_tile);
    }
}

bool gui_add_tile_hibernate_cb( uint32_t tile_number, GUI_CALLBACK_FUNC hibernate_cb ) {
    if ( tile_number < tile_entrys ) {
        tile[ tile_number ].hibernate_cb = hibernate_cb;
        return( true );
    }
    else {
        log_e("tile number %d do not exist", tile_number );
        return( false );
    }
}

bool gui_add_tile_activate_cb( uint32_t tile_number, GUI_CALLBACK_FUNC activate_cb ) {
    if ( tile_number < tile_entrys ) {
        tile[ tile_number ].activate_cb = activate_cb;
        return( true );
    }
    else {
        log_e("tile number %d do not exist", tile_number );
        return( false );
    }
}

uint32_t gui_add_app_tile( uint16_t x, uint16_t y, const char *id ) {
    uint32_t retval = -1;

    for ( int hor = 0 ; hor < x ; hor++ ) {
        for ( int ver = 0 ; ver < y ; ver++ ) {
            if ( retval == -1 ) {
                retval = gui_add_tile( hor + app_tile_pos, ver + GUI_APP_TILE_Y_START, id );
            }
            else {
                gui_add_tile( hor + app_tile_pos, ver + GUI_APP_TILE_Y_START, id );
            }
        }
    }
    app_tile_pos = app_tile_pos + x + 1;
    return( retval );
}

void gui_clear_tile(uint32_t tile_num) {
    lv_obj_clean( tile[ tile_num ].tile );
}

lv_obj_t *gui_get_tile_obj( uint32_t tile_number ) {
    if ( tile_number < tile_entrys ) {
        return( tile[ tile_number ].tile );
    }
    else {
        log_e( "tile number %d do not exist", tile_number );
    }
    return( NULL );
}

void gui_jump_to_maintile( lv_anim_enable_t anim ) {
    if ( tile_entrys != 0 ) {
        gui_jump_to_tilenumber( main_tile_nr, anim );
    }
    else {
        log_e( "main tile do not exist" );
    }
}

void gui_jump_to_tilenumber( uint32_t tile_number, lv_anim_enable_t anim ) {
    if ( tile_number < tile_entrys ) {
        log_i("jump to tile %d from tile %d", tile_number, current_tile );
        lv_tileview_set_tile_act( gui_tileview, tile_pos_table[ tile_number ].x, tile_pos_table[ tile_number ].y, anim );
        // call hibernate callback for the current tile if exist
        /*
        if ( tile[ current_tile ].hibernate_cb != NULL ) {
            log_i("call hibernate cb for tile: %d", current_tile );
            tile[ current_tile ].hibernate_cb();
        }
        // call activate callback for the new tile if exist
        if ( tile[ tile_number ].activate_cb != NULL ) { 
            log_i("call activate cb for tile: %d", tile_number );
            tile[ tile_number ].activate_cb();
        }
        */
        //current_tile = tile_number;
    }
    else {
        log_e( "tile number %d do not exist", tile_number );
    }
}

lv_obj_t * gui_obj_create(lv_obj_t *parent)
{
    lv_obj_t * child = lv_obj_create( parent, NULL );
    lv_tileview_add_element( gui_tileview, child );

    return child;
}

void gui_add_slide_element(lv_obj_t *element)
{
    lv_tileview_add_element( gui_tileview, element );
}

void gui_init(void) {
    lv_disp_set_bg_color(NULL, gui_color_black);
    gui_define_styles();
    gui_setup_tileview();
    //gui_set_bg();
}
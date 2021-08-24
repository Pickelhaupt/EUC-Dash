#ifndef _GUI_H_
    #define _GUI_H
    #define LV_LVGL_H_INCLUDE_SIMPLE

    #include "lvgl.h"

    #define GUI_APP_TILE_X_START     0
    #define GUI_APP_TILE_Y_START     4

    //define clolors
    static lv_color_t gui_color_green = lv_color_make(0x00, 0xfa, 0x0f);
    static lv_color_t gui_color_pajero_green = lv_color_make(0x3f, 0xff, 0x5f);
    static lv_color_t gui_color_dark_pajero_green = lv_color_make(0x1f, 0x77, 0x3f);
    static lv_color_t gui_color_white = lv_color_make(0xff, 0xff, 0xff);
    static lv_color_t gui_color_black = lv_color_make(0x00, 0x00, 0x00);

    static lv_color_t default_color = gui_color_pajero_green;

    LV_FONT_DECLARE(DIN1451_m_cond_24);
    LV_FONT_DECLARE(DIN1451_m_cond_28);
    LV_FONT_DECLARE(DIN1451_m_cond_36);
    LV_FONT_DECLARE(DIN1451_m_cond_44);
    LV_FONT_DECLARE(DIN1451_m_cond_66);
    LV_FONT_DECLARE(DIN1451_m_cond_72);
    LV_FONT_DECLARE(DIN1451_m_cond_80);
    LV_FONT_DECLARE(DIN1451_m_cond_85);
    LV_FONT_DECLARE(DIN1451_m_cond_90);
    LV_FONT_DECLARE(DIN1451_m_cond_100);
    LV_FONT_DECLARE(DIN1451_m_cond_120);
    LV_FONT_DECLARE(DIN1451_m_cond_180);

    typedef void ( * GUI_CALLBACK_FUNC ) ( void );

    typedef struct {
        lv_obj_t *tile;
        GUI_CALLBACK_FUNC activate_cb;
        GUI_CALLBACK_FUNC hibernate_cb;
        uint16_t x;
        uint16_t y;
        const char *id;
    } lv_tile_t;

    void gui_init(void);

    lv_style_t *gui_get_style(void);
    
    lv_style_t *gui_get_linestyle(void);

    lv_style_t *gui_get_textstyle(void);

    lv_style_t *gui_get_buttonstyle(void);

    lv_style_t *gui_get_pagestyle(void);

    lv_style_t *gui_get_edgestyle(void);

     /**
     * @brief jump to the given tile
     * 
     * @param   tile    tile number
     * @param   anim    LV_ANIM_ON or LV_ANIM_OFF for animated switch
     */
    void gui_jump_to_tilenumber( uint32_t tile_number, lv_anim_enable_t anim );
    /**
     * @brief jump to the last active tile
     * 
     * @param   anim    LV_ANIM_ON or LV_ANIM_OFF for animated switch
     */
    void gui_jump_to_maintile( lv_anim_enable_t anim );
    /**
     * @brief add a tile at a specific position
     * 
     * @param   x   x position
     * @param   y   y position
     * 
     * @return  tile number
     */
    uint32_t gui_add_tile( uint16_t x, uint16_t y, const char *id );
    /**
     * @brief get the lv_obj_t for a specific tile number
     *
     * @param   tile_number   tile number
     * 
     * @return  lv_obj_t
     */
    lv_obj_t * gui_get_tile_obj( uint32_t tile_number );
    /**
     * @brief register an hibernate callback function when leave the tile
     * 
     * @param   tile_number     tile number
     * @param   hibernate_cb    pointer to the hibernate callback function
     * 
     * @return  true or false, true means registration was success
     */
    
    bool gui_add_tile_hibernate_cb( uint32_t tile_number, GUI_CALLBACK_FUNC hibernate_cb );
    /**
     * @brief register an activate callback function when enter the tile
     * 
     * @param   tile_number     tile number
     * @param   activate_cb     pointer to the activate callback function
     * 
     * @return  true or false, true means registration was success
     */
    bool gui_add_tile_activate_cb( uint32_t tile_number, GUI_CALLBACK_FUNC activate_cb );
    /**
     * @brief get active tile number
     * 
     * @return  active tile number
     */
    uint32_t gui_get_active_tile( void );
    /**
     * @brief add a independent sub tile formation
     * 
     *  predefined tiles
     * 
     *  +---+   1 = main tile
     *  | 1 |   2 = offroad tile
     *  +---+  
     *  | 2 |    
     *  +---+
     * 
     *  sub tiles
     * 
     *  +---+---+    +---+   +---+---+
     *  | n |n+1|    | n |   | n |n+1|
     *  +---+---+    +---+   +---+---+
     *  |n+2|n+3|    |n+1|
     *  +---+---+    +---+
     * 
     * @param   x   x size in tiles
     * @param   y   y size in tiles
     * 
     * @return  tile number, if get more than 1 tile it is the first tile number
     */
    uint32_t gui_add_app_tile( uint16_t x, uint16_t y, const char *id );

    void gui_add_slide_element(lv_obj_t *element);
#endif
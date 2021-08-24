#ifndef _SETUP_H
    #define _SETUP_H

    #include <lvgl.h>

    #define MAX_MENU_ITEMS      12
    #define MENU_CONT_HEIGHT    50

    LV_IMG_DECLARE(right_32px);
    LV_IMG_DECLARE(left_32px);
    LV_IMG_DECLARE(setup_32px);
    LV_IMG_DECLARE(time_32px);
    

    /**
     * @brief structure to hold menu item data
     * 
     * @param   cont (lv_obj_t) the lvgl container object for the menu item
     * @param   label (lv_obj_t) the lvgl label object for the menu item
     * @param   icon
     * @param   arrow
     */
    typedef struct {
        lv_obj_t *cont;
        lv_obj_t *label;
        lv_obj_t *icon_cont;
        lv_obj_t *icon;
        lv_obj_t *arrow;
    }setup_item_t;

    /**
     * @brief set up the settings tile
     */
    void setup_init( void );
    /**
     * @brief register a menu item to the eucdash settings menu
     * 
     * @param   icon the icon representing the menu item, should be 32x32 px
     * @param   event_cb the callback function to be called when the item is clicked
     * @param   item_label the label text to be shown on the menu item, 2 lines of approx. 16 chars
     * @return  menu entry number
     */
    uint32_t setup_register_menu_item(const lv_img_dsc_t *icon, lv_event_cb_t event_cb, const char *item_label);

    uint32_t setup_get_tile_num();

    uint32_t setup_get_ubmenu_tile_num();

    void setup_time_preinit();

    void enter_setup_event_cb( lv_obj_t * obj, lv_event_t event );
#endif
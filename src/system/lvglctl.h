#ifndef _LVGLCTL_H

    #define _LVGLCTL_H

    #include "config.h"
    
    #ifdef LV_TILEVIEW_DEF_ANIM_TIME
        #undef LV_TILEVIEW_DEF_ANIM_TIME
    #endif
    #define LV_TILEVIEW_DEF_ANIM_TIME   150

    /**
     * @brief GUI setup
     */
    void lvglctl_init( void );
    /**
     * @brief force a complete redraw cycle on next gui cycle
     * 
     * @param force  true for redraw
     */
    void lvglctl_force_redraw( bool force );

#endif // _STATUSBAR_H
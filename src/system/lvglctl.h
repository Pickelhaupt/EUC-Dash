#ifndef _LVGLCTL_H

    #define _LVGLCTL_H

    #include "config.h"
    
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
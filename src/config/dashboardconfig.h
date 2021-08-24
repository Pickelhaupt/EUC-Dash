#ifndef _DASHBOARDCONFIG_H
    #define _DASHBOARDCONFIG_H

    #include "config.h"
    #include "basejsonconfig.h"

    #define DASHBOARDCONFIG_JSON_FILE    "/dashboardconfig.json" /** @brief defines json config file name */

    /**
     * @brief wifictl config structure
     */
    class dashboardconfig_t : public BaseJsonConfig {
        public:
        dashboardconfig_t();
        bool lights = false;
        bool bars = true;
        bool simple = false;
        bool medium = false;
        bool full = true;
        bool timedisplay = false;
        bool impdist = false;
        bool imptemp = false;

        protected:
        ////////////// Available for overloading: //////////////
        virtual bool onLoad(JsonDocument& document);
        virtual bool onSave(JsonDocument& document);
        virtual bool onDefault( void );
        virtual size_t getJsonBufferSize() { return 2000; }
    };

#endif // _DASHBOARDCONFIG_H
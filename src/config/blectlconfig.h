/****************************************************************************
 *   Aug 11 17:13:51 2020
 *   Copyright  2020  Dirk Brosswick
 *   Email: dirk.brosswick@googlemail.com
 ****************************************************************************/
 
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#ifndef _BLECTL_CONFIG_H
    #define _BLECTL_CONFIG_H

    #include "basejsonconfig.h"

    #define BLECTL_JSON_COFIG_FILE         "/blectl.json"   /** @brief defines json config file name */
    #define BLECTL_STORED_WHEEL_FILE         "/stored_wheels.json"   /** @brief defines json config file name */

    /**
     * @brief blectl config structure
     */
    class blectlconfig_t : public BaseJsonConfig {
        public:
        blectlconfig_t();
        bool autoon = true;                     /** @brief auto on/off */
        bool autoconnect = true;                /** @brief advertising on/off */
        bool enable_on_standby = false;         /** @brief enable on standby on/off */
        bool disable_only_disconnected = false; /** @brief disable only when disconnected on/off */
        bool show_notification = true;          /** @brief enable show notifications */
        int32_t txpower = 1;                    /** @brief tx power, valide values are from 0 to 4 */

        protected:
        ////////////// Available for overloading: //////////////
        virtual bool onLoad(JsonDocument& document);
        virtual bool onSave(JsonDocument& document);
        virtual bool onDefault( void );
        virtual size_t getJsonBufferSize() { return 2000; }
    } ;

    typedef struct {
        char address[18]="00:00:00:00:00:00";
        byte type = 5;
        char name[6]="N/A";
    } wheel_t;

    class stored_wheels_t : public BaseJsonConfig {
        public:
        stored_wheels_t();
        wheel_t* wheel = NULL;

        protected:
        ////////////// Available for overloading: //////////////
        virtual bool onLoad(JsonDocument& document);
        virtual bool onSave(JsonDocument& document);
        virtual bool onDefault( void );
        virtual size_t getJsonBufferSize() { return 2000; }
    } ;

#endif // _BLECTL_CONFIG_H
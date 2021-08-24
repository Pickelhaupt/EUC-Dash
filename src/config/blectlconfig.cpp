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
#include "blectlconfig.h"
#include "system/alloc.h"
#include "system/blectl.h"


blectlconfig_t::blectlconfig_t() : BaseJsonConfig(BLECTL_JSON_COFIG_FILE) {
}

bool blectlconfig_t::onSave(JsonDocument& doc) {
    doc["autoon"] = autoon;
    doc["autoconnect"] = autoconnect;
    doc["enable_on_standby"] = enable_on_standby;
    doc["disable_only_disconnected"] = disable_only_disconnected;
    doc["tx_power"] = txpower;
    doc["show_notification"] = show_notification;

    return true;
}

bool blectlconfig_t::onLoad(JsonDocument& doc) {
    autoon = doc["autoon"] | true;
    autoconnect = doc["autoconnect"] | true;
    enable_on_standby = doc["enable_on_standby"] | false;
    disable_only_disconnected = doc["disable_only_disconnected"] | false;
    txpower = doc["tx_power"] | 1;
    show_notification = doc["show_notification"] | true;
  
    return true;
}

bool blectlconfig_t::onDefault( void ) {
    return true;
}

stored_wheels_t::stored_wheels_t() : BaseJsonConfig(BLECTL_STORED_WHEEL_FILE) {
}

bool stored_wheels_t::onSave(JsonDocument& doc) {
    for ( int i = 0 ; i < MAX_STORED_WHEELS ; i++){
        doc["wheel"][i]["address"] = wheel[i].address;
        doc["wheel"][i]["type"] = wheel[i].type;
        doc["wheel"][i]["name"] = wheel[i].name;
    }
    return true;
}

bool stored_wheels_t::onLoad(JsonDocument& doc) {
    if (wheel == NULL) {
        wheel = ( wheel_t*)CALLOC( sizeof(wheel_t) * MAX_STORED_WHEELS, 1);
        if (!wheel) {
            log_e("no wheel list");
            while(true);
        }
    }

    for ( int i = 0 ; i < MAX_STORED_WHEELS ; i++){
        
        wheel[i].type = doc["type"][i] | 5;
        if (doc ["wheel"][i]["address"] && doc["wheel"][i]["name"]) {
            strlcpy( wheel[i].address, doc["wheel"][i]["address"], sizeof(wheel[i].address));
            strlcpy( wheel[i].name, doc["wheel"][i]["name"], sizeof(wheel[i].name));
        }
    }
    return true;
}

bool stored_wheels_t::onDefault(void) {
    return true;
}
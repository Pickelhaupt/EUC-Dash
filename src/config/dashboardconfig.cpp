/****************************************************************************
 *   2021 Jesper Ortlund
 *   Derived from My-TTGO-Watch -- 2020 Dirk Brosswick
 ****************************************************************************
 *
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

#include "dashboardconfig.h"
#include "system/alloc.h"

dashboardconfig_t::dashboardconfig_t() : BaseJsonConfig(DASHBOARDCONFIG_JSON_FILE){
}

bool dashboardconfig_t::onSave(JsonDocument& doc) {
    doc["lights"] = lights;
    doc["bars"] = bars;
    doc["simple"] = simple;
    doc["medium"] = medium;
    doc["full"] = full;
    doc["timedisplay"] = timedisplay;
    doc["impdist"] = impdist;
    doc["imptemp"] = imptemp;
    return true;
}

bool dashboardconfig_t::onLoad(JsonDocument& doc) {
    lights = doc["lights"] | false;
    bars = doc["bars"] | true;
    simple = doc["simple"] | false;
    medium = doc["medium"] | false;
    full = doc["full"] | true;
    timedisplay = doc["timedisplay"] | false;
    impdist = doc["impdist"] | false;
    imptemp = doc["imptemp"] | false;
    return true;
}

bool dashboardconfig_t::onDefault( void ) {
    return true;
}

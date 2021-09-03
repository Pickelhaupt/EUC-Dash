/****************************************************************************
 * 2020 Jesper Ortlund
 ****************************************************************************/
 
/****************************************************************************
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
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
 *****************************************************************************/

#ifndef _WHEELCTL_H
    #define _WHEELCTL_H

    #include "config.h"
    #include "callback.h"
    #include "config/wheelctlconfig.h"
    
    // Below this speed no distance or ride time is recorded
    #define MIN_RIDE_SPEED  1
    #define WHEELCTL_JSON_CONFIG_FILE    "/wheelctl.json" /** @brief defines json config file name */
    #define CURRENT_TRIP_JSON_FILE    "/c-tripsave.json" /** @brief defines json config file name */
    #define LAST_TRIP_JSON_FILE    "/l-tripsave.json" /** @brief defines json config file name */
    #define TOTAL_TRIP_JSON_FILE    "/t-tripsave.json" /** @brief defines json config file name */

    // POWER_CORRECT_CONST is used to tune the power consumption and economy values I have not 
    // done enough tests to come up with an accurate value yet, it might also differ between wheel models
    #define POWER_CORRECT_CONST  1.3

    /**
     * @brief persistent tripdata structure
     */
    typedef struct {
        long timestamp = 0;
        float trip = 0.0;
        float ride_time = 0;
        float avg_speed = 0;
        float max_speed = 0;
        float max_current = 0;
        float max_regen_current = 0;
        float max_power = 0;
        float min_battery = 100;
        float max_battery = 0;
        float max_temperature = 0;
        float consumed_energy = 0;
        float trip_economy = 0;
    } trip_data_t;

    /**
     * @brief wheel config structure
     */
    typedef struct {
        bool enable=true;
    } wheelctl_config_t;

    enum {  
        WHEELCTL_CONFIG_LED,            //toggle leds when toggling light
        WHEELCTL_CONFIG_HORN,           //long press on dash activates horn if speed > 3kmh
        WHEELCTL_CONFIG_HAPTIC,         //Enable haptic feedback for alerts
        WHEELCTL_CONFIG_LIGHTS_OFF,     //turn off lights when connecting to wheel
        WHEELCTL_CONFIG_NUM     //number of wheel configuration parameters
    };

    /**
     * @brief wheel constants structure
     */
    typedef struct {
        byte value;
    } wheelctl_constants_t;

    enum { 
        WHEELCTL_CONST_MAXCURRENT,  //Maximum current draw for wheel model -required
        WHEELCTL_CONST_CRITTEMP,    //Critical internal temperature -required, might be made optional
        WHEELCTL_CONST_WARNTEMP,    //internal temperature to trigger warning -required, might e made optional
        WHEELCTL_CONST_BATTVOLT,    //Voltage of the battery pack for the wheel model -required
        WHEELCTL_CONST_BATTWARN,    //Percentage of battery remaining when warning should be triggered for the specific wheel model -required
        WHEELCTL_CONST_BATTCRIT,     
        WHEELCTL_CONST_BATT_IR,     //battery pack internal resistance
        WHEELCTL_CONST_BATT_P,     //number of battery cells in parallel
        WHEELCTL_CONST_BATT_S,     //number of battery cells in parallel
        WHEELCTL_CONST_NUM          //number of wheel constants
    };

    /**
     * @brief battery cell data structure
     */
    typedef struct {
        byte volt; //volt * 10
        byte capacity; //Ah * 10
        byte resistance; //mOhm
    } wheelctl_celldata_t;

    typedef struct {
        String value;
    } wheelctl_info_t;

    enum { 
        WHEELCTL_INFO_SERIAL,       //Serial Numer
        WHEELCTL_INFO_MANUFACTURER, //Wheel manufacturer value should be KS, GW, IM or NB -- make sure this is set when implementing a new wheel model
        WHEELCTL_INFO_MODEL,        //Wheel model -- make sure the wheel ctl constants are set up for the specific model 
        WHEELCTL_INFO_VERSION,      //in case there are multiple versions for a specific model
        WHEELCTL_INFO_BATTCAP,
        WHEELCTL_INFO_WHEELCOLOR,
        WHEELCTL_INFO_MANUFDATE,
        WHEELCTL_INFO_BLESUUID,       
        WHEELCTL_INFO_BLESDUUID,
        WHEELCTL_INFO_BLENAME,
        WHEELCTL_INFO_BLEDATA,
        WHEELCTL_INFO_BLEMFG,
        WHEELCTL_INFO_NUM           //number of info entries
    };

    /** This wastes 80 bytes due to storing unused max and min floats for entries that doesn't need them
     * However, at the moment I think it's a worthwile tradeoff
     * @brief wheel data structure, holds current, max and min values
     */
    typedef struct {
        float value = 0;
        float max_value = 0;
        float min_value = 0;
    } wheelctl_data_t;

    enum { 
        WHEELCTL_VOLTAGE,   //Current battery voltage -required
        WHEELCTL_SPEED,     //Current speed in kmh -required
        WHEELCTL_ODO,       //Total ride distance since new
        WHEELCTL_CURRENT,   //Current current consumption -required
        WHEELCTL_TEMP,      //Internal wheel temperature -required, might change to optional
        WHEELCTL_RMODE,     //Wheel ride mode
        WHEELCTL_BATTPCT,   //Calculated percentage of remaining battery
        WHEELCTL_POWER,     //Wheel power output
        WHEELCTL_TRIP,      //Value = Ride distance since wheel power on
        WHEELCTL_UPTIME,    //Time since power on in seconds
        WHEELCTL_TOPSPEED,  //max speed reached in kmh since power on
        WHEELCTL_FANSTATE,  //Internal fan run state
        WHEELCTL_ALARM1,    //Speed when first alarm is triggered
        WHEELCTL_ALARM2,    //Speed when second alarm is triggered
        WHEELCTL_ALARM3,    //Speed when third alarm is triggered
        WHEELCTL_TILTBACK,  //Speed when tiltback is triggered  -required
        WHEELCTL_DATA_NUM   //number of data entries
    };
    
    /**
     * @brief initial setup of wheelctl
     */
    void wheelctl_setup( void );

    /**
     * @brief get the value for a specific wheel data entry
     * 
     * @param   entry     configitem: WHEELCTL_VOLTAGE, WHEELCTL_SPEED, WHEELCTL_ODO, WHEELCTL_CURRENT,  
     * WHEELCTL_TEMP, WHEELCTL_RMODE, WHEELCTL_BATTPCT, WHEELCTL_POWER, WHEELCTL_TRIP, WHEELCTL_UPTIME, 
     * WHEELCTL_TOPSPEED, WHEELCTL_FANSTATE, WHEELCTL_ALARM1, WHEELCTL_ALARM2, WHEELCTL_ALARM3, WHEELCTL_TILTBACK, 
     * WHEELCTL_RIDETIME, WHEELCTL_DATA_NUM
     * 
     * @return  float
     */
    float wheelctl_get_data( byte entry );

    /**
     * @brief set the value for a specific wheel data entry
     * 
     * @param   entry     configitem: WHEELCTL_VOLTAGE, WHEELCTL_SPEED, WHEELCTL_ODO, WHEELCTL_CURRENT,  
     * WHEELCTL_TEMP, WHEELCTL_RMODE, WHEELCTL_BATTPCT, WHEELCTL_POWER, WHEELCTL_TRIP, WHEELCTL_UPTIME, 
     * WHEELCTL_TOPSPEED, WHEELCTL_FANSTATE, WHEELCTL_ALARM1, WHEELCTL_ALARM2, WHEELCTL_ALARM3, WHEELCTL_TILTBACK, 
     * WHEELCTL_RIDETIME
     * @param   value    the value of the data entry
     */
    void wheelctl_set_data( byte entry, float value );

    /**
     * @brief get the max value for a specific wheel data entry
     * 
     * @param   entry     onfigitem: WHEELCTL_VOLTAGE, WHEELCTL_SPEED, WHEELCTL_CURRENT,  
     * WHEELCTL_TEMP,  WHEELCTL_BATTPCT, WHEELCTL_POWER
     * 
     * @return  float
     */
    float wheelctl_get_max_data( byte entry );

    /**
     * @brief set the max value for a specific wheel data entry
     * 
     * @param   entry     configitem: WHEELCTL_VOLTAGE, WHEELCTL_SPEED, WHEELCTL_CURRENT,  
     * WHEELCTL_TEMP,  WHEELCTL_BATTPCT, WHEELCTL_POWER
     * @param   max_value    the value of the data entry
     */
    void wheelctl_set_max_data( byte entry, float max_value );

    /**
     * @brief get the  value of the wheel constant
     * 
     * @param   entry     configitem: WHEELCTL_CONST_MAXCURRENT,  WHEELCTL_CONST_CRITTEMP, 
     * WHEELCTL_CONST_WARNTEMP,   WHEELCTL_CONST_BATTVOLT, WHEELCTL_CONST_BATTWARN
     * 
     * @return  uint8_t
     */
    byte wheelctl_get_constant( byte entry );

    /**
     * @brief set the value of the wheel constant
     * 
     * @param   entry     configitem: WHEELCTL_CONST_MAXCURRENT, WHEELCTL_CONST_CRITTEMP, 
     * WHEELCTL_CONST_WARNTEMP, WHEELCTL_CONST_BATTVOLT, WHEELCTL_CONST_BATTWARN
     * @param   value     the value of the constant
     */
    void wheelctl_set_constant( byte entry, uint8_t value );

    /**
     * @brief get the value of the wheel info entry
     * 
     * @param   entry     configitem: WHEELCTL_INFO_SERIAL, WHEELCTL_INFO_MANUFACTURER, 
     * WHEELCTL_INFO_MODEL, WHEELCTL_INFO_VERSION
     * 
     * @return  String
     */
    String wheelctl_get_info( byte entry );

    /**
     * @brief set the value of the wheel info entry
     * 
     * @param   entry     configitem: WHEELCTL_INFO_SERIAL, WHEELCTL_INFO_MANUFACTURER, 
     * WHEELCTL_INFO_MODEL, WHEELCTL_INFO_VERSION
     * 
     * @param   value     the value of the info entry
     */
    void wheelctl_set_info( byte entry, String value );
    /**
     * @brief get the state of the wheel configuraion setting
     * 
     * @param   config     configitem: WHEELCTL_CONFIG_LED, WHEELCTL_CONFIG_HORN, 
     * WHEELCTL_CONFIG_HAPTIC, WHEELCTL_CONFIG_LIGHTS_OFF, WHEELCTL_CONST_BATTWARN
     */
    bool wheelctl_get_config( byte config );
    /**
     * @brief set the state of the wheel configuration entry
     * 
     * @param   config     configitem: WHEELCTL_INFO_SERIAL, WHEELCTL_INFO_MANUFACTURER, 
     * WHEELCTL_INFO_MODEL, WHEELCTL_INFO_VERSION
     * 
     * @param   enable     if the setting is true or false
     */
    void wheelctl_set_config( byte config, bool enable );
    /**
     * @brief toggle EUC main lights
     */
    void wheelctl_toggle_lights( void );
    /**
     * @brief force all dashboard elements to update
     */
    void wheelctl_update_values(void);
    /**
     * @brief set startup wheel settings according to configuration.
     * available settings: lights off when connect.
     */
    void wheelctl_connect_actions(void);
    /**
     * @brief set actions to perform when wheel is disconnected
     */
    void wheelctl_disconnect_actions(void);
     /**
     * @brief Save wheel configuration
     */
    void wheelctl_save_config( void );
    /**
     * @brief Reset trip data
     */
    void wheelctl_reset_trip( void );

    #endif
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

#include "config.h"
#include "Arduino.h"
#include "wheelctl.h"
#include "blectl.h"
#ifdef HAS_MOTOR
#include "motor.h"
#endif
#include "callback.h"
#include "config/json_psram_allocator.h"
#include "alloc.h"
#include "Kingsong.h"
#include "eventmgm.h"
//#include "gui/mainbar/setup_tile/setup_tile.h"
#include "gui/dashboard/dashboard.h"

#define BATT_AVG_ENTRIES 10

lv_task_t *speed_shake = nullptr;
lv_task_t *current_shake = nullptr;
lv_task_t *temp_shake = nullptr;
lv_task_t *ride_tick = nullptr;
lv_task_t *save_trip_task = nullptr;

static void lv_speed_shake(lv_task_t *speed_shake);
static void lv_current_shake(lv_task_t *current_shake);
static void lv_temp_shake(lv_task_t *temp_shake);
void update_speed_shake(float value);
void update_current_shake(float value);
void update_temp_shake(float value);

void wheelctl_update_max_min(int entry, float value, bool update_min);
void wheelctl_update_regen_current(int entry, float value);
void wheelctl_update_battpct_max_min(int entry, float value);
void update_calc_battery(float value);
void wheelctl_calc_power(float value);
void wheelctl_tick_update( void );
void wheelctl_save_trip_task(lv_task_t *save_trip_task);
void wheelctl_update_powercons( float seconds );
void wheelctl_update_avgspeed(float value);
void wheelctl_update_watch_trip(float value);
void wheelctl_read_config( void );
void wheelctl_save_tripdata(void);
void wheelctl_read_tripdata(void);


bool shakeoff[3] = {true, true, true};
bool lightsoff = true;
bool firstrun[WHEELCTL_DATA_NUM];
float old_uptime = 0;
bool sync_trip = true;
bool sync_millis = true;
bool saving_trip_data = false; //for disabling dashboard updates while saving trip data

wheelctl_data_t wheelctl_data[WHEELCTL_DATA_NUM];
wheelctl_constants_t wheelctl_constants[WHEELCTL_CONST_NUM];
wheelctl_info_t wheelctl_info[WHEELCTL_INFO_NUM];
wheelctl_config_t wheelctl_config[WHEELCTL_CONFIG_NUM];
tripdata_t current_tripdata;
wheelctlconfig_t wheelctlconfig;

/**
* @brief set wheel constants to initial default values
*/
void wheelctl_init_constants( void ) {
    wheelctl_constants[WHEELCTL_CONST_MAXCURRENT].value = 40;
    wheelctl_constants[WHEELCTL_CONST_CRITTEMP].value = 65;
    wheelctl_constants[WHEELCTL_CONST_WARNTEMP].value = 55;
    wheelctl_constants[WHEELCTL_CONST_BATTVOLT].value = 67;
    wheelctl_constants[WHEELCTL_CONST_BATTWARN].value = 40;
    wheelctl_constants[WHEELCTL_CONST_BATTCRIT].value = 10;
    wheelctl_constants[WHEELCTL_CONST_BATT_IR].value = 20;
}

void wheelctl_setup(void)
{
    wheelctl_data[WHEELCTL_SPEED].max_value = 0;
    wheelctl_data[WHEELCTL_SPEED].min_value = 0;
    wheelctl_data[WHEELCTL_BATTPCT].max_value = 0;
    wheelctl_data[WHEELCTL_BATTPCT].min_value = 100;
    wheelctl_data[WHEELCTL_CURRENT].max_value = 0;
    wheelctl_data[WHEELCTL_CURRENT].min_value = 0;
    wheelctl_data[WHEELCTL_TEMP].min_value = 0;
    wheelctl_init_constants();
    wheelctl_update_values();
    wheelctl_read_config();
    wheelctl_read_tripdata();
    //current_trip_read_data();
    sync_trip = true;
    #ifdef HAS_MOTOR
        motor_vibe(5, true);
    #endif
}

void wheelctl_connect_actions(void) 
{
    if (wheelctlconfig.save_light_state) {
        lightsoff = true;
        wheelctl_toggle_lights();
    }
    sync_trip = true;
    sync_millis = true;
    //ride_tick = lv_task_create( wheelctl_tick_update, 1000, LV_TASK_PRIO_LOW, NULL );
    //save_trip_task = lv_task_create( wheelctl_save_trip_task, 20000, LV_TASK_PRIO_LOW, NULL );
    //setup_tile_connect_update(wheelctl_get_info(WHEELCTL_INFO_MODEL));
}

void wheelctl_disconnect_actions(){
    //if (ride_tick != nullptr) lv_task_del(ride_tick);
    //if (save_trip_task != nullptr) lv_task_del(save_trip_task);
    //setup_tile_connect_update("disconnected");
}

void wheelctl_update_values(void)
{
    for (int i = 0; i < WHEELCTL_DATA_NUM; i++)
    {
        firstrun[i] = {true};
    }
}

float wheelctl_get_data(byte entry)
{
    if (entry < WHEELCTL_DATA_NUM)
    {
        return (wheelctl_data[entry].value);
    }
    return 0;
}

void wheelctl_set_data(byte entry, float value)
{
    if (entry < WHEELCTL_DATA_NUM && !saving_trip_data)
    {
        if (firstrun[entry]) wheelctl_data[entry].value = value;
        switch (entry)
        {
        case WHEELCTL_SPEED:
            if (wheelctl_data[entry].value != value || firstrun[entry])
            {
                update_speed_shake(value);
                wheelctl_update_max_min(entry, value, false);
                if (dash_active) dashboard_speed_update(value, wheelctl_data[WHEELCTL_ALARM3].value, wheelctl_data[WHEELCTL_TILTBACK].value, wheelctl_data[WHEELCTL_SPEED].max_value, wheelctl_data[WHEELCTL_SPEED].min_value);
                firstrun[entry] = false;
            }
            break;
        case WHEELCTL_CURRENT:
            if (wheelctl_data[entry].value != value || firstrun[entry])
            {
                update_current_shake(value);
                wheelctl_update_max_min(entry, value, false);
                wheelctl_update_regen_current(entry, value);
                wheelctl_calc_power(value);
                if (dash_active) dashboard_current_update(value, wheelctl_constants[WHEELCTL_CONST_MAXCURRENT].value, wheelctl_data[WHEELCTL_CURRENT].min_value, wheelctl_data[WHEELCTL_CURRENT].max_value);
                firstrun[entry] = false;
            }
            break;
        case WHEELCTL_VOLTAGE:
            if (wheelctl_data[entry].value != value || firstrun[entry])
            {
                wheelctl_update_max_min(entry, value, true);
                update_calc_battery(value);
                firstrun[entry] = false;
            }
            break;
        case WHEELCTL_TEMP:
            if (wheelctl_data[entry].value != value || firstrun[entry])
            {
                update_temp_shake(value);
                wheelctl_update_max_min(entry, value, true);
                if (dash_active) dashboard_temp_update(value, wheelctl_constants[WHEELCTL_CONST_WARNTEMP].value, wheelctl_constants[WHEELCTL_CONST_CRITTEMP].value, wheelctl_data[WHEELCTL_TEMP].max_value);
                firstrun[entry] = false;
            }
            break;
        case WHEELCTL_BATTPCT:
            if (wheelctl_data[entry].value != value || firstrun[entry])
            {
                wheelctl_update_battpct_max_min(entry, value);
                if (dash_active) dashboard_batt_update(value, current_tripdata.min_battery, current_tripdata.max_battery);
                firstrun[entry] = false;
            }
            break;
        case WHEELCTL_POWER:
            wheelctl_update_max_min(entry, value, false);
            break;
        case WHEELCTL_TRIP:
            wheelctl_update_watch_trip(value);
            wheelctl_update_avgspeed(value);
            break;
        case WHEELCTL_FANSTATE:
            if (dash_active) dashboard_fan_indic(value);
            break;
        case WHEELCTL_UPTIME:
            wheelctl_tick_update();
        }
        firstrun[entry] = false;
        wheelctl_data[entry].value = value;
    }
}

void wheelctl_tick_update( void )
{
    static unsigned long oldmillis = 0;
    static float delta_seconds = 0.0;
    static byte savedelay = 0;

    if ( oldmillis == 0 || oldmillis > millis() || sync_millis ) {
        oldmillis = millis();
        sync_millis = false;
    }
    delta_seconds = (millis() - oldmillis) / 1000.0;
    if (wheelctl_data[WHEELCTL_SPEED].value >= MIN_RIDE_SPEED) {
        current_tripdata.ride_time += delta_seconds;
    }
    wheelctl_update_powercons(delta_seconds);
    oldmillis = millis();
    
    current_tripdata.max_speed = wheelctl_data[WHEELCTL_SPEED].max_value;
    current_tripdata.max_current = wheelctl_data[WHEELCTL_CURRENT].max_value;
    current_tripdata.max_power = wheelctl_data[WHEELCTL_POWER].max_value;
    current_tripdata.max_temperature = wheelctl_data[WHEELCTL_TEMP].max_value;

    if (savedelay > 28) {
        wheelctl_save_tripdata();
        savedelay = 0;
    }
    savedelay++;
}

void wheelctl_save_trip_task(lv_task_t *save_trip_task) {
    wheelctl_save_tripdata();
}

void wheelctl_update_watch_trip(float value)
{
    static float last_value;
    if (value < last_value || sync_trip || wheelctl_data[WHEELCTL_SPEED].value < MIN_RIDE_SPEED) { 
        last_value = value; 
    }
    current_tripdata.trip += (value - last_value);
    last_value = value;
    sync_trip = false;
    if (dash_active && !saving_trip_data) dashboard_trip_update(current_tripdata.trip);
}

void wheelctl_update_avgspeed(float value)
{
    if (current_tripdata.ride_time != 0) {
        current_tripdata.avg_speed = current_tripdata.trip / (current_tripdata.ride_time / 3600);
    }
}

void wheelctl_update_powercons( float seconds ) {
    if( seconds != 0 ) current_tripdata.consumed_energy = current_tripdata.consumed_energy + (POWER_CORRECT_CONST * wheelctl_data[WHEELCTL_POWER].value * seconds / 3600 );
    if (current_tripdata.trip != 0) current_tripdata.trip_economy = current_tripdata.consumed_energy / current_tripdata.trip;
}

void wheelctl_update_max_min(int entry, float value, bool update_min)
{
    if (wheelctl_data[entry].value > wheelctl_data[entry].max_value)
    {
        wheelctl_data[entry].max_value = wheelctl_data[entry].value;
    }
    if (wheelctl_data[entry].value < wheelctl_data[entry].min_value && update_min)
    {
        wheelctl_data[entry].min_value = wheelctl_data[entry].value;
    }
}

void wheelctl_update_battpct_max_min(int entry, float value)
{
    if (wheelctl_data[WHEELCTL_CURRENT].value > 0)
    {
        wheelctl_update_max_min(entry, value, true);
        current_tripdata.max_battery = wheelctl_data[WHEELCTL_BATTPCT].max_value;
        current_tripdata.min_battery = wheelctl_data[WHEELCTL_BATTPCT].min_value;
    }
    if (value < 10) {
        if (dash_active) dashboard_batt_alert(true);
    }
    else {
        if (dash_active) dashboard_batt_alert(false);
    }
}

void wheelctl_update_regen_current(int entry, float value)
{
    if (value < 0)
    {
        float negamp = (value * -1);
        if (negamp > wheelctl_data[entry].min_value)
        {
            wheelctl_data[entry].min_value = negamp;
            current_tripdata.max_regen_current = negamp;
        }
    }
}

void wheelctl_calc_power(float value)
{
    wheelctl_set_data(WHEELCTL_POWER, wheelctl_data[WHEELCTL_VOLTAGE].value * value);
}

void update_calc_battery(float value)
{
    float voltagesag = wheelctl_constants[WHEELCTL_CONST_BATT_IR].value * wheelctl_data[WHEELCTL_CURRENT].value;

    /*
    static int centivolt_array[BATT_AVG_ENTRIES] = {0};
    static int i = 0;
    int sum = 0;
    int num = 0;
    if (i < BATT_AVG_ENTRIES) i++; else i = 0;

    centivolt_array[i] = (value * 100) + voltagesag; //compensate for battery pack internal resitance
    for (int j = 0; j < BATT_AVG_ENTRIES; j++)
    {
        if (centivolt_array[j] > 0)
        {
            sum += centivolt_array[j];
            num++;
        }
    }
    int centivolt = sum / num;
    */

    int centivolt = (value * 100) + voltagesag;

    if (wheelctl_constants[WHEELCTL_CONST_BATTVOLT].value < 70)
    {
        if (centivolt > 6680)
            wheelctl_set_data(WHEELCTL_BATTPCT, 100.0);
        else if (centivolt > 5440)
            wheelctl_set_data(WHEELCTL_BATTPCT, (centivolt - 5320) / 13.6);
        else if (centivolt > 5120)
            wheelctl_set_data(WHEELCTL_BATTPCT, (centivolt - 5120) / 36.0);
        else
            wheelctl_set_data(WHEELCTL_BATTPCT, 0.0);
        return;
    }
    else if (wheelctl_constants[WHEELCTL_CONST_BATTVOLT].value < 86)
    {
        if (centivolt > 8350)
            wheelctl_set_data(WHEELCTL_BATTPCT, 100.0);
        else if (centivolt > 6800)
            wheelctl_set_data(WHEELCTL_BATTPCT, (centivolt - 6650) / 17);
        else if (centivolt > 6400)
            wheelctl_set_data(WHEELCTL_BATTPCT, (centivolt - 6400) / 45);
        else
            wheelctl_set_data(WHEELCTL_BATTPCT, 0.0);
        return;
    }
    else if (wheelctl_constants[WHEELCTL_CONST_BATTVOLT].value < 105)
    {
        if (centivolt > 10020)
            wheelctl_set_data(WHEELCTL_BATTPCT, 100.0);
        else if (centivolt > 8160)
            wheelctl_set_data(WHEELCTL_BATTPCT, (centivolt - 8070) / 19.5);
        else if (centivolt > 7660)
            wheelctl_set_data(WHEELCTL_BATTPCT, (centivolt - 7935) / 48.75);
        else
            wheelctl_set_data(WHEELCTL_BATTPCT, 0.0);
        return;
    }
}

float wheelctl_get_max_data(byte entry)
{
    if (entry < WHEELCTL_DATA_NUM)
    {
        return (wheelctl_data[entry].max_value);
    }
    return 0;
}

void wheelctl_set_max_data(byte entry, float max_value)
{
    if (entry < WHEELCTL_DATA_NUM)
    {
        wheelctl_data[entry].max_value = max_value;
    }
}

byte wheelctl_get_constant(byte entry)
{
    if (entry < WHEELCTL_CONST_NUM)
    {
        return (wheelctl_constants[entry].value);
    }
    return 0;
}

void wheelctl_set_constant(byte entry, byte value)
{
    if (entry < WHEELCTL_CONST_NUM)
    {
        wheelctl_constants[entry].value = value;
    }
}

String wheelctl_get_info(byte entry)
{
    if (entry < WHEELCTL_INFO_NUM)
    {
        return (wheelctl_info[entry].value);
    }
    return "undefined";
}

void wheelctl_set_info(byte entry, String value)
{
    if (entry < WHEELCTL_INFO_NUM)
    {
        wheelctl_info[entry].value = value;
    }
}

//Haptic feedback
void update_speed_shake(float value)
{
    if (value >= wheelctl_data[WHEELCTL_ALARM3].value && shakeoff[0])
    {
        eventmgm_set_event(EVENTMGM_WAKEUP_REQUEST); //used tilt event mask to wake up display
        speed_shake = lv_task_create(lv_speed_shake, 250, LV_TASK_PRIO_LOWEST, NULL);
        lv_task_ready(speed_shake);
        shakeoff[0] = false;
        log_i("speedshake on");
    }
    else if (value < wheelctl_data[WHEELCTL_ALARM3].value && !shakeoff[0] && speed_shake != nullptr)
    {
        lv_task_del(speed_shake);
        shakeoff[0] = true;
        log_i("speedshake off");
    }
}

void update_current_shake(float value)
{
    if (value >= (wheelctl_constants[WHEELCTL_CONST_MAXCURRENT].value * 0.75) && shakeoff[1] && current_shake != nullptr)
    {
        eventmgm_set_event(EVENTMGM_WAKEUP_REQUEST);
        current_shake = lv_task_create(lv_current_shake, 500, LV_TASK_PRIO_LOWEST, NULL);
        lv_task_ready(current_shake);
        shakeoff[1] = false;
        if (dash_active) dashboard_current_alert(true);
        //if (simpledash_active) simpledash_current_alert(true);
    }
    else if (value < (wheelctl_constants[WHEELCTL_CONST_MAXCURRENT].value * 0.75) && !shakeoff[1])
    {
        lv_task_del(current_shake);
        shakeoff[1] = true;
        if (dash_active) dashboard_current_alert(false);
        //if (simpledash_active) simpledash_current_alert(false);
    }
}

void update_temp_shake(float value)
{
    if (value > wheelctl_constants[WHEELCTL_CONST_CRITTEMP].value && shakeoff[2])
    {
        eventmgm_set_event(EVENTMGM_WAKEUP_REQUEST);
        temp_shake = lv_task_create(lv_temp_shake, 1000, LV_TASK_PRIO_LOWEST, NULL);
        lv_task_ready(temp_shake);
        shakeoff[2] = false;
        if (dash_active) dashboard_temp_alert(true);
        //if (simpledash_active) simpledash_temp_alert(true);
    }
    else if (value <= wheelctl_constants[WHEELCTL_CONST_CRITTEMP].value && !shakeoff[2] && temp_shake != nullptr)
    {
        lv_task_del(temp_shake);
        shakeoff[2] = true;
        if (dash_active) dashboard_temp_alert(false);
        //if (simpledash_active) simpledash_temp_alert(false);
    }
}

static void lv_current_shake(lv_task_t *current_shake)
{
    #ifdef HAS_MOTOR
    motor_vibe(50, true);
    #endif
}

static void lv_temp_shake(lv_task_t *temp_shake)
{
    #ifdef HAS_MOTOR
    motor_vibe(20, true);
    delay(150);
    motor_vibe(20, true);
    #endif
}

static void lv_speed_shake(lv_task_t *speed_shake)
{
    #ifdef HAS_MOTOR
    motor_vibe(20, true);
    #endif
} //End haptic feedback

void wheelctl_toggle_lights(void)
{
    String wheeltype = wheelctl_info[WHEELCTL_INFO_MANUFACTURER].value;
    if (wheeltype == "KS")
    {
        if (blectl_cli_getconnected()) {
            ks_lights(lightsoff);
            //if (wheelctl_config[WHEELCTL_CONFIG_LED].enable) ks_led(lightsoff);
        }
        if (lightsoff) lightsoff = false; else lightsoff = true;
    }
    else if (wheeltype == "GW")
    {
        //if (blectl_cli_getconnected()) gw_lights(lightsoff);
        //if (lightsoff) lightsoff = false; else lightsoff = true;
    }
    else if (wheeltype == "IM")
    {
        //if (blectl_cli_getconnected()) im_lights(lightsoff);
        //if (lightsoff) lightsoff = false; else lightsoff = true;
    }
    else if (wheeltype == "NBZ")
    {
        //if (blectl_cli_getconnected()) nbz_lights(lightsoff);
        //if (lightsoff) lightsoff = false; else lightsoff = true;
    }
    else if (wheeltype == "NB")
    {
        //if (blectl_cli_getconnected()) nb_lights(lightsoff);
        //if (lightsoff) lightsoff = false; else lightsoff = true;
    }
}


void wheelctl_save_config( void ) {
    wheelctlconfig.save();
}

void wheelctl_read_config( void ) {
    wheelctlconfig.load();
}


void wheelctl_save_tripdata(void) {
    current_tripdata.save();
}

void wheelctl_read_tripdata(void) {
    current_tripdata.load();

    wheelctl_data[WHEELCTL_SPEED].max_value = current_tripdata.max_speed;
    wheelctl_data[WHEELCTL_SPEED].min_value = current_tripdata.avg_speed;
    wheelctl_data[WHEELCTL_CURRENT].max_value = current_tripdata.max_current;
    wheelctl_data[WHEELCTL_CURRENT].min_value = current_tripdata.max_regen_current;
    wheelctl_data[WHEELCTL_POWER].max_value = current_tripdata.max_power;
    wheelctl_data[WHEELCTL_BATTPCT].max_value = current_tripdata.max_battery;
    wheelctl_data[WHEELCTL_BATTPCT].min_value = current_tripdata.min_battery;
    wheelctl_data[WHEELCTL_TEMP].max_value = current_tripdata.max_temperature;
}

void wheelctl_reset_trip( void ) {
    #ifdef HAS_MOTOR
        motor_vibe(5, true);
    #endif
    current_tripdata.ride_time = 0.0;
    current_tripdata.trip = 0.0;
    current_tripdata.max_speed = 0.0;
    current_tripdata.avg_speed = 0.0;
    current_tripdata.max_current = 0.0;
    current_tripdata.max_regen_current = 0.0;
    current_tripdata.max_power = 0.0;
    current_tripdata.max_battery = 0.0;
    current_tripdata.min_battery = 100.0;
    current_tripdata.max_temperature =  0.0;
    current_tripdata.consumed_energy = 0.0;
    current_tripdata.trip_economy = 0.0;

    wheelctl_data[WHEELCTL_SPEED].max_value = current_tripdata.max_speed;
    wheelctl_data[WHEELCTL_SPEED].min_value = current_tripdata.avg_speed;
    wheelctl_data[WHEELCTL_CURRENT].max_value = current_tripdata.max_current;
    wheelctl_data[WHEELCTL_CURRENT].min_value = current_tripdata.max_regen_current;
    wheelctl_data[WHEELCTL_POWER].max_value = current_tripdata.max_power;
    wheelctl_data[WHEELCTL_BATTPCT].max_value = current_tripdata.max_battery;
    wheelctl_data[WHEELCTL_BATTPCT].min_value = current_tripdata.min_battery;
    wheelctl_data[WHEELCTL_TEMP].max_value = current_tripdata.max_temperature;
    //current_trip_save_data();
}
/****************************************************************************
 *   2020 Jesper Ortlund
 *   Snippets and inspiration from My-TTGO-Watch by Dirk Brosswick
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

/*
 *  
 *
 */

#include <BLEDevice.h>
//#include <BLEClient.h>
//#include <BLEUtils.h>
//#include <BLE2902.h>
#include "SPIFFS.h"
#include "blectl.h"
//#include "pmu.h"
#include "eventmgm.h"
#include "config/json_psram_allocator.h"
#include "config/blectlconfig.h"
#include "wheelctl.h"
#include "gui/dashboard/dashboard.h"
#include "gui/gui.h"


#include "Kingsong.h"

EventGroupHandle_t blectl_status = NULL;
portMUX_TYPE DRAM_ATTR blectlMux = portMUX_INITIALIZER_UNLOCKED;

//blectl_config_t blectl_config;
blectlconfig_t blectl_config;
stored_wheel_t stored_wheel[MAX_STORED_WHEELS];
detected_wheel_t detected_wheel[MAX_DETECTED_WHEELS];
blectl_msg_t blectl_msg;
callback_t *blectl_callback = NULL;
//stored_wheels_t stored_wheels;

bool blectl_send_event_cb(EventBits_t event, void *arg);
bool blectl_cli_eventmgm_event_cb(EventBits_t event, void *arg);
bool blectl_cli_eventmgm_loop_cb(EventBits_t event, void *arg);
void blectl_cli_loop(void);
bool connectToServer(void);
static void scanCompleteCB(BLEScanResults scanResults);
void blectl_clear_detected_wheels(void);
bool blectl_wheeladdress_detected(String addr);

bool clidoConnect = false;
bool cli_ondisconnect = false;
bool wheel_found = false;
bool notify_active = false;
int wheel_num = 0;
int scandelay = 0;
byte blectl_detected_wheels;
bool newscan = false;

uint8_t txfValue = 0;
String blename;
String blemfg;
byte myWheeltype;
BLEClient *pClient = NULL;
BLEScan *pBLEScan = NULL;
char zero_addr[18] = "00:00:00:00:00:00";

static BLERemoteCharacteristic *pRemoteCharacteristic;
static BLEAdvertisedDevice *myDevice;
static uint64_t NextMillis = millis();


class MyClientCallback : public BLEClientCallbacks
{
    void onConnect(BLEClient *pclient)
    {
        log_i("onConnect");
        blectl_set_event(BLECTL_CLI_CONNECTED);
        blectl_clear_event(BLECTL_CLI_DISCONNECTED);
    }
    void onDisconnect(BLEClient *pclient)
    {
        cli_ondisconnect = true;
        blectl_set_event(BLECTL_CLI_DISCONNECTED);
        blectl_clear_event(BLECTL_CLI_CONNECTED);
        wheelctl_disconnect_actions();
        log_i("onDisconnect -- cliconnected is false");
        return;
    }
};

void blectl_reset_scandelay(void) {
    NextMillis = millis() - 14000;
}

bool blectl_cli_eventmgm_event_cb(EventBits_t event, void *arg) {
    bool retval = true;
    switch (event) {
    case EVENTMGM_STANDBY:
        if (blectl_get_event(BLECTL_CLI_CONNECTED))
        {
            retval = false;
            log_i("standby blocked by wheel being connected");
        }
        else log_i("go standby");
        break;
    case EVENTMGM_WAKEUP:
        blectl_reset_scandelay();
        log_i("go wakeup");
        break;
    case EVENTMGM_SILENCE_WAKEUP:
        blectl_reset_scandelay();
        log_i("go silence wakeup");
        break;
    }
    return (retval);
}

void blectl_set_event(EventBits_t bits)
{
    portENTER_CRITICAL(&blectlMux);
    xEventGroupSetBits(blectl_status, bits);
    portEXIT_CRITICAL(&blectlMux);
}

void blectl_clear_event(EventBits_t bits)
{
    portENTER_CRITICAL(&blectlMux);
    xEventGroupClearBits(blectl_status, bits);
    portEXIT_CRITICAL(&blectlMux);
}

bool blectl_get_event(EventBits_t bits)
{
    portENTER_CRITICAL(&blectlMux);
    EventBits_t temp = xEventGroupGetBits(blectl_status) & bits;
    portEXIT_CRITICAL(&blectlMux);
    if (temp) return (true);
    return (false);
}

bool blectl_register_cb(EventBits_t event, CALLBACK_FUNC callback_func, const char *id)
{
    if (blectl_callback == NULL)
    {
        blectl_callback = callback_init("blectl");
        if (blectl_callback == NULL)
        {
            log_e("blectl callback alloc failed");
            while (true)
                ;
        }
    }
    return (callback_register(blectl_callback, event, callback_func, id));
}

bool blectl_send_event_cb(EventBits_t event, void *arg)
{
    log_i("blectl send callback");
    return (callback_send(blectl_callback, event, arg));
}

void blectl_set_enable_on_standby(bool enable_on_standby)
{
    blectl_config.enable_on_standby = enable_on_standby;
    blectl_save_config();
}

void blectl_on(){
    //btStart();
}
void blectl_off(){
    //btStop();
}

void blectl_set_txpower(int32_t txpower) {
    if (txpower >= 0 && txpower <= 4) {
        blectl_config.txpower = txpower;
    }
    switch (blectl_config.txpower) {
    case 0:
        BLEDevice::setPower(ESP_PWR_LVL_N12);
        break;
    case 1:
        BLEDevice::setPower(ESP_PWR_LVL_N9);
        break;
    case 2:
        BLEDevice::setPower(ESP_PWR_LVL_N6);
        break;
    case 3:
        BLEDevice::setPower(ESP_PWR_LVL_N3);
        break;
    case 4:
        BLEDevice::setPower(ESP_PWR_LVL_N0);
        break;
    default:
        BLEDevice::setPower(ESP_PWR_LVL_N9);
        break;
    }
    blectl_save_config();
}

void blectl_set_autoon(bool autoon) {
    blectl_config.autoon = autoon;
    if (autoon) blectl_on();
    else blectl_off();
    blectl_save_config();
}

int32_t blectl_get_txpower(void) {
    return (blectl_config.txpower);
}

bool blectl_get_enable_on_standby(void) {
    return (blectl_config.enable_on_standby);
}

bool blectl_get_autoon(void) {
    return (blectl_config.autoon);
}

void blectl_set_autoconnect(bool autoconnect) {
    blectl_config.autoconnect = autoconnect;
    blectl_save_config();
}

bool blectl_get_autoconnect(void) {
    return (blectl_config.autoconnect);
}

void blectl_save_config(void) {
    blectl_config.save();
}

void blectl_read_config(void) {
    blectl_config.load();
}

bool blectl_save_stored_wheels (void) {
    fs::File file = SPIFFS.open( BLECTL_JSON_WHEEL_FILE, FILE_WRITE );
   bool successful = false;

    if (!file) {
        log_e("Can't open file: %s!", BLECTL_JSON_WHEEL_FILE );
    }
    else {
        SpiRamJsonDocument doc( 400 ); 
        for (int i = 0; i < MAX_STORED_WHEELS; i++) {
            doc["wheel"][i + 1]["_address"] = stored_wheel[ i ].address;
            doc["wheel"][i + 1]["_type"] = stored_wheel[ i ].type;
            doc["wheel"][i + 1]["_name"] = stored_wheel[ i ].name;
        }
        if ( serializeJsonPretty( doc, file ) == 0) {
            log_e("Failed to write config file");
            successful = false;
        }
        else successful = true;
        doc.clear();
    }
    file.close();
    return successful;
}

void blectl_read_stored_wheels (void) {
    fs::File file = SPIFFS.open( BLECTL_JSON_WHEEL_FILE, FILE_READ );
    if (!file) {
        log_e("Can't open file: %s!", BLECTL_JSON_WHEEL_FILE );
    }
    else {
        int fs = 0;
        int filesize = file.size();
        if (file.size() == 0) fs = 1000;
        SpiRamJsonDocument doc( (filesize * 2) + fs );

        DeserializationError error = deserializeJson( doc, file );
        if ( error ) {
            log_e("update check deserializeJson() failed: %s", error.c_str() );
        }
        else {
            for (int i = 0; i < MAX_STORED_WHEELS; i++) {
                stored_wheel[ i ].address = doc["wheel"][i + 1]["_address"] | "00:00:00:00:00:00";
                stored_wheel[ i ].type = doc["wheel"][i + 1]["_type"] | 0;
                stored_wheel[ i ].name = doc["wheel"][i + 1]["_name"] | blectl_wheeltype_to_string(stored_wheel[ i ].type);
            }
        }        
        doc.clear();
    }
    file.close();
}

String blectl_get_stored_wheel_address(byte wheelnum) {
    return stored_wheel[ wheelnum ].address;
}

byte blectl_get_stored_wheel_type(byte wheelnum) {
    return stored_wheel[ wheelnum ].type;
}

String blectl_get_stored_wheel_name(byte wheelnum) {
    return stored_wheel[ wheelnum ].name;
}

String blectl_get_detected_wheel_address(byte wheelnum) {
    return detected_wheel[ wheelnum ].address;
}

byte blectl_get_detected_wheel_type(byte wheelnum) {
    return detected_wheel[ wheelnum ].type;
}

String blectl_get_detected_wheel_name(byte wheelnum) {
    return detected_wheel[ wheelnum ].name;
}

byte blectl_get_max_detected_wheels(void) {
    return MAX_DETECTED_WHEELS;
}

byte blectl_get_num_detected_wheels(void) {
    return blectl_detected_wheels;
}

void blectl_clear_detected_wheels(void) {
    for (int i = 0; i < MAX_DETECTED_WHEELS; i++) {
        detected_wheel[i].type = WHEELTYPE_NUM;
        detected_wheel[i].address = "00:00:00:00:00:00";
        detected_wheel[i].name = "N/A";
    } 
}

bool blectl_stored_wheel_exist(byte wheelnum) {
    if ( stored_wheel[ wheelnum ].address == "00:00:00:00:00:00" ) return false;
    else return true;
}

bool blectl_wheeladdress_stored(String addr){
for (int i = 0; i < MAX_STORED_WHEELS; i++) { 
        if (stored_wheel[i].address == addr) {
            return true;
        } 
    }
    return false;
}

bool blectl_wheeladdress_detected(String addr){
for (int i = 0; i < MAX_DETECTED_WHEELS; i++) { 
        if (detected_wheel[i].address == addr) {
            return true;
        } 
    }
    return false;
}

byte blectl_get_free_wheelslot( void ){
    for (int i = 0; i < MAX_STORED_WHEELS; i++) { 
        if (!blectl_stored_wheel_exist(i)) {
            return i;
        }
    }
    log_w("no free wheel storage slots");
    return MAX_STORED_WHEELS;
}

String blectl_wheeltype_to_string (byte wheeltype) {
    if (wheeltype == WHEELTYPE_KS) return "KS";
    if (wheeltype == WHEELTYPE_GW) return "GW";
    if (wheeltype == WHEELTYPE_IM) return "IM";
    if (wheeltype == WHEELTYPE_NB) return "NB";
    if (wheeltype == WHEELTYPE_NBZ) return "NBZ";
    if (wheeltype == WHEELTYPE_NUM) return "N/A";
    else return "N/A";
}

bool blectl_add_stored_wheel(String wheeladdress, byte wheeltype, byte wheelslot) {
    bool successful;
    stored_wheel[ wheelslot ].address = wheeladdress;
    stored_wheel[ wheelslot ].type = wheeltype;
    stored_wheel[ wheelslot ].name = blectl_wheeltype_to_string(wheeltype);
    if (stored_wheel[ wheelslot ].address = wheeladdress) {
        successful = blectl_save_stored_wheels();
    }
    else successful = false;
    return successful;
}

bool blectl_remove_stored_wheel(byte wheelnum) {
    bool successful;
    stored_wheel[ wheelnum ].address = "00:00:00:00:00:00";
    stored_wheel[ wheelnum ].type = WHEELTYPE_NUM;
    stored_wheel[ wheelnum ].name = blectl_wheeltype_to_string(WHEELTYPE_NUM);
    if ( stored_wheel[ wheelnum ].address == "00:00:00:00:00:00" ) {
        successful = blectl_save_stored_wheels();
    }
    else successful = false;
    return successful;
}

void blectl_remove_all_wheels(void) {
    for (byte i = 0; i < MAX_STORED_WHEELS; i++) { 
        blectl_remove_stored_wheel(i);
    }
}

bool blectl_set_prio_stored_wheel(byte wheelnum) {
    String tempaddress;
    bool successful;
    if ( stored_wheel[ wheelnum ].address != "00:00:00:00:00:00" ) {
        tempaddress = stored_wheel[ wheelnum ].address;
        stored_wheel[ wheelnum ].address = stored_wheel[ 0 ].address;
        stored_wheel[ 0 ].address = tempaddress;
    }
    if(stored_wheel[ 0 ].address == tempaddress) {
        successful = blectl_save_stored_wheels();
    }
    else successful = false;
    return successful;
}

void matchStoredWheels(BLEAdvertisedDevice advertisedDevice) {
    String adv_addr = advertisedDevice.getAddress().toString().c_str();
    for (int i = 0; i < MAX_STORED_WHEELS; i++) { 
        if (stored_wheel[i].address != "00:00:00:00:00:00") {
            Serial.printf("stored wheel: %d wheeltype %d address: ", i, stored_wheel[i].type);
            Serial.println(stored_wheel[i].address);  
            wheel_found = false;
            if ( adv_addr == stored_wheel[i].address ) {
                log_i("stored wheel detected");
                Serial.printf("Stored wheel detected, wheel num: %d address %s\n", i, stored_wheel[i].address.c_str());
                myDevice = new BLEAdvertisedDevice(advertisedDevice);
                myWheeltype = stored_wheel[i].type;
                clidoConnect = true;
                blectl_set_event(BLECTL_CLI_DOCONNECT);
                return;
            }
            else{
                Serial.printf("device %s is not a stored wheel\n", advertisedDevice.getAddress().toString().c_str());
            }
        }
    }
}

void detectNewWheels(BLEAdvertisedDevice advertisedDevice) {
    String adv_addr = advertisedDevice.getAddress().toString().c_str();
    if(!blectl_wheeladdress_stored(adv_addr) && !blectl_wheeladdress_detected(adv_addr)) {
        newscan = false;
        if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(KS_SERVICE_UUID_1))
        {
            log_i("Kingsong, gotway or Inmotion wheel detected");
            Serial.println("Kingsong, gotway or Inmotion wheel detected");
                
            detected_wheel[wheel_num].type = WHEELTYPE_KS;
            detected_wheel[wheel_num].address = advertisedDevice.getAddress().toString().c_str();
            detected_wheel[wheel_num].name = blectl_wheeltype_to_string(detected_wheel[wheel_num].type);
            Serial.printf("dectected wheel: %s address: %s\n",detected_wheel[wheel_num].name.c_str(),  detected_wheel[wheel_num].address.c_str());

            //temp until settings implemented
            stored_wheel[wheel_num].address = advertisedDevice.getAddress().toString().c_str();
            stored_wheel[wheel_num].name = blectl_wheeltype_to_string(detected_wheel[wheel_num].type);
            stored_wheel[wheel_num].type = WHEELTYPE_KS;

            wheel_num++;
        } 
        else if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(NB_SERVICE_UUID))
        {
            log_i("Ninebot wheel detected");
            detected_wheel[wheel_num].type = WHEELTYPE_NB;
            detected_wheel[wheel_num].address = advertisedDevice.getAddress().toString().c_str();
            detected_wheel[wheel_num].name = blectl_wheeltype_to_string(detected_wheel[wheel_num].type);
            Serial.printf("dectected wheel: %s address: %s\n",detected_wheel[wheel_num].name.c_str(),  detected_wheel[wheel_num].address.c_str());
            wheel_num++;
        } 
        else if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(NBZ_SERVICE_UUID))
        {
            log_i("Ninebot-Z wheel detected");
            detected_wheel[wheel_num].type = WHEELTYPE_NBZ;
            detected_wheel[wheel_num].address = advertisedDevice.getAddress().toString().c_str();
            detected_wheel[wheel_num].name = blectl_wheeltype_to_string(detected_wheel[wheel_num].type);
            Serial.printf("dectected wheel: %s address: %s\n",detected_wheel[wheel_num].name.c_str(),  detected_wheel[wheel_num].address.c_str());
            wheel_num++;
        }
        if (wheel_num > (MAX_DETECTED_WHEELS)) {
            log_i("max number of wheels detected %d", MAX_DETECTED_WHEELS);
        }
    }
}

static void scanCompleteCB(BLEScanResults scanResults) {
	log_e("Scan complete!\n");
	log_e("We found %d devices\n", scanResults.getCount());
    
    if(blectl_get_event(BLECTL_CLI_DETECT)) {
        for(int i = 0 ; (i < scanResults.getCount()) ; i++) {
            if(wheel_num <= (MAX_DETECTED_WHEELS)) detectNewWheels(scanResults.getDevice(i));
        }
        blectl_set_event(BLECTL_CLI_DETECT_DONE);
        blectl_send_event_cb(BLECTL_CLI_DETECT_DONE, NULL);
        blectl_clear_event(BLECTL_CLI_DETECT); 
        newscan = true;
    } else {
        for(int i = 0 ; (i < scanResults.getCount()) ; i++) {
            if(!blectl_get_event(BLECTL_CLI_DOCONNECT)) matchStoredWheels(scanResults.getDevice(i));
        }
    }  
} // scanCompleteCB

bool blectl_cli_eventmgm_loop_cb(EventBits_t event, void *arg){   
    bool retval = true;
    switch (event)
    {
    case EVENTMGM_STANDBY:
        break;
    case EVENTMGM_WAKEUP:
        blectl_cli_loop();
        break;
    case EVENTMGM_SILENCE_WAKEUP:
        blectl_cli_loop();
        break;
    }
    return (retval);
}

void blectl_cli_loop(void){
    static int scandelay = 15000;
    if(!blectl_get_autoconnect() && pClient != NULL) pClient->disconnect();
    
    if (clidoConnect)
    {
        if (connectToServer()){
            log_i("We are now connected to the BLE Server.");
            if ( myWheeltype == WHEELTYPE_KS ) initks();
            //if ( myWheeltype == WHEELTYPE_GW ) initgw();
            //if ( myWheeltype == WHEELTYPE_IM ) initim();
            //if ( myWheeltype == WHEELTYPE_NB ) initnb();
            //if ( myWheeltype == WHEELTYPE_NBZ ) initnbz();

            dashboard_reload();
            gui_jump_to_tilenumber(dashboard_get_tile(), LV_ANIM_OFF);
        }
        else log_w("We have failed to connect to the server;");
        clidoConnect = false;
        blectl_clear_event(BLECTL_CLI_DOCONNECT);
    }
    
    if (millis() - NextMillis > scandelay){
        NextMillis += scandelay;
        if (blectl_config.autoconnect) {
            blectl_set_event(BLECTL_CLI_DOSCAN);
        }
    }
    if (blectl_get_event(BLECTL_CLI_DOSCAN) && !blectl_get_event(BLECTL_CLI_CONNECTED)) {
        wheel_num = 0;
        if (blectl_get_event(BLECTL_CLI_DETECT)) {
            Serial.println("detecting new wheels..");
            
            if (newscan) blectl_clear_detected_wheels();
        } else {
            Serial.println("scanning for stored wheels");
        }
        blectl_scan_once(1);
        blectl_clear_event(BLECTL_CLI_DOSCAN); 
    }
}

void writeBLE(byte *wBLEbyte, int alength){
    pRemoteCharacteristic->writeValue(wBLEbyte, alength);
}

static void notifyCallback(BLERemoteCharacteristic *pBLERemoteCharacteristic, uint8_t *pData, size_t length, bool isNotify) {
    if(myWheeltype == WHEELTYPE_KS){
    //Only decode if package contains relevant data
        if (length == 20) 
        {
            if(!notify_active) notify_active = true;
            if (pData[0] == 0xAA && pData[1] == 0x55)
            {
                decodeKS(pData); // For Kingsong only atm.                         
            }
        }
    }
    else if(myWheeltype == WHEELTYPE_GW){
    //prepare for GW wheels
        if (length == 20) 
        {
            if(!notify_active) notify_active = true;
            if (pData[0] == 0xAA && pData[1] == 0x55)
            {
                //decodeGW(pData);                        
            }
        }
    }
}

bool connectToServer()
{
    BLERemoteService *pRemoteService = nullptr;
    cli_ondisconnect = false;
    log_i("Forming a connection to ");

    log_i("%s",myDevice->getAddress().toString().c_str());
    log_i("%s",myDevice->getName().c_str());
    log_i("%s",myDevice->getManufacturerData().c_str());
    log_i("%s",myDevice->getServiceUUID().toString().c_str());

    blename = myDevice->getName().c_str();
    blemfg = myDevice->getManufacturerData().c_str();

    wheelctl_set_info(WHEELCTL_INFO_BLENAME, blename);
    wheelctl_set_info(WHEELCTL_INFO_BLEMFG, blemfg);

    pClient = BLEDevice::createClient();
    log_i(" - Created client");

    pClient->setClientCallbacks(new MyClientCallback());
    log_i(" - set callbacks");

    // Connect to the remote BLE Server.
    pClient->connect(myDevice); // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
    log_i(" - Connected to server");
    delay(50);
    if (cli_ondisconnect){
        log_w("connection lost unexpectedly");
        return false;
    }

    // Obtain a reference to the service we are after in the remote BLE server.
    if (myWheeltype == WHEELTYPE_NUM) {
        pRemoteService = pClient->getService(KS_SERVICE_UUID_2);
        if (pRemoteService != nullptr) {
            log_i(" - Found ks/gw/nb service");
            Serial.println(" - Found ks/gw/nb service");
        }
        if (pRemoteService == nullptr) {
            pRemoteService = pClient->getService(KS_SERVICE_UUID_1);
            if (pRemoteService != nullptr) {
                log_i(" - Found unknown service");
            }
        }
    }
    if (pRemoteService == nullptr && myWheeltype == WHEELTYPE_KS) {
        pRemoteService = pClient->getService(KS_SERVICE_UUID_2);
        if (pRemoteService != nullptr) {
            log_i(" - Found ks service");
        }
    }
    if (pRemoteService == nullptr && myWheeltype == WHEELTYPE_GW) {
        pRemoteService = pClient->getService(KS_SERVICE_UUID_2);
        if (pRemoteService != nullptr) {
            log_i(" - Found ks service");
        }
    }
    if (pRemoteService == nullptr && myWheeltype == WHEELTYPE_NBZ) {
        pRemoteService = pClient->getService(NBZ_SERVICE_UUID);
        if (pRemoteService != nullptr) {
            log_i(" - Found nbz service");
        }
    }  
    if (pRemoteService == nullptr && myWheeltype == WHEELTYPE_NB) {
        pRemoteService = pClient->getService(NB_SERVICE_UUID);
        if (pRemoteService != nullptr) {
            log_i(" - Found nbz service");
        }
    }  
    if (pRemoteService == nullptr && myWheeltype == WHEELTYPE_IM) {
        pRemoteService = pClient->getService(IM_WRITE_SERVICE_UUID);
        if (pRemoteService != nullptr) {
            log_i(" - Found im service");
        }
    }
    //No corresponding service found
    if (pRemoteService == nullptr)
    {
        log_e("Failed to find our service UUID: ", KS_SERVICE_UUID_2.toString().c_str());
        pClient->disconnect();
        blectl_clear_event(BLECTL_CLI_CONNECTED);
        return false;
    }

    if (cli_ondisconnect){
        log_w("connection lost unexpectedly - 2");
        return false;
    }

    // Obtain a reference to the characteristic in the service of the remote BLE server.

    if (myWheeltype == WHEELTYPE_NUM || myWheeltype == WHEELTYPE_KS || myWheeltype == WHEELTYPE_GW) {
        pRemoteCharacteristic = pRemoteService->getCharacteristic(KS_CHAR_UUID);
        if (pRemoteCharacteristic != nullptr) {
            log_i(" - Found KS/GW characteristic");
            Serial.println(" - Found KS/GW characteristic");
        }
        else{
            log_e("Failed to find our characteristic UUID: ", KS_CHAR_UUID.toString().c_str());
        }
    }
    else if (myWheeltype == WHEELTYPE_NB) {
        pRemoteCharacteristic = pRemoteService->getCharacteristic(NB_READ_CHAR_UUID);
        if (pRemoteCharacteristic != nullptr) {
            log_i(" - Found IM characteristic");
        }
        else{
            log_e("Failed to find our characteristic UUID: ", IM_READ_CHAR_UUID.toString().c_str());
        }
    }
    else if (myWheeltype == WHEELTYPE_IM) {
        pRemoteCharacteristic = pRemoteService->getCharacteristic(IM_READ_CHAR_UUID);
        if (pRemoteCharacteristic != nullptr) {
            log_i(" - Found IM characteristic");
        }
        else{
            log_e("Failed to find our characteristic UUID: ", IM_READ_CHAR_UUID.toString().c_str());
        }
    }
    else if (myWheeltype == WHEELTYPE_NBZ) {
        pRemoteCharacteristic = pRemoteService->getCharacteristic(NBZ_READ_CHAR_UUID);
        if (pRemoteCharacteristic != nullptr) {
            log_i(" - Found NBZ characteristic");
        }
        else{
            log_e("Failed to find our characteristic UUID: ", NBZ_READ_CHAR_UUID.toString().c_str());
        }
    }
    if (pRemoteCharacteristic == nullptr)
    {
        log_e("Failed to find any suitable characteristic UUID");
        pClient->disconnect();
        blectl_clear_event(BLECTL_CLI_CONNECTED);
        return false;
    }
    // Read the value of the characteristic.
    if (pRemoteCharacteristic->canRead())
    {
        std::string value = pRemoteCharacteristic->readValue();
        const char * value_str = value.c_str();
        Serial.printf("characteristic readable value: x%sx\n", value_str);
        Serial.println(value_str);
        if( strcmp( value.c_str(), "" ) == 0 ) {
            Serial.println("no characteristic value received");
            //ks_init_notifications();
            value_str = pRemoteCharacteristic->readValue().c_str();
            Serial.printf("characteristic readable value: x%sx\n", value_str);
        } else {
            Serial.println("characteristic value received");
            Serial.printf("characteristic readable value: x%sx\n", value_str);
        }
    }
    // Register for notify
    if (pRemoteCharacteristic->canNotify() == true)
    {
        notify_active = false;
        pRemoteCharacteristic->registerForNotify(notifyCallback);
        Serial.printf("characteristic does notify -- registered for notifications\n");
        
        if (myWheeltype == WHEELTYPE_NUM) {
            if (!notify_active) {
                Serial.printf("notifications inactive probably KS wheel\n");
                wheelctl_set_info(WHEELCTL_INFO_MANUFACTURER, "KS");
                myWheeltype = WHEELTYPE_KS;
            }
            else {
                Serial.printf("notifications active probably GW wheel\n");
                wheelctl_set_info(WHEELCTL_INFO_MANUFACTURER, "GW");
                myWheeltype = WHEELTYPE_GW;
            }
        }
    }
    blectl_set_event(BLECTL_CLI_CONNECTED);
    return blectl_get_event(BLECTL_CLI_CONNECTED);
}

bool blectl_cli_getconnected( void )
{ 
    return blectl_get_event(BLECTL_CLI_CONNECTED);
}

void blectl_scan_once(int scantime)
{ 
    if ( !blectl_get_event(BLECTL_CLI_CONNECTED) )
    {     
        log_i("Disconnected... starting scan");
        pBLEScan->start(scantime, scanCompleteCB, false);
    }
}

void blectl_scan_setup()
{
    log_i("Starting Arduino BLE Client application...");
    blectl_read_config();
    blectl_read_stored_wheels();
    blectl_status = xEventGroupCreate();
    BLEDevice::init("esp32-ble");
    blectl_set_txpower( blectl_config.txpower );

    pBLEScan = BLEDevice::getScan();
    blectl_clear_detected_wheels();
    //blectl_reset_scandelay();
    blectl_set_event(BLECTL_CLI_DETECT);
    //blectl_remove_all_wheels();
    eventmgm_register_cb(EVENTMGM_SILENCE_WAKEUP | EVENTMGM_STANDBY | EVENTMGM_WAKEUP | EVENTMGM_WAKEUP_REQUEST | EVENTMGM_STANDBY_REQUEST | EVENTMGM_SILENCE_WAKEUP_REQUEST, blectl_cli_eventmgm_event_cb, "blectl_cli");
    eventmgm_register_loop_cb(EVENTMGM_SILENCE_WAKEUP | EVENTMGM_STANDBY | EVENTMGM_WAKEUP, blectl_cli_eventmgm_loop_cb, "blectl_cli loop");
}
#include "config.h"
#include "SPIFFS.h"

#include "hardware/hardware.h"
#include "hardware/display.h"
#include "hardware/i2c_bus.h"
#include "hardware/button.h"
#include "hardware/rtc.h"
#include "hardware/power.h"
#include "system/configuration.h"
#include "system/eventmgm.h"
#include "system/lvglctl.h"
#include "system/blectl.h"
#include "system/wheelctl.h"
#include "system/wheeldb.h"
#include "gui/gui.h"
#include "gui/main/mainscreen.h"

void setup() {
    Serial.begin(115200);
    if(SPIFFS.begin(true)){ 
        Serial.println("SPIFFS mounted successfully");
        unsigned int totalBytes = SPIFFS.totalBytes();
        unsigned int usedBytes = SPIFFS.usedBytes();

        Serial.printf("===== File system info =====\n");
        Serial.printf("Total space:      %d byte\n", totalBytes);
        Serial.printf("Total space used: %d byte\n", usedBytes);
        Serial.println();
    }
    else{
        Serial.println("An Error has occurred while mounting SPIFFS");  
    }
    
    eventmgm_init();
    
    //configuration_init();

    
    wheeldb_setup();
    wheelctl_setup();

    display_init();

    #ifdef HAS_RTC
        rtc_init();
    #endif
    
    #ifdef HAS_BUTTONS
        button_init();
    #endif

    lvglctl_init();

    blectl_scan_setup();

    if (I2C_SDA > 0) {
        Wire.begin(I2C_SDA, I2C_SCL);
    }
    //i2c_bus1.scan();

    esp_sleep_enable_gpio_wakeup ();
    eventmgm_set_event(EVENTMGM_WAKEUP);  
    delay(100);
    display_set_brightness(220, 300); 
}

void loop() {
    //run event management loop, responsible for all events and loops
    eventmgm_loop();
}
#include <Wire.h>
#include "RTClib.h"
#include "rtc.h"
#include "fs.h"
#include "spiffs.h"

RTC_DS1307 rtc;

char clockstring[8];
char datestring[16];

void rtc_init(){
    if (! rtc.begin()) {
        Serial.println("Couldn't find RTC");
    }
    if (! rtc.isrunning()) {
        Serial.println("RTC is NOT running!");
    }
}

void rtc_set_time(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second) {
    rtc.adjust(DateTime(year, month, day, hour, minute, second));
}

time_t rtc_get_time(){
    DateTime now = rtc.now();
    time_t time = now.unixtime();
    return time;
}

//example function to get time in HH:MM format
char* rtc_get_clockstring(){
    struct tm info;
    time_t currenttime = rtc_get_time();
    localtime_r(&currenttime, &info);
    strftime(clockstring, sizeof(clockstring), "%H:%M", &info);
    return clockstring;
}

//example function to get date in "Wkd DD Mon YYYY" format "Mon 12 Feb 2019"
char* rtc_get_datestring(){ 
    struct tm info;
    time_t currenttime = rtc_get_time();
    localtime_r(&currenttime, &info);
    strftime(datestring, sizeof(datestring), "%a %d %b %Y", &info);
    return datestring;
}

void rtc_print_time() {
    char* timestring = rtc_get_clockstring();
    Serial.println(timestring);
}
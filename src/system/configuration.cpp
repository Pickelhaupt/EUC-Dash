
#include <Arduino.h>
#include <FS.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include "configuration.h"

config_item_t config_item;

/** @brief read configuration file and assign values to config_items */
void configuration_read_config( void ) {
  fs::File file = SPIFFS.open( MAIN_CONFIG_FILE, FILE_READ );
  if (!file) {
    log_e("Can't open file: %s!", MAIN_CONFIG_FILE );
  } else {
    StaticJsonDocument<MAIN_CONFIG_DOCSIZE> jsondoc;
    DeserializationError error = deserializeJson( jsondoc, file );
    if ( error ) {
      log_e("update check deserializeJson() failed: %s", error.c_str() );
    } else {
      config_item.fahrenheit = jsondoc["fahren"] | false;
      config_item.mmhg = jsondoc["mmhg"] | false;
      config_item.clock24h = jsondoc["clock24h"] | true;
      strlcpy( config_item.timezone_name, jsondoc["tz_name"] | DEFAULT_TIMEZONE_NAME, sizeof( config_item.timezone_name ) );
      strlcpy( config_item.timezone_rule, jsondoc["tz_name"] | DEFAULT_TIMEZONE_RULE, sizeof( config_item.timezone_rule ) );
    }
    jsondoc.clear();
  }
  file.close();
}

/** @brief save configuration file*/
void configuration_save_config( void ) {
  fs::File file = SPIFFS.open( MAIN_CONFIG_FILE, FILE_WRITE );
  if (!file) {
    log_e("Can't open file: %s!", MAIN_CONFIG_FILE );
  } else {
    StaticJsonDocument<MAIN_CONFIG_DOCSIZE> jsondoc;
    jsondoc["fahren"] = config_item.fahrenheit;
    jsondoc["mmhg"] = config_item.mmhg;
    jsondoc["clock24h"] = config_item.clock24h;
    jsondoc["tz_name"] = config_item.timezone_name;
    jsondoc["tz_rule"] = config_item.timezone_rule;
    if ( serializeJsonPretty( jsondoc, file ) == 0) {
      log_e("Failed to write config file");
    }
    jsondoc.clear(); 
  }
  file.close();
}

bool configuration_get_fahrenheit (void) {
  return config_item.fahrenheit;
}
void configuration_set_fahrenheit (bool value) {
  config_item.fahrenheit = value;
  configuration_save_config();
}
bool configuration_get_mmhg (void) {
  return config_item.mmhg;
}
void configuration_set_mmhg (bool value) {
  config_item.mmhg = value;
  configuration_save_config();
}
bool configuration_get_clock24h (void) {
  return config_item.clock24h;
}
void configuration_set_clock24h (bool value) {
  config_item.clock24h = value;
  configuration_save_config();
}
char* configuration_get_timezone_name(void) {
  return config_item.timezone_name;
}
void configuration_set_timezone_name(char* tz_name) {
  strlcpy( config_item.timezone_name, tz_name, sizeof( config_item.timezone_name ) );
  configuration_save_config();
}
char* configuration_get_timezone_rule(void) {
  return config_item.timezone_rule;
}
void configuration_set_timezone_rule(char* tz_rule) {
  strlcpy( config_item.timezone_rule, tz_rule, sizeof( config_item.timezone_rule ) );
  configuration_save_config();
}

void listFilesInDir(File dir, int numTabs = 1) {
  while (true) {
 
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files in the folder
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      listFilesInDir(entry, numTabs + 1);
    } else {
      // display zise for file, nothing for directory
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void configuration_init(){   
    if(SPIFFS.begin(true)){ 
        Serial.println("SPIFFS mounted successfully");
        
        unsigned int totalBytes = SPIFFS.totalBytes();
        unsigned int usedBytes = SPIFFS.usedBytes();
 
        Serial.println("===== File system info =====");
        Serial.print("Total space:      ");
        Serial.print(totalBytes);
        Serial.println("byte");
        Serial.print("Total space used: ");
        Serial.print(usedBytes);
        Serial.println("byte");
        Serial.println();
        // Open dir folder
        File dir = SPIFFS.open("/");
        // List file at root
        listFilesInDir(dir);
        Serial.println("initial configuration read");
        configuration_read_config();
    }
    else{
        Serial.println("An Error has occurred while mounting SPIFFS");  
    }
}


#ifndef _FILESYS_H
    #define _FILESYS_H

    #define MAIN_CONFIG_FILE "/configuration.json"
    #define DEFAULT_TIMEZONE_RULE "UTC0"
    #define DEFAULT_TIMEZONE_NAME "UTC"


    #define MAIN_CONFIG_DOCSIZE 300 //Size of all jason pairs in bytes roughly 20 chars per item name plus size of values
    typedef struct {
        bool fahrenheit = false;
        bool mmhg = false;
        bool clock24h = true;
        char timezone_rule[40] = DEFAULT_TIMEZONE_RULE;
        char timezone_name[32] = DEFAULT_TIMEZONE_NAME;
    } config_item_t;

    /** @brief initialise the SPIFFS filesystem and read configuration file*/
    void configuration_init(void);

    /** @brief get temperature unit @returns false = celsius, true = fahrenheit */
    bool configuration_get_fahrenheit (void); 
    /** @brief set temperature unit @param value false = celsius, true = fahrenheit */
    void configuration_set_fahrenheit (bool value); 
    /** @brief get barometer unit @returns false = hPa, true = mmhg */
    bool configuration_get_mmhg (void);
    /** @brief set temperature unit @param value false = hPa, true = mmhg */
    void configuration_set_mmhg (bool value);
    /** @brief get clock format @returns false = 12h, true = 24h */
    bool configuration_get_clock24h (void);
    /** @brief set clock format @param value false = 12h, true = 24h */
    void configuration_set_clock24h (bool value);
    char* configuration_get_timezone_name(void);
    void configuration_set_timezone_name(char* tz_name);
    char* configuration_get_timezone_rule(void);
    void configuration_set_timezone_rule(char* tz_rule);

#endif
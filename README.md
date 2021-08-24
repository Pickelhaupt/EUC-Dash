# EUC-Dash

**2021-08-24 Rewrite of EUC-Dash-ESP32 -- aim is to support multiple ESP32 platforms** 
Open Smart Watch is currently being worked on. Support planned for:
- TTGO t-watch
- TTGO T4

At the moment only the Dashboard and automatic BLE connection to KingSong wheels work.

## Features
Reads BLE notifications from the electric unicycle and display data on the ESP32 display
- Reads KS BLE notifications
- Full dashboard
- Non functioning Clock display
- Placeholder for settings display
- rudimentary button support

### Data read and decoded
- Current speed
- Voltage
- Current
- Total Distance traveled
- Distance traveled since power on
- Time since power on
- Power
- Battery percentage remaining
- Speed alarm settings
- Tiltback (Max speed) setting
- Max speed since power on
- Cooling fan status
- Ride mode setting
- EUC temperature
### Data displayed on dashboards
- Current speed 
- Max speed
- Wheel battery level
- Wheel max battery
- Wheel min battery
- Current
- Max current
- Max regen breaking current
- Temperature 
- Max temperature 
- Trip meter 

### Supported Wheel Models
Only supports Kingsong wheels at the moment. it autodetects the following models:
- KS14M/D/S
- KS16/KS16/S/X/XS
- KS18L/XL
- KS-S18

Gotway support is being actively worked on.

## Dependencies
### Required libraries:
Libraries are downloaded automatically by PlatformIO when compiling for the first time.
- bodmer/TFT_eSPI@^2.3.59
- lvgl/lvgl @ ^7.11.0
- bblanchon/ArduinoJson @ ^6.17.3
- adafruit/RTClib @ ^1.12.5
- evert-arias/EasyButton @ ^2.0.1

## Bugs and issues
- First draft, most functions to be ported/rewritten

## Todo
- RTC and working clock
- Settings menu
- Trip and info screens
- Gotway support
- Inmotion support
- Veteran support

## Building the project
Requires PlatformIO and driver for the USB chip in the chosen platform. for more info see: 
https://github.com/Pickelhaupt/EUC-Dash-ESP32/tree/master/src
## Connecting to the wheel
If the "connect to wheel" setting on the main setup screen is on it should connect automatically when it finds a compatible wheel when the screen is on, it will not connect when screen is off as the device is in sleep mode. However there is currently no function implemented to make it possible to choose what wheel it will connect to of there are more than one compatible wheel in range, it will simply connect to the first one it finds.

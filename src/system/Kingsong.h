/****************************************************************************
 * 2020 Jesper Ortlund
 * KingSong decoding derived from Wheellog 
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

#ifndef __KINGSONG_H
#define __KINGSONG_H

/*define constants for specific KS wheel models 
* add here when adding support for a new model
*/
#define KS_DEFAULT_MAXCURRENT   40 //maximum current draw
#define KS_DEFAULT_CRITTEMP     65 //critical internal temperature
#define KS_DEFAULT_WARNTEMP     50 //Hight internal temperature
#define KS_DEFAULT_BATTVOLT     67 //battery pack max voltage
#define KS_DEFAULT_BATTWARN     25 //remaining battery percentage warning -- 
#define KS_DEFAULT_BATT_IR      20 //internal resistance in 1/100 ohms -- 


#include "config.h"
#include "callback.h"
/**
* @brief Set the primary lights mode 
* 
* @param   mode     configitem: byte containing the desired light mode: 0x00 = on, 0x01 = off, 0x02 = ? 0x03 = ?
* 
*/
void ks_lights(byte mode);
/**
* @brief toggle wheel lock
* 
* @param   mode     configitem: bool containing the desired lock state: false = unlocked, true = locked
* 
*/
void ks_lock(void);
/**
* @brief toggle leds when toggling lights
* 
* @param   mode     configitem: byte containing the desired led state: 0x00 = on, 0x01 = off
* 
*/
void ks_led(byte mode);

/*************************************************************
    Kingsong wheel data decoder adds current values to
    the wheeldata array. Prootocol decoding from Wheellog by
    Kevin Cooper,
    would have been a lot of work without that code
    to reference.
    Should be fairly easy to adapt this to Gotway as well.
    Function is called on by the notifyCallback function in blectl
    decoded data is added to the data struct in wheelctl
    Todo:
    - Add Serial and model number
    - Add periodical polling of speed settings? Verify by
      testing with low battery
 ************************************************************/

/**
* @brief Decode a kingsong 20 byte BLE package assigned to a byte array 
* 
* @param   KSData[]     configitem: byte array containing 20 elements
* 
*/
void decodeKS(byte KSData[]);
/**
* @brief Initialise the Kingsong wheel
*/
void initks();
/**
* @brief Initialise the Kingsong BLE notification function by sending a series of requests
*/
void ks_init_notifications();

#endif /* __KINGSONG */
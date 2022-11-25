#ifndef DISPLAY_H
#define DISPLAY_H

/**
 * @file    :    display.h
 * @author  :    Shawn Nagar
 * @version :    v1.0
 * @details :    Header file used to define all time display interaction based functionality
*/

#include "time.h"
#include "common.h"

/*********Structs / Enums***********/

/*********Functions***********/

/**
 * @brief   :   Function Description: displays time on screen
 * @param   :   time_struct* - pointer to struct to store time
 * @return  :   FUNC_STATUS
 * */
FUNC_STATUS display_time(time_struct*);

/**
 * @brief   :   Function Description: displays date on screen
 * @param   :   date_struct* - pointer to struct to store date values
 * @return  :   FUNC_STATUS
 * */
FUNC_STATUS display_date(date_struct*);

/**
 * @brief   :   Function Description: Clears the screen
 * @param   :   void
 * @return  :   FUNC_STATUS
 * */
FUNC_STATUS display_reset(void);

/**
 * @brief   :   Function Description: Turns on the backlight
 * @param   :   void
 * @return  :   void
*/
void enable_backlight(void);

/**
 * @brief   :   Function Description: Turns off the backlight
 * @param   :   void
 * @return  :   void
*/
void disable_backlight(void);

/**
 * @brief   :   Function Description: Sends UART data to display
 * @param   :   uint8_t* - Pointer to buffer of data to send
 * @param   :   uint8_t - Number of bytes to send
 * @return  :   FUNC_STATUS
 * */
FUNC_STATUS send_to_display(uint8_t*, uint8_t);

#endif
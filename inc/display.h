#ifndef DISPLAY_H
#define DISPLAY_H

/**
 * @file    :    display.h
 * @author  :    Shawn Nagar
 * @version :    v1.0
 * @details :    Header file used to define all time display interaction based functionality
*/

#include "time.h"

/*********Structs / Enums***********/

/*********Functions***********/

/**
 * @brief   :   Function Description: displays time on screen
 * @param   :   time_struct* - pointer to struct to store time
 * @return  :   void
*/
void display_time(time_struct*);

/**
 * @brief   :   Function Description: displays date on screen
 * @param   :   date_struct* - pointer to struct to store date values
 * @return  :   void
*/
void display_date(date_struct*);

/**
 * @brief   :   Function Description: Clears the screen
 * @param   :   void
 * @return  :   void
*/
void display_reset(void);

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

#endif
#ifndef TIME_H
#define TIME_H

/**
 * @file    :    time.h
 * @author  :    Shawn Nagar
 * @version :    v1.0
 * @details :    Header file used to define all time calculation / determination based functionality
*/

#include <stdint.h>

#define RTC_PORT    UART_0  /**< #define in case UART needs to be changed later*/

/*********Structs / Enums***********/

/**
 * @brief   :   Struct used to define hours, min and sec
*/
typedef struct{
    uint8_t hr;
    uint8_t min;
    uint8_t sec;
}time_struct;

/**
 * @brief   :   Struct used to define days, months and years
*/
typedef struct{
    uint8_t day;
    uint8_t month;
    uint8_t year;
}date_struct;

/*********Functions***********/

/**
 * @brief   :   Function Description: Requests time from rtc via uart
 * @param   :   time_struct* - pointer to struct to store time values from rtc
 * @return  :   void
*/
void get_time(time_struct*);

/**
 * @brief   :   Function Description: Requests date from rtc via uart
 * @param   :   date_struct* - pointer to struct to store date values from rtc 
 * @return  :   void
*/
void get_date(date_struct*);

/**
 * @brief   :   Function Description: increments the time in the struct by 1 sec
 * @param   :   date_struct* - pointer to store time data to increment by 1 sec
 * @return  :   void
*/
void increment_sec(time_struct*);

#endif
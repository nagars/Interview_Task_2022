#ifndef TIME_H
#define TIME_H

/**
 * @file    :    time.h
 * @author  :    Shawn Nagar
 * @version :    v1.0
 * @details :    Header file used to define all time calculation / determination based functionality
*/

#include <stdint.h>
#include "common.h"

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
 * @param   :   void
 * @return  :   FUNC_STATUS
*/
FUNC_STATUS request_time(void);

/**
 * @brief   :   Function Description: Requests date from rtc via uart
 * @param   :   void
 * @return  :   FUNC_STATUS
*/
FUNC_STATUS request_date(void);

/**
 * @brief   :   Function Description: increments the time in the struct by 1 sec
 * @param   :   time_struct* - pointer to store time data to increment by 1 sec
 * @return  :   FUNC_STATUS
*/
FUNC_STATUS increment_sec(time_struct*);

/**
 * @brief   :   Function Description: Sends UART data to RTC
 * @param   :   uint8_t* - Pointer to buffer of data to send
 * @param   :   uint8_t - Number of bytes to send
 * @return  :   FUNC_STATUS
*/
FUNC_STATUS send_to_rtc(uint8_t*, uint8_t);

/**
 * @brief   :   Function Description: Receives data from RTC via UART
 * @param   :   uint8_t* - Pointer to rx buffer
 * @return  :   FUNC_STATUS
*/
FUNC_STATUS read_from_rtc(uint8_t* );

/**
 * @brief   :   Function Description: Receives data from RTC via UART and fills time struct
 * @param   :   date_struct* - pointer to date struct
 * @return  :   FUNC_STATUS
*/
FUNC_STATUS return_date(date_struct*);

/**
 * @brief   :   Function Description: Receives data from RTC via UART and fills time struct
 * @param   :   time_struct* - pointer to time struct
 * @return  :   FUNC_STATUS
*/
FUNC_STATUS return_time(time_struct*);

#endif
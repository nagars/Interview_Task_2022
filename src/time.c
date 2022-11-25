#include "../inc/time.h"

static uint8_t rtc_data_ready_flag;    /**<Flag to track if data is available on UART0*/

/**
 * @brief   :   Function Description: Requests time from rtc via uart
 * @param   :   time_struct* - pointer to struct to store time values from rtc
 * @return  :   void
*/
void get_time(time_struct*){

    /**<Check for NULL pointer*/

    /**<Clear struct*/

    /**<Fill buffer to be sent via uart to RTC*/

    /**<Transmit to RTC*/

    /**<Wait until data is available in uart buffer*/

    /**<Read UART data from rtc*/

    /**<Fill struct*/
}

/**
 * @brief   :   Function Description: Requests date from rtc via uart
 * @param   :   date_struct* - pointer to struct to store date values from rtc 
 * @return  :   void
*/
void get_date(date_struct*){

     /**<Check for NULL pointer*/

    /**<Clear struct*/

    /**<Fill buffer to be sent via uart to RTC*/

    /**<Transmit to RTC*/

    /**<Wait until data is available in uart buffer*/

    /**<Read UART data from rtc*/

    /**<Fill struct*/

}

/**
 * @brief   :   Function Description: increments the time in the struct by 1 sec
 * @param   :   date_struct* - pointer to store time data to increment by 1 sec
 * @return  :   void
*/
void increment_sec(time_struct*){

    /**<Check for NULL pointer*/

    /**<Increment seconds*/

    /**<If seconds exceeds 59, reset sec and increment min*/

    /**<If min exceeds 59, reset min, sec and increment hr*/

    /**<If hr exceeds 99, disable counter*/

}

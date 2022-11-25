#include "../inc/time.h"

uint8_t rtc_data_ready_flag;    /**<Flag to track if data is available from RTC*/

/**
 * @brief   :   Function Description: Requests time from rtc via uart
 * @param   :   void
 * @return  :   FUNC_STATUS
*/
FUNC_STATUS request_time(void){

    /**<Fill buffer to be sent via uart to RTC*/
    uint8_t tx_buf[2] = {0};
    tx_buf[0] = 0xFE;
    tx_buf[1] = 0x01;

    /**<Transmit to RTC*/
    if(send_to_rtc(tx_buf, sizeof(tx_buf)) == FUNC_FAILURE){
        return FUNC_FAILURE;
    }

    return FUNC_SUCCESS;
}

/**
 * @brief   :   Function Description: Requests date from rtc via uart
 * @param   :   void 
 * @return  :   FUNC_STATUS
*/
FUNC_STATUS request_date(void){

    /**<Fill buffer to be sent via uart to RTC*/
    uint8_t tx_buf[2] = {0};
    tx_buf[0] = 0xFE;
    tx_buf[1] = 0x02;

    /**<Transmit to RTC*/
    if(send_to_rtc(tx_buf, sizeof(tx_buf)) == FUNC_FAILURE){
        return FUNC_FAILURE;
    }

    return FUNC_SUCCESS;

}

/**
 * @brief   :   Function Description: increments the time in the struct by 1 sec
 * @param   :   time_struct* - pointer to store time data to increment by 1 sec
 * @return  :   FUNC_STATUS
*/
FUNC_STATUS increment_sec(time_struct* p_time){

    /**<Check for NULL pointer*/
    if(p_time == NULL){
        error = NULL_POINTER_ERR;       /**<Set error number*/
        return FUNC_FAILURE;     
    }

    /**<Check for max value that can be displayed*/
    /**<If hr exceeds 99, disable counter*/
    if(p_time->hr >= 99){
        error = MAX_COUNT_VAL_ERR;      /**<Set error number*/
        return FUNC_FAILURE;
    }

    /**<Increment seconds*/
    /**<If seconds exceeds 59, reset sec and increment min*/
    if(p_time->sec >= 59){
        p_time->sec = 0;
        (p_time->min)++;
    }else{
        (p_time->sec)++;
    }

    /**<If min exceeds 59, reset min, sec and increment hr*/
    if(p_time->min >= 59){
        p_time->min = 0;
        p_time->sec = 0;
        (p_time->hr)++;
    }else{
        (p_time->min)++;
    }

    return FUNC_SUCCESS;
}

/**
 * @brief   :   Function Description: Sends UART data to RTC
 * @param   :   uint8_t* - Pointer to buffer of data to send
 * @param   :   uint8_t - Number of bytes to send
 * @return  :   FUNC_STATUS
*/
FUNC_STATUS send_to_rtc(uint8_t* p_buff, uint8_t num_bytes){

    /**<Check for NULL pointer*/
    if(p_buff == NULL){
        error = NULL_POINTER_ERR;       /**<Set error number*/
        return FUNC_FAILURE;     
    }

    /**<Transmit data one byte at a time*/
    for(uint8_t n = 0; n < num_bytes, n++){
        UART_write(RTC_PORT, p_buff[n]);
    }

    return FUNC_SUCCESS;
}

/**
 * @brief   :   Function Description: Receives data from RTC via UART
 * @param   :   uint8_t* - Pointer to rx buffer
 * @return  :   FUNC_STATUS
*/
FUNC_STATUS read_from_rtc(uint8_t* p_buff){

    /**<Check for NULL pointer*/
    if(p_buff == NULL){
        error = NULL_POINTER_ERR;       /**<Set error number*/
        return FUNC_FAILURE;     
    }

    /**<Get number of bytes to read*/
    uint8_t num_byte_avail = UART_Bytes_Available(RTC_PORT);

    for(uint8_t n = 0; n < num_bytes_avail; n++){
        /**<Read one character and place in buffer*/
        p_buff[n] = UART_read_byte(RTC_PORT);

        /**<If number of characters to read exceeds buffer size, exit with error*/
        if(n >= UART_RX_BUF_SIZE){
            error = UART_RX_BUFFER_FULL_ERR;
            return FUNC_STATUS;
        }
    }

    return FUNC_SUCCESS;
}
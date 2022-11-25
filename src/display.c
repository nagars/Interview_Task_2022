#include "../inc/display.h"

/**
 * @brief   :   Function Description: displays timeas HH:MM:SS on screen
 * @param   :   time_struct* - pointer to struct to store time
 * @return  :   FUNC_STATUS
*/
FUNC_STATUS display_time(time_struct* p_time){

    /**<Check for NULL pointer*/
    if(p_time == NULL){
        error = NULL_POINTER_ERR;       /**<Set error number*/
        return FUNC_FAILURE;            
    }

    /**<Validate data*/
    if(p_time->hr > 23){
        error = INVALID_TIME_ERR;       /**<Set error number*/
        return FUNC_FAILURE;   
    }

    if(p_time->min > 59){
        error = INVALID_TIME_ERR;       /**<Set error number*/
        return FUNC_FAILURE;   
    }

    if(p_time->sec > 59){
        error = INVALID_TIME_ERR;       /**<Set error number*/
        return FUNC_FAILURE;   
    }

    /**<Fill buffer to send to Display via UART*/
    uint8_t tx_buf[5] = {0};

    /**<Fill header*/
    tx_buf[0] = 0xFC;
    tx_buf[1] = 0xDD;

    tx_buf[2] = p_time->hr; 
    tx_buf[3] = p_time->min; 
    tx_buf[4] = p_time->sec; 

    /**<Transmit*/
    if(send_to_display(tx_buf, sizeof(tx_buf)) == FUNC_FAILURE){
        return FUNC_FAILURE;
    }
    
    return FUNC_SUCCESS;
}

/**
 * @brief   :   Function Description: displays date as DD:MM:YY on screen
 * @param   :   date_struct* - pointer to struct to store date values
 * @return  :   void
*/
void display_date(date_struct* p_date){
   
    /**<Check for NULL pointer*/
    if(p_date == NULL){
        error = NULL_POINTER_ERR;       /**<Set error number*/
        return FUNC_FAILURE;            
    }

    /**<Validate data*/
    if(p_date->month > 12){             /**<Num of months cant exceed 12*/
        error = INVALID_DATE_ERR;       /**<Set error number*/
        return FUNC_FAILURE;   
    }

    if(p_date->year > 99){              /**<Num of years cant exceed double digits*/
        error = INVALID_DATE_ERR;       /**<Set error number*/
        return FUNC_FAILURE;   
    }

    switch(p_date->month){
        case 2:                                 /**<28 days in Feb*/
            if(p_date->day > 28){
                error = INVALID_DATE_ERR;       /**<Set error number*/
                return FUNC_FAILURE;   
            }
            break;
        case 1:                                 /**<31 days in a month*/
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
        
            if(p_date->day > 31){
                error = INVALID_DATE_ERR;       /**<Set error number*/
                return FUNC_FAILURE;   
            }
            break;

        case 4:
        case 6:
        case 9:
        case 11:                                /**<30 days in a month*/
            if(p_date->day > 30){
                error = INVALID_DATE_ERR;       /**<Set error number*/
                return FUNC_FAILURE;   
            }
            break;
        
        default:
            break;
    }

    /**<Fill buffer to send to Display via UART*/
    uint8_t tx_buf[5] = {0};

    /**<Fill header*/
    tx_buf[0] = 0xFC;
    tx_buf[1] = 0xDD;

    tx_buf[2] = p_date->day; 
    tx_buf[3] = p_date->month; 
    tx_buf[4] = p_date->year; 

    /**<Transmit*/
    if(send_to_display(tx_buf, sizeof(tx_buf)) == FUNC_FAILURE){
        return FUNC_FAILURE;
    }
    
    return FUNC_SUCCESS;
}

/**
 * @brief   :   Function Description: Clears the screen
 * @param   :   void
 * @return  :   FUNC_STATUS
*/
FUNC_STATUS display_reset(void){

    /**<Fill buffer to send to Display via UART*/
    uint8_t tx_buf[2] = {0};

    /**<Fill header*/
    tx_buf[0] = 0xFC;
    tx_buf[1] = 0xDC;

    /**<Transmit*/
    if(send_to_display(tx_buf, sizeof(tx_buf)) == FUNC_FAILURE){
        return FUNC_FAILURE;
    }
    
    return FUNC_SUCCESS;

}

/**
 * @brief   :   Function Description: Turns on the backlight
 * @param   :   void
 * @return  :   void
*/
void enable_backlight(void){

    /**<set GPIO enable pin (high)*/
    GPIO_state_set(PORT_B, BACKLT_GPIO_OUT, 1);
}

/**
 * @brief   :   Function Description: Turns off the backlight
 * @param   :   void
 * @return  :   void
*/
void disable_backlight(void){

    /**<Clear GPIO enable pin (low)*/
    GPIO_state_set(PORT_B, BACKLT_GPIO_OUT, 0);

}

/**
 * @brief   :   Function Description: Sends UART data to display
 * @param   :   uint8_t* - Pointer to buffer of data to send
 * @param   :   uint8_t - Number of bytes to send
 * @return  :   FUNC_STATUS
*/
FUNC_STATUS send_to_display(uint8_t* p_buff, uint8_t num_bytes){

    /**<Check for NULL pointer*/
    if(p_buff == NULL){
        error = NULL_POINTER_ERR;       /**<Set error number*/
        return FUNC_FAILURE;     
    }

    for(uint8_t n = 0; n < num_bytes, n++){
        UART_write(DISPLAY_PORT, p_buff[n]);
    }

    return FUNC_SUCCESS;
}
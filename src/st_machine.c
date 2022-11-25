#include "../inc/st_machine.h"

st_para_struct st_state_data;     /**<Struct containing state machine flags/data*/
(*p_func_state)(void);          /**<Global function pointer for state machine*/

extern uint8_t rtc_data_ready_flag;    /**<Flag to track if data is available from RTC*/

/**
 * @brief   :   Function Description: Transitions from current state to Time Mode State
 * @param   :   void
 * @return  :   void
*/
void trans_to_TimeMode(void){

    /**<Change state variable*/

    /**<While loop*/

    /**<Request new data from RTC*/

    /**<Check for new data from RTC*/

        /**<If available, update display*/

    /**<Check for Mode button pressed*/

        /**<Change state machine pointer to next state (Date mode)*/

        /**<Return*/

    /**<loop*/
}

/**
 * @brief   :   Function Description: Transitions from current state to Date Mode State
 * @param   :   void
 * @return  :   void
*/
void trans_to_DateMode(void){

    /**<Change state variable*/

    /**<While loop*/

    /**<Request data from RTC*/

    /**<Check for new data*/
        
        /**<Update display*/

    /**<Check for Mode button pressed*/

        /**<Change state machine pointer to next state (Stop watch mode)*/

        /**<Return*/

    /**<loop*/

}

/**
 * @brief   :   Function Description: Transitions from current state to StopWatch Mode Reset State
 * @param   :   void
 * @return  :   void
*/
void trans_to_StopWatchMode_Reset(void){

    /**<Change state variable*/

    /**<Reset Display*/

    /**<While loop*/

    /**<Check for Start/stop button pressed*/

        /**<Change state machine pointer to next state (Counting mode)*/

        /**<Return*/

    /**<Check for Mode button pressed*/

        /**<Change state machine pointer to next state (Time Mode)*/

        /**<Return*/

    /**<Loop*/
}

/**
 * @brief   :   Function Description: Transitions from current state to StopWatch Mode Counting State
 * @param   :   void
 * @return  :   void
*/
void trans_to_StopWatchMode_Counting(void){

    /**<Change state variable*/

    /**<While loop*/

    /**<Check for data from RTC*/

        /**<Increment counter
         * The RTC periodically (Every 1 sec) sends data via UART. I am using that as a 1 sec
         * timer. When new data comes on UART, I assume a second has passed and increment the counter
        */

    /**<Check for Start/stop button pressed*/

        /**<Change state machine pointer to next state (paused mode)*/

        /**<Return*/

    /**<Check for reset button pressed*/

        /**<Change state machine pointer to next state (reset mode)*/

        /**<Return*/

    /**<Check for Mode button pressed*/

        /**<Change state machine pointer to next state (Time mode)*/

        /**<Return*/

    /**<Loop*/
}

/**
 * @brief   :   Function Description: Transitions from current state to StopWatch Mode Paused State
 * @param   :   void
 * @return  :   void
*/
void trans_to_StopWatchMode_Paused(void){

    /**<Change state variable*/

    /**<While loop*/

    /**<Check for Start/stop button pressed*/

        /**<Change state machine pointer to next state (Counting mode)*/

        /**<Return*/

     /**<Check for reset button pressed*/

        /**<Change state machine pointer to next state (reset mode)*/

        /**<Return*/

    /**<Check for Mode button pressed*/

        /**<Change state machine pointer to next state (TIme mode)*/

        /**<Return*/

    /**<Loop*/

}


/**
 * @brief   :   Function Description: ISR called when data is available on any UART
 * @param   :   UART_e uart_port: Enum for which UART port to use
 * @return  :   void
*/
__ISR__ void UART_receive_event(UART_e uart_port){

    /**<Check if data is available on UART0 (RTC)*/

        /**<Set flag based on current state machine state
         * I chose to use flags rather than directly fill the structs with
         * updated time or date data as the ISR maybe called when the main program
         * is operating on one of those structs
         * 
         * Ideally one should be able to disable ISR's in critical code
        */

       rtc_data_ready_flag = TRUE;

    /**<Check if data is available on UART1 (DISPLAY)*/
    /**<Note: According to current requirements, should never happen*/

    return;
}

/**
 * @brief   :   Function Description: ISR called when a transition occurs on a GPIO
 * @param   :   port_e gpio_port: enum for GPIO Port
 * @param   :   uint8_t pin: Pin number that triggered interrupt 
 * @return  :   void
*/
__ISR__ void GPIO_input_change_event(port_e gpio_port, uint8_t pin){

    /**<Check which GPIO triggered the ISR*/

        /**<If Port A, GPIO 0, set / clear backlight (Port B, GPIO 0)*/

        /**<If Port A, GPIO 1, set/clear Mode button flag*/

        /**<If Port A, GPIO 2, set/clear start/stop button flag*/

        /**<If Port A, GPIO 3, set/clear reset button flag*/

    return;

}
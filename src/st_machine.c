#include "../inc/st_machine.h"

static st_para_struct st_state_data; /**<Struct containing state machine flags/data*/
void (*p_func_state)(void);          /**<Global function pointer for state machine*/

static uint8_t rtc_data_ready_flag;     /**<Flag to track if data is available from RTC*/
static uint8_t rtc_data_requested_flag; /**<Tracks if rtc data request was sent to rtc*/
static uint8_t backlight_active_flag;   /**<Tracks if backlight is on or not*/

static time_struct time; /**<Struct to store rtc time / stopwatch counter*/
static date_struct date; /**<Struct to store rtc date*/

/**
 * @brief   :   Function Description: Transitions from current state to Time Mode State
 * @param   :   void
 * @return  :   void
 */
void trans_to_TimeMode(void)
{

    /**<Change state variable*/
    st_state_data.st_state = TIME_MODE;

    /**<Clear flags*/
    rtc_data_requested_flag = FALSE;
    rtc_data_ready_flag = FALSE;

    /**<While loop*/
    while (1)
    {

        /**<Check if any request for data is pending*/
        if (rtc_data_requested_flag == FALSE)
        {
            /**Request new time data*/
            request_time();
            /**<Set data requested flag*/
            rtc_data_requested_flag = TRUE;
        }

        /**<Check for new data from RTC*/
        if (rtc_data_ready_flag == TRUE)
        {

            /**<If available, read data*/
            return_time(&time);

            /**<Update display*/
            display_time(&time);

            /**<Request fulfilled, reset data requested and data ready flags*/
            rtc_data_requested_flag = FALSE;
            rtc_data_ready_flag = FALSE;
        }

        /**<Check for Mode button pressed*/
        if (st_state_data.modebutton_event == TRUE){

            /**<Change state machine pointer to next state (Date mode)*/
            p_func_state = trans_to_DateMode;

            /**<Clear mode button event flag*/
            st_state_data.modebutton_event = FALSE;

            /**<Return*/
            return;
        }

    } /**<loop*/

    return;
}

/**
 * @brief   :   Function Description: Transitions from current state to Date Mode State
 * @param   :   void
 * @return  :   void
 */
void trans_to_DateMode(void)
{

    /**<Change state variable*/
    st_state_data.st_state = DATE_MODE;

    /**<Clear flags*/
    rtc_data_requested_flag = FALSE;
    rtc_data_ready_flag = FALSE;

    /**<While loop*/
    while (1)
    {

        /**<Check if any request for data is pending*/
        if (rtc_data_requested_flag == FALSE)
        {

            /**Request new time data*/
            request_date();
            /**<Set data requested flag*/
            rtc_data_requested_flag = TRUE;
        }

        /**<Check for new data from RTC*/
        if (rtc_data_ready_flag == TRUE)
        {

            /**<If available, read data*/
            return_date(&date);

            /**<Update display*/
            display_date(&date);

            /**<Request fulfilled, reset data requested and data ready flags*/
            rtc_data_requested_flag = FALSE;
            rtc_data_ready_flag = FALSE;
        }

        /**<Check for Mode button pressed*/
        if (st_state_data.modebutton_event == TRUE){
            /**<Change state machine pointer to next state (Stop watch mode)*/
            p_func_state = trans_to_StopWatchMode_Reset;

            /**<Clear mode button event flag*/
            st_state_data.modebutton_event = FALSE;

            /**<Return*/
            return;
        }

    } /**<loop*/

    return;
}

/**
 * @brief   :   Function Description: Transitions from current state to StopWatch Mode Reset State
 * @param   :   void
 * @return  :   void
 */
void trans_to_StopWatchMode_Reset(void)
{

    /**<Change state variable*/
    st_state_data.st_state = STOPWATCH_MODE_RESET;

    /**<clear time struct and Update display*/
    memset(&time, 0, sizeof(time_struct));
    display_time(&time);

    /**<Clear Start/stop button flags*/
    st_state_data.startbutton_event = FALSE;
    st_state_data.stopbutton_event = FALSE;

    /**<While loop*/
    while (1)
    {

        /**<Check for Start/stop button pressed*/
        if (st_state_data.startbutton_event == TRUE)
        {
            /**<Change state machine pointer to next state (Counting mode)*/
            p_func_state = trans_to_StopWatchMode_Counting;

            /**<Return*/
            return;
        }

        /**<Check for Mode button pressed*/
        if (st_state_data.modebutton_event == TRUE){

            /**<Change state machine pointer to next state (Time mode)*/
            p_func_state = trans_to_TimeMode;

            /**<Clear mode button event flag*/
            st_state_data.modebutton_event = FALSE;

            /**<Return*/
            return;
        }

    } /**<Loop*/

}

/**
 * @brief   :   Function Description: Transitions from current state to StopWatch Mode Counting State
 * @param   :   void
 * @return  :   void
 */
void trans_to_StopWatchMode_Counting(void)
{

    /**<Change state variable*/
    st_state_data.st_state = STOPWATCH_MODE_COUNTING;

    /**<Create temp buffer for flushing uart buffer*/
    uint8_t uart_rx[UART_RX_BUF_SIZE] = {0};

    /**<While loop*/
    while (1){

        /**<Check for data from RTC*/
        if (rtc_data_ready_flag == TRUE)
        { /**<Should happen automatically every 1 sec*/

            /**<Increment counter
             * The RTC periodically (Every 1 sec) sends data via UART. I am using that as a 1 sec
             * timer. When new data comes on UART, I assume a second has passed and increment the counter
             */
            increment_sec(&time);

            /**<Read from UART buffer to flush it. Discard data*/
            read_from_rtc(uart_rx);

            /**<Clear rtc data ready flag*/
            rtc_data_ready_flag = FALSE;
        }

        /**<Check for Start/stop button pressed*/
        if (st_state_data.stopbutton_event == TRUE)
        {

            /**<Change state machine pointer to next state (paused mode)*/
            p_func_state = trans_to_StopWatchMode_Paused;

            /**<Return*/
            return;
        }

        /**<Check for reset button pressed*/
        if (st_state_data.resetbutton_event == TRUE){

            /**<Change state machine pointer to next state (reset mode)*/
            p_func_state = trans_to_StopWatchMode_Reset;

            /**<Clear resetbutton flag*/
            st_state_data.resetbutton_event = FALSE;

            /**<Return*/
            return;
        }

        /**<Check for Mode button pressed*/
        if (st_state_data.modebutton_event == TRUE){

            /**<Change state machine pointer to next state (Time mode)*/
            p_func_state = trans_to_TimeMode;

            /**<Clear mode button event flag*/
            st_state_data.modebutton_event = FALSE;

            /**<Return*/
            return;
        }   

    } /**<Loop*/
}

/**
 * @brief   :   Function Description: Transitions from current state to StopWatch Mode Paused State
 * @param   :   void
 * @return  :   void
 */
void trans_to_StopWatchMode_Paused(void)
{
    /**<Change state variable*/
    st_state_data.st_state = STOPWATCH_MODE_PAUSED;

    while(1){/**<While loop*/

        /**<Check for Start/stop button pressed*/
        if(st_state_data.startbutton_event == TRUE){

            /**<Change state machine pointer to next state (Counting mode)*/
            p_func_state = trans_to_StopWatchMode_Counting;

            /**<Return*/
            return;
        }

         /**<Check for reset button pressed*/
        if (st_state_data.resetbutton_event == TRUE){

            /**<Change state machine pointer to next state (reset mode)*/
            p_func_state = trans_to_StopWatchMode_Reset;

            /**<Clear resetbutton flag*/
            st_state_data.resetbutton_event = FALSE;

            /**<Return*/
            return;
        }

       /**<Check for Mode button pressed*/
        if (st_state_data.modebutton_event == TRUE){

            /**<Change state machine pointer to next state (Time mode)*/
            p_func_state = trans_to_TimeMode;

            /**<Clear mode button event flag*/
            st_state_data.modebutton_event = FALSE;

            /**<Return*/
            return;
        }   

    }/**<Loop*/
}

/**
 * @brief   :   Function Description: ISR called when data is available on any UART
 * @param   :   UART_e uart_port: Enum for which UART port to use
 * @return  :   void
 */
__ISR__ void UART_receive_event(UART_e uart_port)
{

    /**<Check if data is available on UART0 (RTC)*/
    if (uart_port == RTC_PORT)
    {
        /**<Set flag based on current state machine state
         * I chose to use flags rather than directly fill the structs with
         * updated time or date data as the ISR maybe called when the main program
         * is operating on one of those structs
         *
         * Ideally one should be able to disable ISR's in critical code
         */

        rtc_data_ready_flag = TRUE;
    }

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
__ISR__ void GPIO_input_change_event(port_e gpio_port, uint8_t pin)
{

    /**<Check which GPIO port triggered the ISR*/
    if (gpio_port == PORT_A)
    {

        switch (pin)
        {

        case LIGHT_GPIO_IN:
            /**<If Port A, GPIO 0, set / clear backlight (Port B, GPIO 0)*/
            if (backlight_active_flag == TRUE)
            {
                /**<Disable backlight*/
                disable_backlight();

                /**<Clear flag*/
                backlight_active_flag = FALSE;
            }
            else if (backlight_active_flag == FALSE)
            {
                /**<Enable backlight*/
                enable_backlight();

                /**<Set flag*/
                backlight_active_flag = TRUE;

            }

            break;

        case MODE_GPIO_IN:
            /**<If Port A, GPIO 1, set/clear Mode button flag*/
            st_state_data.modebutton_event = TRUE;

            break;

        case START_STOP_GPIO_IN:
            /**<If Port A, GPIO 2, set/clear start/stop button flag*/
            if (st_state_data.startbutton_event == FALSE)
            { /**<Assumed stopwatch is in reset or paused*/
                st_state_data.startbutton_event = TRUE;
                st_state_data.stopbutton_event = FALSE;
            }
            else if (st_state_data.stopbutton_event == FALSE)
            { /**<Assumed stop watch is counting*/
                st_state_data.startbutton_event = FALSE;
                st_state_data.stopbutton_event = TRUE;
            }

            break;

        case RESET_GPIO_IN:
            /**<If Port A, GPIO 3, set/clear reset button flag*/
            st_state_data.resetbutton_event = TRUE;

            break;

        default:
            break;
        }
    }

    return;
}
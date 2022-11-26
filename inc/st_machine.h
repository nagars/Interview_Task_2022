#ifndef ST_MACHINE_H
#define ST_MACHINE_H

/**
 * @file    :    st_machine.h
 * @author  :    Shawn Nagar
 * @version :    v1.0
 * @details :    Header file used to define structs and function pointers required for the state machined
*/

#include "time.h"
#include "display.h"
#include "common.h"

extern void (*p_func_state)(void);           /**<Global function pointer for state machine*/

/*********Structs / Enums***********/

/**
 * @brief   :   Enum used to track the current state of the state machine
*/
typedef enum{
    TIME_MODE,
    DATE_MODE,
    STOPWATCH_MODE_RESET,
    STOPWATCH_MODE_COUNTING,
    STOPWATCH_MODE_PAUSED,
}ST_MACHINE_STATE;

/**
 * @brief   :   Struct used to define flags / parameters required by the state machine
*/
typedef struct{
    uint8_t modebutton_event;
    uint8_t stopbutton_event;
    uint8_t startbutton_event;
    uint8_t resetbutton_event;
    ST_MACHINE_STATE st_state;
}st_para_struct;


/*********Functions***********/

/**
 * @brief   :   Function Description: Transitions from current state to Time Mode State
 * @param   :   void
 * @return  :   void
*/
void trans_to_TimeMode(void);

/**
 * @brief   :   Function Description: Transitions from current state to Date Mode State
 * @param   :   void
 * @return  :   void
*/
void trans_to_DateMode(void);

/**
 * @brief   :   Function Description: Transitions from current state to StopWatch Mode Reset State
 * @param   :   void
 * @return  :   void
*/
void trans_to_StopWatchMode_Reset(void);

/**
 * @brief   :   Function Description: Transitions from current state to StopWatch Mode Counting State
 * @param   :   void
 * @return  :   void
*/
void trans_to_StopWatchMode_Counting(void);

/**
 * @brief   :   Function Description: Transitions from current state to StopWatch Mode Paused State
 * @param   :   void
 * @return  :   void
*/
void trans_to_StopWatchMode_Paused(void);

#endif
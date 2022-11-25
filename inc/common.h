#ifndef COMMON_H
#define COMMON_H

/**
 * @file    :    common.h
 * @author  :    Shawn Nagar
 * @version :    v1.0
 * @details :    Header file used to define common definitions and functions
*/

extern ERRNO error;     /**<Global error number variable. Set upon error, else 0*/

#define DISPLAY_PORT    UART_1      /**< #define in case UART needs to be changed later*/
#define RTC_PORT        UART_0      /**< #define in case UART needs to be changed later*/

#define DISPLAY_BAUD    9600        /**<Baud rate of Display uart*/
#define RTC_BAUD        9600        /**<Baud rate of RTC Uart*/

/**<Input GPIO pins defined on Port A*/
#define LIGHT_GPIO_IN           0   /**<Input for backlight enable/disable button*/
#define MODE_GPIO_IN            1   /**<Input for Mode selection button*/
#define START_STOP_GPIO_IN      2   /**<Input for Start/Stop stopwatch button*/
#define RESET_GPIO_IN           3   /**<Input for Reset stopwatch button*/

/**<Output GPIO pins defined on Port B*/
#define BACKLT_GPIO_OUT         0   /**<Output for enabling / disabling the display backlight*/

/**<GPIO role definitions*/
#define OUTPUT  0       /**<GPIO is defined as output type*/
#define INPUT   1       /**<GPIO is defined as input type*/

/**
 * @brief   : Enum to store return value of functions
*/
typedef enum{
    FUNC_SUCCESS = 0,
    FUNC_FAILURE = -1,
}FUNC_STATUS;

typedef enum{
    NULL_POINTER_ERR,
    INVALID_TIME_ERR,
    INVALID_DATE_ERR,
}ERRNO;

#endif


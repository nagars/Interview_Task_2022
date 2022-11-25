#ifndef COMMON_H
#define COMMON_H

/**
 * @file    :    common.h
 * @author  :    Shawn Nagar
 * @version :    v1.0
 * @details :    Header file used to define common definitions and functions
*/

#define DISPLAY_PORT    UART_1      /**< #define in case UART needs to be changed later*/
#define RTC_PORT        UART_0      /**< #define in case UART needs to be changed later*/

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
#endif
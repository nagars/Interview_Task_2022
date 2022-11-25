#include "inc/st_machine.h"

int main (void){

    /**<System Initialisations*/

    /**<Peripheral Initialisations*/
    
    /**<Initialise GPIOs*/
    GPIO_init(PORT_B, BACKLT_GPIO_OUT, OUTPUT); /**<GPIO0 on PortB defined as output to control backlight of display*/
    GPIO_init(PORT_A, LIGHT_GPIO_IN, INPUT);    /**<GPIO0 on Port A defined as input for Light button*/
    GPIO_init(PORT_A, MODE_GPIO_IN, INPUT);    /**<GPIO1 on Port A defined as input for Mode button*/
    GPIO_init(PORT_A, START_STOP_GPIO_IN, INPUT);    /**<GPIO0 on Port A defined as input for start/stop button*/
    GPIO_init(PORT_A, RESET_GPIO_IN, INPUT);    /**<GPIO0 on Port A defined as input for Reset button*/

    /**<State machine initialisation*/
    p_func_state = trans_to_TimeMode(); /**<Default mode on boot is Time Mode*/

    while(1){
        /**<Enter state machine*/
        p_func_state();
    }

}
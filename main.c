#include "inc/st_machine.h"

st_para_struct st_state_data;     /**<Struct containing state machine flags/data*/
(*p_func_state)(void);      /**<Global function pointer for state machine*/

int main (void){

    /**<System Initialisations*/

    /**<Peripheral Initialisations*/

    /**<State machine initialisation*/
    p_func_state = trans_to_TimeMode();

    while(1){
        /**<Enter state machine*/
        p_func_state();
    }

}
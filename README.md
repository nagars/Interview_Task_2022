## Description:
Temporary repository for xxx company interview task. 

## Objective: 
Design the firmware for a watch in c

## Feature list:
1. 3 Modes of operation
    1. Modes are implemented through a state machine
    2. State transitions occur through a Mode button
2. Modes are defined as follows:
    1. Time: Display of HH:MM:SS. Chosen by default
    2. Date: Display of DD:MM:YY.
    3. Stop Watch: Display of HH:MM:SS. 
        1. Counter is Started / Stopped by Start/stop button.
        2. Reset to 0 by reset button.
3. Reset button and start/stop button are disabled in Time and Date modes
4. Back-light can be enabled / disabled by Light button

## Assumptions:
1. RTC broadcasts time every 1 sec unless specifically requested
2. GPIO ISR takes GPIO port and pin as a parameter to easily determine which GPIO triggered the interrupt
3. UART ISR takes the UART port as a parameter to easily determine which UART triggered the interrupt
4. All input GPIO's trigger ISR's by default
5. GPIO interrupts are only triggered on a rising signal


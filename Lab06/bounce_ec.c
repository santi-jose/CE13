//Jose Santiago jlsantia@ucsc.edu
// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>


int main(void)
{
    BOARD_Init();

    
    printf("Welcome to CRUZID's bounce ec.  Compiled at %s %s",__DATE__,__TIME__);
    
    // Configure Timer 1 and ADC :


    while (1);
}

/**
 * This is the interrupt for the Timer1 peripheral. 
 */
void __ISR(_TIMER_1_VECTOR, IPL4AUTO) Timer1Handler(void)
{
    // Clear the interrupt flag.
    INTClearFlag(INT_T1);


}

/**
 * This is the ISR for the ADC1 peripheral.
 */
void __ISR(_ADC_VECTOR, IPL2AUTO) AdcHandler(void)
{
    // Clear the interrupt flag.
    INTClearFlag(INT_AD1);


}
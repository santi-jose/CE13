// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries
#include "Buttons.h"
#include "Leds.h"

//user variables
static uint8_t buttonEvents;

int main(void)
{
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_256, 0xFFFF);

    // Set up the timer interrupt with a priority of 4.
    INTClearFlag(INT_T1);
    INTSetVectorPriority(INT_TIMER_1_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_1_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T1, INT_ENABLED);

    ButtonsInit();
    LEDS_INIT();

//    while (1) {
//        int button_states = BUTTON_STATES();
//        LEDS_SET(button_states);
//    }

    while (1) {
        if (buttonEvents) {
            if (buttonEvents & BUTTON_EVENT_1UP) {
                puts("BUTTON_EVENT_1UP");
            }
            if (buttonEvents & BUTTON_EVENT_1DOWN) {
                puts("BUTTON_EVENT_1DOWN");
            }
            buttonEvents = BUTTON_EVENT_NONE;
        }
    }
    

    while (1);
}

/**
 * This is the interrupt for the Timer1 peripheral. It checks for button events and stores them in a
 * module-level variable.
 */
void __ISR(_TIMER_1_VECTOR, IPL4AUTO) Timer1Handler(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 4;

    // Check for events.
    buttonEvents = ButtonsCheckEvents(BUTTON_STATES());
}
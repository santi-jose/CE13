//Jose Santiago jlsantia@ucsc.edu

// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"
#include "Leds.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>
#include <stdio.h>


//macros
#define LEFT 2
#define RIGHT -2

//struct to store TimerResult variable

struct TimerResult {
    uint8_t event;
    uint8_t value;
};

static struct TimerResult Timer_1;

int main(void)
{
    BOARD_Init();


    printf("Welcome to jlsantia's bounce switch.  Compiled at %s %s\n", __DATE__, __TIME__);

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_8, 0xFFFF);

    // Set up the timer interrupt with a priority of 4.
    INTClearFlag(INT_T1);
    INTSetVectorPriority(INT_TIMER_1_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_1_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T1, INT_ENABLED);


    //state variable to store states with bouncing LED
    int state = LEFT;
    LEDS_INIT();
    uint8_t Leds_Get;
    LEDS_SET(0b00000001);
    
    
    
    while (1) {
        if (Timer_1.event == TRUE) {
            Leds_Get = LEDS_GET();
                if (Leds_Get == 0b10000000) { //if at the last light switch directions
                state = RIGHT;
                Leds_Get = Leds_Get >> 1;
                LEDS_SET(Leds_Get);
            } else if (Leds_Get == 0b00000001) {//if at the first light switch directions
                state = LEFT;
                Leds_Get = Leds_Get << 1;
                LEDS_SET(Leds_Get);
            } else {    //else go the same direction
                if (state == RIGHT) {
                    Leds_Get = Leds_Get >> 1;
                    LEDS_SET(Leds_Get);
                }
                if (state == LEFT) {
                    Leds_Get = Leds_Get <<1;
                    LEDS_SET(Leds_Get);
                }
            }
            Timer_1.event = FALSE;  //clear event flag
        }
    }

    
    
//    uint8_t get_result;
//
//    if (get_result == 0xCC) {
//        printf("LEDS_GET() test 1/4 passed\n");
//    } else {
//        printf("LEDS_GET() test 1/4 failed\n");
//    }
//    int i;
//    for (i = 0; i < 10000000; i++);
//    LEDS_SET(0xDD);
//    get_result = LEDS_GET();
//    if (get_result == 0xDD) {
//        printf("LEDS_GET() test 2/4 passed\n");
//    } else {
//        printf("LEDS_GET() test 2/4 failed\n");
//    }
//    for (i = 0; i < 10000000; i++);
//    LEDS_SET(0);
//    get_result = LEDS_GET();
//    if (get_result == 0) {
//        printf("LEDS_GET() test 3/4 passed\n");
//    } else {
//        printf("LEDS_GET() test 3/4 failed\n");
//    }
//    for (i = 0; i < 10000000; i++);
//    LEDS_SET(0xFF);
//    get_result = LEDS_GET();
//    if (get_result == 0xFF) {
//        printf("LEDS_GET() test 4/4 passed\n");
//    } else {
//        printf("LEDS_GET() test 4/4 failed\n");
//    }
//    for (i = 0; i < 10000000; i++);


    while (1);
}


/**
 * This is the interrupt for the Timer1 peripheral. During each call it increments a counter (the
 * value member of a module-level TimerResult struct). This counter is then checked against the
 * binary values of the four switches on the I/O Shield (where SW1 has a value of 1, SW2 has a value
 * of 2, etc.). If the current counter is greater than this switch value, then the event member of a
 * module-level TimerResult struct is set to true and the value member is cleared.
 */
void __ISR(_TIMER_1_VECTOR, IPL4AUTO) Timer1Handler(void)
{
    // Clear the interrupt flag.
    INTClearFlag(INT_T1);

    //increment value 
    Timer_1.value++;

    //if timer value exceeds return of SWUITCH_STATES, set event to TRUE and value to 0
    if (Timer_1.value > SWITCH_STATES()) {
        Timer_1.event = TRUE;
        Timer_1.value = 0;
    }

}



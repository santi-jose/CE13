//Jose Santiago jlsantia@ucsc.edu

// **** Include libraries here ****
// Standard C libraries


//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries
//------don't include BinaryTree.h or Morse.h!-----
#include "Morse.h"

//variables
int checkMorseInit;
static MorseEvent morseEvent;

int main()
{
    BOARD_Init();


    printf("Welcome to jlsantia's Lab8 Morse.h tester!  Compiled on %s %s\n", __DATE__, __TIME__);

    printf("Beginning automatic portion of Morse.h tester:\n");
    //test MorseInit()
    checkMorseInit = MorseInit();

    if (checkMorseInit == SUCCESS) {
        printf("MorseInit(); ran successfully\n");
    } else {
        printf("MorseInit(); failed to run\n");
    }


    //MorseInit();

    MorseEvent morseEventTest;
    morseEventTest.type = MORSE_EVENT_DOT;

    //test MorseDecode()
    morseEventTest = MorseDecode(morseEventTest);

    if (morseEventTest.type == MORSE_EVENT_NONE) {
        printf("MorseDecode(); Test 1/4 passed\n");
    } else {
        printf("MorseDecode(); Test 1/4 passed\n");
    }

    morseEventTest.type = MORSE_EVENT_NEW_LETTER;

    morseEventTest = MorseDecode(morseEventTest);

    if (morseEventTest.type == MORSE_EVENT_CHAR_DECODED) {
        printf("MorseDecode(); test 2/4 passed\n");
    } else {
        printf("MorseDecode(); test 2/4 failed\n");
    }


    printf("MorseDecode(); should be E, we got: %c\n", morseEventTest.parameter);


    //testing MorseDecode(); result should be W
    morseEventTest.type = MORSE_EVENT_DOT;

    morseEventTest = MorseDecode(morseEventTest);

    morseEventTest.type = MORSE_EVENT_DASH;

    morseEventTest = MorseDecode(morseEventTest);

    morseEventTest.type = MORSE_EVENT_DASH;

    morseEventTest = MorseDecode(morseEventTest);

    morseEventTest.type = MORSE_EVENT_NEW_LETTER;

    morseEventTest = MorseDecode(morseEventTest);

    if (morseEventTest.type == MORSE_EVENT_CHAR_DECODED) {
        printf("MorseDecode(); test 3/4 passed\n");
    } else {
        printf("MorseDecode(); test 3/4 failed\n");
    }

    //testing edge case to see "#"    
    morseEventTest.type = MORSE_EVENT_DOT;

    morseEventTest = MorseDecode(morseEventTest);

    morseEventTest.type = MORSE_EVENT_DOT;

    morseEventTest = MorseDecode(morseEventTest);

    morseEventTest.type = MORSE_EVENT_DASH;

    morseEventTest = MorseDecode(morseEventTest);

    morseEventTest.type = MORSE_EVENT_DASH;

    morseEventTest = MorseDecode(morseEventTest);

    morseEventTest.type = MORSE_EVENT_NEW_LETTER;

    morseEventTest = MorseDecode(morseEventTest);

    printf("We are expecting a W: %c\n", morseEventTest.parameter);

    if (morseEventTest.type == MORSE_EVENT_ERROR) {
        printf("MorseDecode(); Test 4/4 passed\n");
    } else {
        printf("MorseDecode(); Test 4/4 failed\n");
    }
    printf("We got our invalid character(#) indicator: %c\n", morseEventTest.parameter);

    //forcing edge case: test a leaf node: Trying to go past L in tree
    morseEventTest.type = MORSE_EVENT_DOT;

    morseEventTest = MorseDecode(morseEventTest);

    morseEventTest.type = MORSE_EVENT_DASH;

    morseEventTest = MorseDecode(morseEventTest);

    morseEventTest.type = MORSE_EVENT_DOT;

    morseEventTest = MorseDecode(morseEventTest);

    morseEventTest.type = MORSE_EVENT_DOT;

    morseEventTest = MorseDecode(morseEventTest);
    //at this point we should have  an "l"

    //    morseEventTest.type = MORSE_EVENT_NEW_LETTER;
    //    
    //    morseEventTest = MorseDecode(morseEventTest);
    //    
    //    printf("At this point we should have an L: %c\n",morseEventTest.parameter);

    //now I am going to add the error check. Any dot or dash event should return an error
    morseEventTest.type = MORSE_EVENT_DOT;

    morseEventTest = MorseDecode(morseEventTest);

    if (morseEventTest.type == MORSE_EVENT_ERROR) {
        printf("MorseDecode(); test 5/5 passed\n");
    } else {
        printf("MorseDecode(); test 5/5 failed\n");
    }





    printf("Beginning interactive portion of Morse.h tester:\n");

    // <editor-fold defaultstate="collapsed" desc="Configure Timer">

    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.
    OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_16, BOARD_GetPBClock() / 16 / 100);

    // Set up the timer interrupt with a medium priority of 4.
    INTClearFlag(INT_T2);
    INTSetVectorPriority(INT_TIMER_2_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_2_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T2, INT_ENABLED);
    // </editor-fold>    

    while (1) {
        //poll for MorseEvents and print them when detected
        if (morseEvent.type == MORSE_EVENT_DOT) {
            printf("DOT event generated\n");
            int i;
            for(i=0;i<100000;i++){  
                
            }
        }
        if (morseEvent.type == MORSE_EVENT_DASH) {
            printf("DASH event generated\n");
            int i;
            for(i=0;i<100000;i++){
                
            }
        }
        if (morseEvent.type == MORSE_EVENT_NEW_LETTER) {
            printf("MORSE_EVENT_NEW_LETTER event generated\n");
            int i;
            for(i=0;i<100000;i++){
                
            }
        }
        if (morseEvent.type == MORSE_EVENT_NEW_WORD) {
            printf("MORSE_EVENT_NEW_WORD event generated\n");
            int i;
            for(i= 0; i<100000;i++){
                
            }
        }
        if (morseEvent.type == MORSE_EVENT_NONE) {
            printf("MORSE_EVENT_NONE event generated\n");
            int i;
            for(i=0;i<100000;i++){
                
            }
        }
    }
}

//You shouldn't need to modify this ISR!

void __ISR(_TIMER_2_VECTOR, IPL4AUTO) TimerInterrupt100Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;


    morseEvent = MorseCheckEvents(); //added type MorseEvent was giving me error before??
}

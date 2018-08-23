//Jose Santiago jlsantia@ucsc.edu

// **** Include libraries here ****
// Standard C libraries


//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>
#include <stdio.h>

// User libraries
//------don't include BinaryTree.h or Morse.h!-----
#include "Ascii.h"
#include "Morse.h"
#include "Oled.h"
#include "OledDriver.h"

//Helper functions:
void OledAddToTopLine(MorseEvent event);
void OledClearTopLine(MorseEvent event);
void OledAddToBottomLine(MorseEvent event);

//module level morseEvent
static MorseEvent morseEvent;

//printing arrays
char string[50];
char *lastChar;

int main()
{
    BOARD_Init();

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

    printf("Welcome to jlsantia's Lab8 Morse decoder!  Compiled on %s %s", __DATE__, __TIME__);

    //initialization code
    OledInit();


    while (1) {
//        OledDrawString("Hello\nWorldI'm\nWorking!\n");
//        OledUpdate();

        //poll for morse events:
        if ((morseEvent.type == MORSE_EVENT_DOT) || (morseEvent.type == MORSE_EVENT_DASH)) {
            OledAddToTopLine(morseEvent); //update top line of OLED
            MorseDecode(morseEvent); //decode morseEvent
            OledAddToBottomLine(morseEvent); //update bottom line of OLED
            //consume morseEvent
        }
        if ((morseEvent.type == MORSE_EVENT_NEW_WORD) || (morseEvent.type == MORSE_EVENT_NEW_LETTER)) {
            OledClearTopLine(morseEvent);
        }
    };
}

//You shouldn't need to modify this ISR!

void __ISR(_TIMER_2_VECTOR, IPL4AUTO) TimerInterrupt100Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

    morseEvent = MorseCheckEvents();
}

void OledAddToTopLine(MorseEvent event)
{
    if (event.type == MORSE_EVENT_DOT) {
        OledDrawString(".");
        OledUpdate();
    }
    if (event.type == MORSE_EVENT_DASH) {
        OledDrawString("-");
        OledUpdate();
    }
}

void OledClearTopLine(MorseEvent event)
{
    if ((event.type == MORSE_EVENT_NEW_WORD) || (event.type == MORSE_EVENT_NEW_LETTER)) {
        OledDrawString("               "); //clear top line
        OledUpdate();
    }
}

void OledAddToBottomLine(MorseEvent event)
{
    if (event.type == MORSE_EVENT_CHAR_DECODED) {
        sprintf(string, "\n%c", event.parameter);
        OledDrawString(string);
        OledUpdate();
    }
    if (event.type == MORSE_EVENT_NEW_WORD) {
        lastChar = event.parameter;
        sprintf(string, "\n  %s", lastChar);
        OledDrawString(string);
        OledUpdate();
    }
    if (event.type == MORSE_EVENT_ERROR) { //print ERROR
        OledDrawString("\n#");
        OledUpdate();
    }
}


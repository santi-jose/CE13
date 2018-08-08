/*
 * File:   Buttons.c
 * Author: Jose Luis Santiago jlsantia@ucsc.edu
 *
 * Created on August 6, 2018, 3:57 PM
 */


#include "xc.h"
#include "Buttons.h"
#include "Board.h"

void ButtonsInit(void)
{
    TRISD |= 0x00E0;
    TRISF |= 0x0002;
}

//variable to store binary value of button states
uint8_t button_state = BUTTON_STATES();

uint8_t ButtonsCheckEvents(uint8_t button_states)
{
    uint8_t prev = BUTTON_STATES();
    if (button_state & BUTTON_STATE_1) {
        if ((prev & BUTTON_EVENT_1UP)&&(BUTTON_STATES() & BUTTON_EVENT_1DOWN)) {
            return BUTTON_EVENT_1DOWN;
        } else if ((prev & BUTTON_EVENT_1DOWN)&&(BUTTON_STATES() & BUTTON_EVENT_1UP)) {
            return BUTTON_EVENT_1UP;
        }
    }
    if (BUTTON_STATES() & BUTTON_STATE_2) {
        if ((prev & BUTTON_EVENT_2UP)&&(BUTTON_STATES() & BUTTON_EVENT_2DOWN)) {
            return BUTTON_EVENT_2DOWN;
        } else if ((prev & BUTTON_EVENT_2DOWN)&&(BUTTON_STATES() & BUTTON_EVENT_2UP)) {
            return BUTTON_EVENT_2UP;
        }
    }
    if (BUTTON_STATES() & BUTTON_STATE_3) {
        if ((prev & BUTTON_EVENT_3UP)&&(BUTTON_STATES() & BUTTON_EVENT_3DOWN)) {
            return BUTTON_EVENT_3DOWN;
        } else if ((prev & BUTTON_EVENT_3DOWN)&&(BUTTON_STATES() & BUTTON_EVENT_3UP)) {
            return BUTTON_EVENT_3DOWN;
        }
    }
    if (BUTTON_STATES() & BUTTON_STATE_4) {
        if ((prev & BUTTON_EVENT_4UP)&&(BUTTON_STATES() & BUTTON_EVENT_4DOWN)) {
            return BUTTON_EVENT_4DOWN;
        } else if ((prev & BUTTON_EVENT_4DOWN)&&(BUTTON_STATES() & BUTTON_EVENT_4UP)) {
            return BUTTON_EVENT_4UP;
        }
    }else return BUTTON_EVENT_NONE;
}
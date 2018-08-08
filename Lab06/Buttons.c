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

//variable to store previous binary value of button states
static uint8_t prev;

uint8_t ButtonsCheckEvents(uint8_t button_states)
{
    if (button_states & BUTTON_STATE_1) { //if button 1 has been pressed
        if (prev & BUTTON_EVENT_1DOWN) {  //if the previous Button up, then button must be down now
            prev |= BUTTON_EVENT_1DOWN; 
            return BUTTON_EVENT_1DOWN;
        } else if (prev & BUTTON_EVENT_1UP) {   //if previous was down
            prev |= BUTTON_EVENT_1UP;    //store flag to return as UP
            return BUTTON_EVENT_1UP;    //return button1 up flag
        }
    }
    if (button_states & BUTTON_STATE_2) { //if button 2 has been pressed
        return 2;
    }
    if (button_states & BUTTON_STATE_3) { //if button 3 has been pressed
        return 3;
    }
    if (button_states & BUTTON_STATE_4) { //if button 4 has been pressed
        return 4;
    }
    return BUTTON_EVENT_NONE;
}
/*
 * File:   part4.c
 * Author: Jose Luis Santiago
 *
 * Created on July 2, 2018, 6:05 PM
 */

//include libraries
#include "BOARD.h"
#include "Ascii.h"
#include "Oled.h"
#include "OledDriver.h"

int main(void)
{
    //initialize Oled 
    OledInit();
    
    //draw string to string buffer
    OledDrawString("Hello\nWorld");
    
    //update oled display with changes
    OledUpdate();
    while(1);
}

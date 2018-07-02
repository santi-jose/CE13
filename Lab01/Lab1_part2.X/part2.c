//  Jose Santiago  jlsantia@ucsc.edu
// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//Class specific libraries
#include "BOARD.h"

// Microchip libraries
#include <xc.h>

// User libraries
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    BOARD_Init();
    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    //Declare Variables
    float fahr, celsius;
    int lower, upper, step;
    char celsHead, fahrHead, kelvHead;

    //Initialize Variables
    lower = 0; //lower limit of temperature
    upper = 300; //upper limit
    step = 20; //step size 
    fahr = lower;
    celsHead = 'C';
    fahrHead = 'F';
    kelvHead = 'K';

    //print header
    printf("%5c %4c\n",(char)fahrHead,(char)celsHead);
    
    //print table
    while (fahr < upper) {
        celsius = (5.0 / 9.0)*(fahr - 32.0);
        printf("%7.1f %04.0f\n", (double) fahr, (double) celsius);
        fahr = fahr + step;
    }
    
    printf("\n");
    
    printf("%4c %7c\n",kelvHead,fahrHead);
    
    float kelv = lower;
    
    //print table
    while (kelv < upper) {
        fahr = (1.8)*(kelv - 273.0)+32.0;
        printf("%07.3f %6.2f\n", (double) kelv, (double) fahr);
        kelv = kelv + step;
    }


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks.
     **************************************************************************************************/

    // Returning from main() is bad form in embedded environments. So we sit and spin.
    while (1);
}

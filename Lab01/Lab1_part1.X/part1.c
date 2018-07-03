//Jose Santiago jlsantia@ucsc.edu
// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <stdlib.h>

//Class specific libraries
#include "BOARD.h"

// Microchip libraries
#include <xc.h>

// User libraries

//User Macros
#define N_ITEMS 5

    unsigned char vals[] = {rand(), rand(), rand(), rand(), rand()};
    int valsToBeSorted[] = {vals[0], vals[1], vals[2], vals[3], vals[4]};

int main(void)
{
    BOARD_Init();
    // Sort the array in place.
    int i, j;
    for (i = 0; i < N_ITEMS; i++) { //use for loop to iterate through list of items (<0to <5)
        int aTemp = valsToBeSorted[i];  //if i < N_ITEMS store value to be stored into valsToBeSorted array from aTemp
        for (j = i - 1; j >= 0; j--) {  //create loop to start changing after (i-1)>=0
            if (valsToBeSorted[j] <= aTemp) //if current index [j] in array is less than aTemp break
                break;
            valsToBeSorted[j + 1] = valsToBeSorted[j];  //store new value into old array address(changing value position)
        }
        valsToBeSorted [j + 1] = aTemp; //set temporary equal to new array address value(save value for next change in number position)
    }

    // Print out the array
    printf("[");
    for (i = 0; i < 4; i++) {
        printf("%d, ", valsToBeSorted[i]);
    }
    printf("%d]\n", valsToBeSorted[i]);

    /*
     * Returning from main() is bad form in embedded environments. So we
     * sit and spin.
     */
    while (1);
}
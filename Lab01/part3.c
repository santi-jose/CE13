//  NAME?  UCSC EMAIL?
// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <math.h>

//CMPE13 Support Library
#include "BOARD.h"
#include "math.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries

// **** Declare function prototypes ****

int main()
{
    BOARD_Init();
    printf("\n\nTesting math.h:\n");

    //tests for hypotf() from the math library:
    double hypot_result = hypotf(3.0, 4.0);
    printf("hypot(3,4) returned %f and should return %f\n", hypot_result, 5.0000);

    hypot_result = hypotf(1.0, 1.0);
    printf("hypot(1,1) returned %f and should return %f\n", hypot_result, 1.4142);

    //tests for atan2():		
    double atan2_result = atan2(1.5574, 1);
    printf("atan2(1.5574, 1) returned %f and should return %f\n", atan2_result, 1.0000);

    atan2_result = atan2(1, 1);
    printf("atan2(1, 1) returned %f and should return %f\n", atan2_result, M_PI/4);
    
    /******************************** Your code goes below here *******************************/
    printf("\n\nTesting SimpleMath.h:\n");



    /*************************************************************************************************/

    // You can never return from main() in an embedded system (one that lacks an operating system).
    // This will result in the processor restarting, which is almost certainly not what you want!
    while (1);

}



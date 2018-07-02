//Jose Santiago jlsantia@ucsc.edu
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
#include "SimpleMath.h"

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
    
    //tests for SquarePlusOne
    double squarePlusOneResult = SquarePlusOne(10);
    printf("SquarePlusOne(10) returned %f and should return %f\n",squarePlusOneResult,101.0000);
    
    double squarePlusOneResult2 = SquarePlusOne(5);
    printf("SquarePlusOne(5) returned %f and should return %f\n",squarePlusOneResult2,26.0000);

    //tests for DoubleLargest
    double doubleLargestResult = DoubleLargest(3,5);
    printf("DoubleLargest(3,5) returned %f and should return %f\n",doubleLargestResult,10.0000);
    
    double doubleLargestResult2 = DoubleLargest(-3,-10);
    printf("DoubleLargest(-3,-10) returned %f and should return -6.0000\n",doubleLargestResult2);

    /*************************************************************************************************/

    // You can never return from main() in an embedded system (one that lacks an operating system).
    // This will result in the processor restarting, which is almost certainly not what you want!
    while (1);

}



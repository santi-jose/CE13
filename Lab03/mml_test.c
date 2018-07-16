// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"


// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries:
#include "MatrixMath.h"

// Module-level variables:
float zero_matrix[3][3] = {{},{},{}};
float one_to_nine[3][3] = {{1,2,3},{4,5,6},{7,8,9}};

int main()
{
    BOARD_Init();

    printf("Beginning jlsantia's mml test harness, compiled on %s %s\n", __DATE__, __TIME__);
    
    printf("Demonstrating MatrixPrint():\n");
    MatrixPrint(zero_matrix);
    MatrixPrint(one_to_nine);

    //MatrixEquals testing
    if(MatrixEquals(zero_matrix,one_to_nine)==TRUE){
        printf("MatrixEquals Test 1/2 Failed, matrices are not equal\n");
    }
    else{
        printf("MatrixEquals Test 1/2 Passed, matrices are not equal\n");
    }
    
    if(MatrixEquals(zero_matrix,zero_matrix)==TRUE){
        printf("MatrixEquals Test 2/2 Passed, matrices are equal\n");
    }
    else{
        printf("MatrixEquals Test 2/2 Failed, matrices are equal");
    }
    
    //Testing 
    
    while (1);
}


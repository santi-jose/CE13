//Jose Santiago jlsantia@ucsc.edu

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
float nine_to_one[3][3]={{9,8,7},{6,5,4},{3,2,1}};
float one_matrix[3][3]={{1,1,1},{1,1,1},{1,1,1}};
float ten_matrix[3][3]={{10,10,10},{10,10,10},{10,10,10}};
float one_to_five[3][3]={{1,1.5,2},{2.5,3,3.5},{4,4.5,5}};

//expected results for MatrixMultiplication
float thirty_matrix[3][3]={{30,30,30},{30,30,30},{30,30,30}};
float expected_product2[3][3]={{24,19.5,15},{51,42,33},{78,64.5,51}};
float e_scalar_sum_one[3][3]={{-2.14,-1.64,-1.14},{-0.64,-0.14,0.36},{0.86,1.36,1.86}};
float e_scalar_sum_two[3][3]={{34,33,32},{31,30,29},{28,27,26}};
float e_scalar_product_one[3][3]={{-5,-7.5,-10},{-12.5,-15,-17.5},{-20,-22.5,-25}};
float e_scalar_product_two[3][3]={{3.5,7,10.5},{14,17.5,21},{24.5,28,31.5}};

int main()
{
    BOARD_Init();

    printf("Beginning jlsantia's mml test harness, compiled on %s %s\n", __DATE__, __TIME__);
    
    printf("Demonstrating MatrixPrint():\n");
    MatrixPrint(zero_matrix);
    MatrixPrint(one_to_nine);

    //MatrixEquals testing
    if(MatrixEquals(zero_matrix,one_to_nine)==TRUE){    //checks to see if matrices are equal
        printf("MatrixEquals Test 1/2 Failed, matrices are not equal\n");
    }
    else{   //matrices are not equal so it should print this message 
        printf("MatrixEquals Test 1/2 Passed, matrices are not equal\n");
    }
    
    if(MatrixEquals(zero_matrix,zero_matrix)==TRUE){    //checks to see if matrices are equal
        printf("MatrixEquals Test 2/2 Passed, matrices are equal\n");   //prints message here since matrices are equal
    }
    else{   
        printf("MatrixEquals Test 2/2 Failed, matrices are equal");
    }
    
    //Testing MatrixAdd
    float sum_one[3][3];    //array to store sum #1 in testing MatrixAdd
    MatrixAdd(zero_matrix,one_to_nine,sum_one); //calling MatrixAdd to store result into sum_one
    if(MatrixEquals(sum_one,one_to_nine)==TRUE){    //checking to see if Adding we received desired result
        printf("MatrixAdd Test 1/2 Passed, zero_matrix + one_to_nine = one_to_nine\n");
        MatrixPrint(sum_one);
    }
    else{
        printf("MatrixAdd Test 1/2 Failed, sum should be one_to_nine\n");
        MatrixPrint(sum_one);
    }
    
    float sum_two[3][3];    //array to store sum #2 in second test for MatrixAdd
    MatrixAdd(one_to_nine,nine_to_one,sum_two);
    if(MatrixEquals(sum_two,ten_matrix)==TRUE){
        printf("MatrixAdd Test 2/2 Passed, one_to_nine + nine_to_ten = ten_matrix\n");
        MatrixPrint(sum_two);
    }
    else{
        printf("MatrixAdd Test 2/2 Failed, sum should be ten_matrix\n");
        MatrixPrint(sum_two);
    }
    
    //Test MatrixMultiply
    float product_one[3][3];    //array to store product #1 for first MatrixMultiply test
    MatrixMultiply(one_matrix,ten_matrix,product_one);
    if(MatrixEquals(product_one,thirty_matrix)==TRUE){
        printf("MatrixMultiply Test 1/2 passed, one_matrix * ten_matrix = thirty_matrix\n");
        MatrixPrint(product_one);
    }
    else{
        printf("MatrixMultiply Test 1/2 failed, result should be thirty_matrix\n");
        MatrixPrint(product_one);
    }
    
    float product_two[3][3];    //array to store product #2 for second MatrixMultiply test
    MatrixMultiply(one_to_five,nine_to_one,product_two);
    if(MatrixEquals(product_two,expected_product2)==TRUE){
        printf("MatrixMultiply Test 2/2 passed result is:\n");
        MatrixPrint(product_two);
    }
    else{
        printf("MatrixMultiply Test 2/2 failed result is:\n");
        MatrixPrint(product_two);
    }
    
    //MatrixScalarAdd testing
    float scalar_sum_one[3][3];
    MatrixScalarAdd(-3.14,one_to_five,scalar_sum_one);
    if(MatrixEquals(scalar_sum_one,e_scalar_sum_one)==TRUE){
        printf("MatrixScalarAdd Test 1/2 passed, result is:\n");
        MatrixPrint(scalar_sum_one);
    }
    else{
        printf("MatrixScalarAdd Test 1/2 failed, result is:\n");
        MatrixPrint(scalar_sum_one);
    }
    
    float scalar_sum_two[3][3];
    MatrixScalarAdd(25,nine_to_one,scalar_sum_two);
    if(MatrixEquals(scalar_sum_two,e_scalar_sum_two)==TRUE){
        printf("MatrixScalarAdd Test 2/2 passed, result is:\n");
        MatrixPrint(scalar_sum_two);
    }
    else{
        printf("MatrixScalarAdd Test 2/2 failed, result is:\n");
        MatrixPrint(scalar_sum_two);
    }
    
    //MatrixScalarMultiply testing
    float scalar_product_one[3][3];
    MatrixScalarMultiply(-5,one_to_five,scalar_product_one);
    if(MatrixEquals(scalar_product_one,e_scalar_product_one)==TRUE){
        printf("MatrixScalarMultiply Test 1/2 passed, result is:\n");
        MatrixPrint(scalar_product_one);
    }
    else{
        printf("MatrixScalarMultiply Test 1/2 failed, result is:\n");
        MatrixPrint(scalar_product_one);
    }
    
    float scalar_product_two[3][3];
    MatrixScalarMultiply(3.5,one_to_nine,scalar_product_two);
    if(MatrixEquals(scalar_product_two,e_scalar_product_two)==TRUE){
        printf("MatrixScalarMultiply Test 2/2 passed, result is:\n");
        MatrixPrint(scalar_product_two);
    }
    else{
        printf("MatrixScalarMultiply Test 2/2 failed, result is:\n");
        MatrixPrint(scalar_product_two);
    }
    
    
    while (1);
}


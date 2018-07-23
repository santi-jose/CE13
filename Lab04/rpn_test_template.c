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

// User libraries
#include "rpn.h"

int main()
{
    BOARD_Init();
    int error;

    printf("\n###### Beginning jlsantia's rpn test harness: ####\n\n");

    //
    char test0[] = "1 1 +";
    double result0;
    double expected0 = 2;
    printf("Testing RPN_Evaluate with \"%s\"...\n", test0);
    error = RPN_Evaluate(test0, &result0);
    if (error) {
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (result0 != expected0) {
        printf("   Failed, expected = %f , result = %f\n", expected0, result0);
    } else {
        printf("   Success!\n");
    }
    
    //testing RPN_Evaluate subtraction
    char test1[]="25 5 /";
    double result1;
    double expected1 = 5;
    printf("Testing RPN_Evaluate with \"%s\"...\n",test1);
    error = RPN_Evaluate(test1, &result1);
    if(error){
        printf("Failed, RPN_Evaluate produced an error\n");
    }else if(result1 != expected1){
        printf("Failed, expected = %f, result = %f\n",expected1,result1);
    }    
    else{
        printf("Success\n");
    }
    
    //testing RPN_Evaluate multiplication
    char test2[]="1.30 3.0 *";
    double result2;
    double expected2=3.9;
    printf("Testing RPN_Evaluate with \"%s\"...\n",test2);
    error = RPN_Evaluate(test2,&result2);
    if(error){
        printf("Failed, RPN_Evaluate produced an error \n");
    }else if(result2 != expected2){
        printf("Failed, expected = %f, result = %f\n",expected2,result2);
    }
    else{
        printf("Success\n");
    }
    
    
    //testing RPN_Evaluate division
    char test3[]="4.5 5 /";
    double result3;
    double expected3=0.9;
    printf("Testing RPN_Evaluate with \"%s\"...\n",test3);
    error = RPN_Evaluate(test3,&result3);
    if(error){
        printf("Failed, RPN_Evaluate produced an error \n");
    }else if(result3 != expected3){
        printf("Failed, expected = %f, result = %f",expected3,result3);
    }
    else{
        printf("Success\n");
    }
    
    //test divide by zero
    char test4[]="5 0 /";
    double result4;
    printf("Testing RPN_Evaluate divide by zero error with \"%s\"...\n",test4);
    error = RPN_Evaluate(test4, &result4);
    if(error == RPN_ERROR_DIVIDE_BY_ZERO){
        printf("Success\n");
    }
    else{
        printf("Failure, should return error divide by zero error\n");
    }
            

//    printf("Testing ProcessBackspaces:\n");
//    char test_pb1[] = "123\b34";
//    ProcessBackspaces(test_pb1);
//    printf("result    : %s\n", test_pb1);
//    printf("should be : 1234\n");
//
      while (1);
}



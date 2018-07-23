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

    //testing RPN_Evaluate addition
    char test0[] = "1 1 +"; //create rpn_string
    double result0; //create double to store result of RPN_Evaluate
    double expected0 = 2; //save expected result
    printf("Testing RPN_Evaluate with \"%s\"...\n", test0); //print test message
    error = RPN_Evaluate(test0, &result0); //check for error message return
    if (error) { //if error != 0(RPN_NO_ERROR) -> Print error message
        printf("   Failed, RPN_Evaluate produced an error\n");
    } else if (result0 != expected0) { //if expected doesn't match with result print message
        printf("   Failed, expected = %f , result = %f\n", expected0, result0);
    } else { //else print success
        printf("   Success!\n");
    }

    //second addition test
    char test5[] = "1 0 +"; //rpn add by zero string
    double result5;
    double expected5 = 1;
    printf("Testing RPN_Evaluate with \"%s\"...\n", test5);
    error = RPN_Evaluate(test5, &result5);
    if (error) {
        printf("Failed, RPN_Evaluate produced an error\n");
    } else if (result5 != expected5) {
        printf("Failed, expected = %f, result = %f\n", expected5, result5);
    } else {
        printf("Success!\n");
    }


    //testing RPN_Evaluate subtraction
    char test1[] = "25 5 -"; //test rpn_string for subtraction testing
    double result1;
    double expected1 = 20;
    printf("Testing RPN_Evaluate with \"%s\"...\n", test1);
    error = RPN_Evaluate(test1, &result1);
    if (error) {
        printf("Failed, RPN_Evaluate produced an error\n");
    } else if (result1 != expected1) {
        printf("Failed, expected = %f, result = %f\n", expected1, result1);
    } else {
        printf("Success\n");
    }

    //subtraction test 2
    char test7[] = "-2 3 -";
    double result7;
    double expected7 = -5;
    printf("Testing RPN_Evaluate with \"%s\"...\n", test7);
    error = RPN_Evaluate(test7, &result7);
    if (error) {
        printf("Failed, RPN_Evaluate produced an error\n");
    } else if (result7 != expected7) {
        printf("Failed, expected = %f, result = %f\n", expected7, result7);
    } else {
        printf("Success\n");
    }

    //testing RPN_Evaluate multiplication
    char test2[] = "1.30 3.0 *"; //test string for multiplication testing
    double result2; //double used to store result
    double expected2 = 3.9;
    printf("Testing RPN_Evaluate with \"%s\"...\n", test2);
    error = RPN_Evaluate(test2, &result2);
    if (error) {
        printf("Failed, RPN_Evaluate produced an error \n");
    } else if (result2 != expected2) {
        printf("Failed, expected = %f, result = %f\n", expected2, result2);
    } else {
        printf("Success\n");
    }

    //second multiplication test
    char test6[] = "1.5 -5 *";
    double result6;
    double expected6 = -7.5;
    printf("Testing RPN_Evaluate with \"%s\"...\n", test6);
    error = RPN_Evaluate(test6, &result6);
    if (error) {
        printf("Failed, RPN_Evaluate with \"%s\"...\n", expected6, result6);
    } else if (result6 != expected6) {
        printf("Failed, expected = %f, result = %f\n", expected6, result6);
    } else {
        printf("Success\n");
    }


    //testing RPN_Evaluate division
    char test3[] = "4.5 5 /"; //test string for division testing
    double result3; //double used to store result
    double expected3 = 0.9; //declare expected value
    printf("Testing RPN_Evaluate with \"%s\"...\n", test3); //print test message
    error = RPN_Evaluate(test3, &result3); //evaluate test3
    if (error) { //if there is an error from enum returned, print error message
        printf("Failed, RPN_Evaluate produced an error \n");
    } else if (result3 != expected3) { //else if result is not equal to expected print error message
        printf("Failed, expected = %f, result = %f", expected3, result3);
    } else { //else print success
        printf("Success\n");
    }

    //test divide by zero
    char test4[] = "5 0 /"; //test string to divide by zero
    double result4; //double to store result
    printf("Testing RPN_Evaluate divide by zero error with \"%s\"...\n", test4);
    error = RPN_Evaluate(test4, &result4);
    if (error == RPN_ERROR_DIVIDE_BY_ZERO) {
        printf("Success RPN_ERROR_DIVIDE_BY_ZERO received\n");
    } else {
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



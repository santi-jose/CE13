/*
 * File:   rpn.c
 * Author: Jose Luis Santiago jlsantia@ucsc.edu
 *
 * Created on July 23, 2018, 9:37 AM
 */


#include "rpn.h"
#include "stack.h"

int RPN_Evaluate(char * rpn_string, double * result)
{
    char *token; //pointer to the token where strtok() initialization will be stored
    double double1, double2; //initializing float 1 and 2 (operands)
    double operand; //variable to store operand
    struct Stack operandStack; //create stack to push operands onto
    StackInit(&operandStack); //initialize stack
    token = strtok(rpn_string, " "); //split rpn_string up into pieces and store into token pointer

    //while the address of token is not null
    while (token != NULL) {
        operand = atof(token); //convert token into operand
        if (operand == 0.0) { //if operand has value of 0.0 it is either 0 or an operand
            if (token[0] == '0') { //check if token is zero, push if it is
                StackPush(&operandStack, operand);
            } else { //else check to see if it is a valid operator
                if (token[0] == '+') { //pop twice into float1 and 2 and perform addition
                    StackPop(&operandStack, &double1); // pop first operand
                    printf("float1 =:%f\n", double1); //print first operand
                    StackPop(&operandStack, &double2); // pop second operand
                    printf("float 2 =:%f\n", double2); //print second operand
                    *result = double2 + double1; //store sum in result 
                    printf("result=%f\n",*result);
                    return RPN_NO_ERROR;
                } else if (token[0] == '-') { //pop twice into float 1 and 2 and perform subtraction
                    StackPop(&operandStack, &double1); // pop first operand
                    printf("float1 =%f\n", double1); //print first operand
                    StackPop(&operandStack, &double2); // pop second operand
                    printf("float 2 =%f\n", double2); //print second operand
                    *result = double2 - double1;    //store difference into result
                    printf("result=%f\n",*result);
                    return RPN_NO_ERROR;
                } else if (token[0] == '*') { //pop twice into float 1 and 2 and perform multiplication
                    StackPop(&operandStack, &double1); // pop first operand
                    printf("float1 =%f\n", double1); //print first operand
                    StackPop(&operandStack, &double2); // pop second operand
                    printf("float 2 =%f\n", double2); //print second operand
                    *result = double2 * double1;    //store product into result
                    printf("result=%f\n",*result);
                    return RPN_NO_ERROR;
                } else if (token[0] == '/') { //pop twice into float 1 and 2 and perform division
                    StackPop(&operandStack, &double1); // pop first operand
                    if(double1==0.0){   //check if double1 is valid in terms of dividing by zero
                        return RPN_ERROR_DIVIDE_BY_ZERO;
                    }else{
                    printf("float1 =%f\n", double1); //print first operand
                    StackPop(&operandStack, &double2); // pop second operand
                    printf("float 2 =%f\n", double2); //print second operand
                    *result = double2 / double1;    //store quotient into result
                    printf("result=%f\n",*result);
                    return RPN_NO_ERROR;
                    }
                } else {
                    printf("ERROR\n");    //else print error message invalid token
                    return RPN_ERROR_INVALID_TOKEN;
                }
            }
        } else {    //if token is not equal to zero, perform 
            StackPush(&operandStack, operand);
        }
        token=strtok(NULL," "); //iterate through to next null pointer
    }
}
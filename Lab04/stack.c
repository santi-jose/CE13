/*
 * File:   stack.c
 * Author: Jose Luis Santiago jlsantia@ucsc.edu
 *
 * Created on July 18, 2018, 1:00 PM
 */

//include user libraries
#include "stack.h"

//stack init: set currentItemIndex to 0 and set stackInit to TRUE

void StackInit(struct Stack *stack)
{
    stack->currentItemIndex = -1; //set currentItemIndex to -1
    stack->initialized = TRUE; //set stack initialized to TRUE
}

//function pushes item onto stack

int StackPush(struct Stack *stack, double value)
{
    if ((stack->initialized == TRUE)&&(stack->currentItemIndex<STACK_SIZE)) { //if stack is initialized, perform stackPush
        stack->currentItemIndex++; //increment itemIndex
        stack->stackItems[stack->currentItemIndex] = value; //push the value onto the current stack item index
        return SUCCESS;
    } else { //else return STANDARD_ERROR
        return STANDARD_ERROR;
    }
}

//function pops an item from stack

int StackPop(struct Stack *stack, double *value)
{
    if ((stack->initialized == TRUE) && (stack->currentItemIndex>-1)) { //perform StackPop if stack is initialized and the stack is not empty
        *value = stack->stackItems[stack->currentItemIndex]; //pop value
        stack->currentItemIndex--; //decrement stack after popping value
        return SUCCESS; //return success
    } else { //else return error
        return STANDARD_ERROR;
    }
}

int StackIsEmpty(const struct Stack *stack)
{
    if ((stack->currentItemIndex == -1) && (stack->initialized == TRUE)) { //check if stack is empty and stack initialization
        return TRUE;
    } else {
        return FALSE;
    }
}

int StackIsFull(const struct Stack *stack)
{
    if ((stack->currentItemIndex == (STACK_SIZE - 1))&&(stack->initialized == TRUE)) { //check for full stack and stack initialization
        return TRUE;
    } else {
        return FALSE;
    }
}

int StackGetSize(const struct Stack *stack)
{
    if (stack->initialized == FALSE) {
        return SIZE_ERROR;
    } else if ((stack->currentItemIndex == -1) && (stack->initialized == TRUE)) {
        return 0;
    } else {
        return stack->currentItemIndex + 1;
    }
}



//Jose Santiago jlsantia@ucsc.edu

// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries
#include "stack.h"

int main()
{
    BOARD_Init();

    printf("\n###### Beginning jlantia's stack test harness: ####\n\n");

    //Testing StackInit()
    printf("Does StackInit() set the currentItemIndex appropriately?\n");
    struct Stack stack = {};
    StackInit(&stack);
    if (stack.currentItemIndex == -1) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }

    //does StackkInit set initialized to TRUE properly?
    printf("Does StackInit() set initialized to TRUE properly?\n");
    if (stack.initialized == TRUE) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }

    
    
    //Testing StackPush()
    //Testing to see if contents of stack are in right index
    printf("Does StackPush() put the appropriate value in the appropriate array index?\n");
    StackPush(&stack,25);
    if(stack.stackItems[stack.currentItemIndex]==25){   //check if stackItem was properly pushed
        printf("passed\n");
    }
    else{
        printf("failed\n");
    }
    
    //Testing to see if StackPush() is in proper item index
    printf("Did StackPush() push the current item into the proper index?\n");
    if(stack.currentItemIndex == 0){
        printf("passed\n");
    }
    else{
        printf("failed\n");
    }
    
    //Testing StackPop()
    //Test to see if StackPop() returns my pushed value
    printf("Did StackPop() pop the correct value?(25)\n");
    double stackPopValue;   //declare double to store value to pop from stack
    StackPop(&stack,&stackPopValue);    //call StackPop by feeding it pointers to the stack and a pointer to the variable used for pop storage
    if(stackPopValue == 25){    //if stackPopValue is same as pushed value
        printf("passed\n");
    }
    else{
        printf("failed\n");
    }
    
    //Test to see if StackPop() stores correct index after popping
    printf("Does StackPop() return proper index after being called on the stack?\n");
    if(stack.currentItemIndex==-1){ //after popping the only value pushed, the itemindex should be at -1 again
        printf("passed\n");
    }
    else{
        printf("failed\n");
    }
    
    //Testing StackIsEmpty()
    //Test to see if StackIsEmpty () works with an empty stack
    printf("Does StackIsEmpty() return TRUE with our empty stack?\n");
    if(StackIsEmpty(&stack)==TRUE){
        printf("passed\n");
    }
    else{
        printf("failed\n");
    }
    
    //Test to see if StackIsEmpty() returns FALSE with a stack that is not empty
    printf("Does StackIsEmpty() return FALSE with a stack that is not empty?\n");
    StackPush(&stack,69);
    if(StackIsEmpty(&stack)==FALSE){
        printf("passed\n");
    }
    else{
        printf("failed\n");
    }
    
    //StackIsFull() testing
    //Testing StackIsFull() returns FALSE when stack is not full
    printf("Test if StackIsFull() returns FALSE with stack that is not full\n");
    if(StackIsFull(&stack)==FALSE){
        printf("passed\n");
    }
    else{
        printf("failed\n");
    }
    
    //fill stack
    int i;
    for(i=0;i<(STACK_SIZE-1);i++){
        StackPush(&stack,i);
    }
    
    //Check if StackIsFull() returns TRUE for full stack
    printf("Does StackIsFull() return TRUE with a full stack?\n");
    if(StackIsFull(&stack)==TRUE){
        printf("passed\n");
    }
    else{
        printf("failed\n");
    }
    
    //StackGetSize() testing
    //Check if StackGetSize() returns 20 for a full stack
    printf("Does StackGetSize() returns 20 for a full stack?\n");
    if(StackGetSize(&stack)==20){
        printf("passed\n");
    }
    else{
        printf("failed\n");
    }
    
    //Check if StackGetSize() returns 0 for an empty stack
    printf("Does StackGetSize() return 0 when stack is empty?\n");
    for(i=0;i<(STACK_SIZE);i++){
        StackPop(&stack,&stackPopValue);
    }
    
    if(StackGetSize(&stack)==0){
        printf("passed\n");
    }
    else{
        printf("failed\n");
    }
    
    
    
    while (1);
    return 0;
}



/*
 * File:   LinkedListTest.c
 * Author: Jose Luis Santiago jlsantia@ucsc.edu
 *
 * Created on July 30, 2018, 1:47 PM
 */

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries
#include "LinkedList.h"

int main(void)
{



    BOARD_Init();
    printf("\r\nWelcome to jlsantia's LinkedList testing suite\r\n");

    //integer variables to store the sizes of the lists
    int animal_size;
    int myLI_size;

    //create a NULL pointer
    ListItem * myLI = NULL;

    printf("No list yet...\n");
    LinkedListPrint(myLI); //test NULL input for print function

    //test LinkedListNew
    printf("Adding an item...\n");
    myLI = LinkedListNew("FIRST ITEM");
    LinkedListPrint(myLI); //test first item is FIRST_ITEM

    //test LinkedList Size
    myLI_size = LinkedListSize(myLI);
    if (myLI_size == 1) {
        printf("LinkedListSize Test 1/3 Passed. \nSize of first list is:%d\n", myLI_size);
    } else {
        printf("LinkedListSize Test 1/3 Failed. \n Size of first list should be 1\n");
    }

    printf("How about a larger list?\n");
    ListItem * animal_list = LinkedListNew("Elephant");
    ListItem * first_animal = animal_list; //save head node for getfirst testing
    animal_list = LinkedListCreateAfter(animal_list, "Moose");
    animal_list = LinkedListCreateAfter(animal_list, "Cuttlefish");
    LinkedListPrint(animal_list);

    animal_size = LinkedListSize(animal_list);
    if (animal_size == 3) {
        printf("LinkedListSize Test 2/3 passed. \nSecond list size is:%d\n", animal_size);
    } else {
        printf("LinkedListSize Test 2/3 failed. \nSecond list size should be 3\n");
    }


    //test LinkedListGetFirst with animal_list and first_animal pointer we saved earlier
    if (first_animal == LinkedListGetFirst(animal_list)) {
        printf("LinkedListGetFirst Test 1/2 passed. \n");
    } else {
        printf("LinkedListGetFirst Test 1/2 failed. \n");
    }

    //add more items to myLI to test LinkedListGetFirst more
    printf("Adding more items to first list...\n");
    ListItem * first_myLI = myLI;
    myLI = LinkedListCreateAfter(myLI, "SECOND_ITEM");
    myLI = LinkedListCreateAfter(myLI, "THIRST_ITEM");
    myLI = LinkedListCreateAfter(myLI, "FOURTH_ITEM");
    printf("Printing new list of items:\n");
    LinkedListPrint(myLI);

    if (first_myLI == LinkedListGetFirst(animal_list)) {
        printf("LinkedListGetFirst Test 2/2 passed. \n");
    } else {
        printf("LinkedListGetFirst Test 2/2 failed. \n");
    }
    
    //test LinkedListSize a third time
    myLI_size=LinkedListSize(myLI);
    if(myLI_size == 4){
        printf("LinkedListSize Test 3/3 passed. \nFirst list size is now:%d\n",myLI_size);
    }else{
        printf("LinkedListSize Test 3/3 failed. \nList size should be 4\n");
    }

    //trying to remove first animal from animal list
    LinkedListRemove(first_animal);
    animal_size = LinkedListSize(animal_list);
    if(animal_size==2){
        printf("LinkedListRemove Test 1/2 passed. \n");
    }else{
        printf("LinkedListRemove Test 1/2 failed. \n");
    }
    printf("New animal list:\n");
    LinkedListPrint(animal_list);
    
    //trying to first item from myLI
    LinkedListRemove(first_myLI);
    myLI_size=LinkedListSize(myLI);
    if(myLI_size==3){
        printf("LinkedListRemove Test 2/2 passed. \n");
    }else{
        printf("LinkedListRemove Test 2/2 failed. \n");
    }
    printf("New item list:\n");
    LinkedListPrint(myLI);






    printf("DONE!\n");
    while (1);
}

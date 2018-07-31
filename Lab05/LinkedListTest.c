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

int main(void) {
    

    
    BOARD_Init();
	printf("\r\nWelcome to jlsantia's LinkedList testing suite\r\n");
    
        //integer variables to store the sizes of the lists
    int animal_size;   
    int myLI_size;
        
    //create a NULL pointer
    ListItem * myLI = NULL;
    
    printf("No list yet...\n");
    LinkedListPrint(myLI);  //test NULL input for print function
    
    //test LinkedListNew
    printf("Adding an item...\n");
    myLI = LinkedListNew("FIRST ITEM");
    LinkedListPrint(myLI);  //test first item is FIRST_ITEM
    
    //test LinkedList Size
    myLI_size=LinkedListSize(myLI);
    printf("Size of first list is:%d\n",myLI_size);
    
    printf("How about a larger list?\n");
    ListItem * animal_list = LinkedListNew("Elephant");
    animal_list = LinkedListCreateAfter(animal_list, "Moose");
    animal_list = LinkedListCreateAfter(animal_list, "Cuttlefish");
    LinkedListPrint(animal_list);
    
    animal_size = LinkedListSize(animal_list);
    printf("The animal list size is:%d\n",animal_size);
    
	printf("DONE!\n");
        
    
        
        
        
        
        
        
        

        
        while(1);
}

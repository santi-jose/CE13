/*
 * File:   LinkedList.c
 * Author: Jose Luis Santiago jlsantia@ucsc.edu
 *
 * Created on July 29, 2018, 1:57 PM
 */


#include "LinkedList.h"
#include "BOARD.h"
#include <stdio.h>
#include <stdlib.h>

//LinkedListNew creates a new linked list starting with the head

ListItem *LinkedListNew(char *data)
{
    ListItem *newItem; //create pointer to new list
    newItem = (ListItem *) malloc(sizeof (ListItem)); //allocate memory for item node
    if (newItem == NULL) { //if fed in a NULL pointer return NULL and print error message
        printf("Error out of memory to allocate\n");
        return NULL;
    } else { //else print success message and make fill proper struct members
        printf("New list created successfully\n");
        newItem->previousItem = NULL;
        newItem->data = data;
        newItem->nextItem = NULL;
        return newItem; //return pointer to newItem member
    }
}

//Function that removes an item from a list and readjusts the next and previous pointers of surrounding nodes

char *LinkedListRemove(ListItem *item) //function removes an item from list
{
    if (item == NULL) { //check it given a NULL pointer
        printf("Error input NULL pointer\n");
        return NULL;
    } else if(item->previousItem==NULL){    //if at the head of the list
        item->nextItem->previousItem=NULL;
        item->nextItem=NULL;
        return item->data;
    }
    else if(item->nextItem==NULL){  //if at the end of a list
        item->previousItem->nextItem=NULL;
        item->previousItem=NULL;
        return item->data;
    }
    else {  //when inside the list
        ListItem *temp; //create temporary listitem pointer to store item for removal's address
        item->previousItem->nextItem = item->nextItem; //
        item->nextItem->previousItem = item->previousItem;
        temp = item; //copy ListItem pointer to temp
        free(item); //free data stored for listitem item
        return temp->data;
    }
}

int LinkedListSize(ListItem *list)
{
    if(list == NULL){   //return zero if given a NULL
        return 0;
    }
    while(list->previousItem!=NULL){    //go to head node if not in head node
        list = list->previousItem;
    }
    int count=1;    //start count variable at 1 for indexing
    while(list->nextItem!=NULL){    //while not at tail node 
        list = list->nextItem;  //go to next list item
        count++;    //increment count
    }
    return count;   //return count
}

ListItem *LinkedListGetFirst(ListItem *list)
{
    if(list==NULL){ //if given a null pointer return NULL
    return NULL;
    }
    else if(list->previousItem==NULL){  //else if already at head, return same pointer
        return list;
    }
    else{   //else traverse to the head of the list
        while(list->previousItem!=NULL){
            list=list->previousItem;
        }
        return list;    //return head of list
    }
}

ListItem *LinkedListCreateAfter(ListItem *item, char *data)
{
    //create new pointer to new node
    ListItem *newItem;
    newItem = (ListItem *) malloc(sizeof (ListItem));
    //check to see if there is enough memory space to allocate
    if (newItem == NULL) {
        printf("Error out of memory to allocate\n");
        return NULL;
    }
    //give newItem it's data as well as having it point to the proper member
    if (item == NULL) { //check to see if current item is null
        newItem->data = data; //input data put into new member
        newItem->nextItem = item->nextItem; //nextItem listed as first starting member's next Item
        item->nextItem->previousItem = newItem; //set item's nextItem's previousItem as newITem
        newItem->previousItem = NULL; //newItem previousItem set to starting member
        item->nextItem = newItem; //make next item's previous member equal to our new member
        return newItem; //return pointer to newItem
    } else if (item->nextItem == NULL) { //if there is no following list item simply insert newItem after and have it point back to given ListItem
        item->nextItem = newItem; //set current item's next item to newItem
        newItem->previousItem = item; // set newItem's previous item equal to item
        newItem->nextItem = NULL; //set newItem's next item to NULL
        newItem->data = data; //set newItem's data equal to input data
        return newItem; //return pointer to newItem node pointing to previous and null
    } else {
        newItem->data = data; //input data put into new member
        newItem->nextItem = item->nextItem; //nextItem listed as first starting member's next Item
        item->nextItem->previousItem = newItem; //set item's nextItem's previousItem as newITem
        newItem->previousItem = item; //newItem previousItem set to starting member
        item->nextItem = newItem; //make next item's member equal to newItem
        return newItem; //return pointer to newItem
    }
}

int LinkedListSwapData(ListItem *firstItem, ListItem *secondItem)
{
    if(firstItem==NULL||secondItem==NULL){
        return STANDARD_ERROR;
    }
    ListItem * temp = (ListItem *)malloc(sizeof(ListItem));//declare node to store temporary data
    temp->data=firstItem->data;
    firstItem->data=secondItem->data;
    secondItem->data=temp->data;
    free(temp); //free data allocated for temp
    return  SUCCESS;
}

int LinkedListSort(ListItem *list)
{
    return NULL;
}

int LinkedListPrint(ListItem *list)
{ //while the item given is not the head of the list, traverse the list to the head
    if (list == NULL) {
        return STANDARD_ERROR;
    }
    if ((list->previousItem == NULL)&&(list->nextItem == NULL)) { //check to see if list only has one element
        printf("%s\n", list->data);
        return SUCCESS;
    }
    while (list->previousItem != NULL) { //if list is not at head, traverse to head of list
        list = list->previousItem;
    }
    while (list->nextItem != NULL) { //when list is at the head, print data and traverse list forward
        printf("%s\n", list->data);
        list = list->nextItem;
    }
    printf("%s\n",list->data);  //print last item in list when list->nextItem is NULL
    return SUCCESS;
}







/*
 * File:   BinaryTree.c
 * Author: Jose Luis Santiago jlsantia@ucsc.edu
 *
 * Created on August 16, 2018, 2:12 PM
 */

//include user libraries
#include "BinaryTree.h"

//include public libraries
#include <stdlib.h>
#include <stdio.h>

Node *TreeCreate(int level, const char *data)
{
    //allocate memory for root node
    Node *root = (struct Node*) malloc(sizeof (Node));

    //return null if malloc FAILED
    if (root == NULL) {
        return NULL;
    }

    //give our root node our data
    root->data = *data;
    
    //if we have yet to hit our base case
    if (level > 1) {
        //create a right and left child for our root node calling TreeCreate(); recursively
        root->rightChild = TreeCreate(level - 1, data + (1 << (level - 1))); //data + 2^(level-1) to get appropriate order of string format for rightChild's
        root->leftChild = TreeCreate(level - 1, data + 1); //create left branch

    } else {    //we have hit our base case, create NULL leaves
        root->leftChild = NULL;
        root->rightChild = NULL;
    }
    return root;    //return root
}

void TreePrint(Node *node, int space)
{
    int i;
    if (node == NULL) {
        return;
    } else{
        space = space + LEVEL_SPACES; //increment space by LEVEL_SPACES depending on current level
        TreePrint(node->rightChild, space); //print right branch
        printf("\n"); //print new line
        for (i = 0; i < space; i++) { //print the appropriate amount of spaces
            printf(" ");
        }
        if (i == space) { //if spaces have been printed, print data
            printf("%c", node->data);
        }
        TreePrint(node->leftChild, space); //print left branch
    }
}

Node *GetLeftChild(Node *root)
{
    if (root->leftChild == NULL) { //if no leftChild, return NULL
        return NULL;
    } else { //else return pointer to leftChild
        return root->leftChild;
    }
}

Node *GetRightChild(Node *root)
{
    if (root->rightChild == NULL) { //if no rightChild, return NULL
        return NULL;
    } else {    //else return rightChild
        return root->rightChild;
    }
}

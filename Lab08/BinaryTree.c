/*
 * File:   BinaryTree.c
 * Author: Jose Luis Santiago
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

    //if we reach our base case(level = 0): give make the leaves NULL
    if (level == 0) {
        root->leftChild = NULL;
        root->rightChild = NULL;
    } else {
        //give our root node our data
        root->data = *data;

        //create a right and left child for our root node calling TreeCreate(); recursively
        root->rightChild = TreeCreate(level - 1, data + (1 << (level - 1))); //data + 2^(level-1) to get appropriate order of string format for rightChild's
        root->leftChild = TreeCreate(level - 1, data + 1); //create left branch

    }
    return root;
}

void TreePrint(Node *node, int space)
{
    int i;
    if (node == NULL) {
        return;
    } else {
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

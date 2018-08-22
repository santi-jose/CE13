//Jose Santiago jlsantia@ucsc.edu

// Heap size 2048 required!

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries
#include "BinaryTree.h"

// **** Set any macros or preprocessor directives here ****


// **** Define any module-level, global, or external variables here ****


// **** Declare any function prototypes here ****


int main()
{
    BOARD_Init();

	printf("\nWelcome to jlsantia's Binary Tree test harness, compiled on %s %s\n",__DATE__,__TIME__);

	//this is a simple test binary tree, included so you can write the relatively simple TreePrint() before implementing CreateTree().  You should NOT create your binary trees this way.
	
	//level 1 (leaf) nodes
//	Node nodeD = {NULL, NULL, 'C'};
//	Node nodeE = {NULL, NULL, 'E'};
//	Node nodeF = {NULL, NULL, 'F'};
//	Node nodeG = {NULL, NULL, 'G'};
//	//level 2 nodes:
//	Node nodeB = {&nodeD, &nodeE, 'B'};
//	Node nodeC = {&nodeF, &nodeG, 'C'};
//	//level 3 node:
//	Node nodeA = {&nodeB, &nodeC, 'A'};
  	Node * root;
	
        //TreeCreate() test
        root = TreeCreate(3,"ABCDEFG");
        
	TreePrint(root, 5);	
        
        printf("\n");
	
        root = TreeCreate(3,"1234567");
        
        TreePrint(root,1);
        
        printf("\n");
        
        root = TreeCreate(6,"#EISH54V#3UF####2ARL#####WP##J#1TNDB6#X##KC##Y##MGZ7#Q##O#8##90");
        
        TreePrint(root,0);
        
        printf("\n");
	
        //start testing GetRightChild
        
        root = GetRightChild(root);
        
        if(root->data=='T'){
            printf("GetRightChild test 1/2 passed\n");
        }else{
            printf("GetRightChild test 1/2 failed\n");
        }
        
        root = GetRightChild(root);
        
        if(root->data=='M'){
            printf("GetRightChild test 2/2 passed\n");
        }
        
        //start testing GetLeftChild
        root = GetLeftChild(root);
        
        if(root->data == 'G'){
            printf("GetLeftChild test 1/2 passed\n");
        }else{
            printf("GetLeftChild test 1/2 failed\n");
        }
        
        root = GetLeftChild(root);

        if(root->data == 'Z'){
            printf("GetLeftChildtest 2/2 passed\n");
        }else{
            printf("GetLeftChild test 2/2 failed\n");
        }
        
        
    while (1);
}


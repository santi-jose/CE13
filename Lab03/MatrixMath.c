/*
 * File:   MatrixMath.c
 * Author: Jose Luis Santiago jlsantia@ucsc.edu
 *
 * Created on July 15, 2018, 11:59 PM
 */

//include necessary libraries
#include "MatrixMath.h"

//user macros
#define TRUE 1
#define FALSE 0

//Function takes two matrix pointers for arguments and returns 1 if they're equal, 0 otherwise
int MatrixEquals(float mat1[3][3], float mat2[3][3]){
    //nesting for loops to iterate through every matrix data entry
    for(int i=0;i<2;i++){   //iterate through rows
        for(int j=0;j<2;j++){   //iterate through columns
            if(abs(mat1[i][j] - mat2[i][j]) > FP_DELTA){  //check for equality accounting for round error
                return FALSE;
            }     
        }
    }
    return TRUE;
}

//Function adds two matrices together and returns pointer to resultant matrix
void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3]){
    //nesting for loops to iterate through every matrix data entry
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

//Function performs matrix multiplication returning pointer to resultant matrix
void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3]){
    //nest for loops to iterate through matrices
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            result[1][j] = (mat1[i][j] * mat2[j][i]) + result[1][j];    //perform and store matrix multiplication into resultant vector
        }
    }
}

//Function performs scalar addition on Matrix
void MatrixScalarAdd(float x, float mat[3][3], float result[3][3]){
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            result[i][j] = x + mat[i][j];   //perform scalar addition
        }
    }
}

//function performs scalar multiplication on matrix
void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3]){
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            result[i][j] = x * mat[i][j];   //perform scalar multiplication
        }
    }
}

//
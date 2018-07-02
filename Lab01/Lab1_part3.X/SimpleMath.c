/*
 * File:   SimpleMath.c
 * Author: Jose Luis Santiago
 *
 * Created on July 2, 2018, 1:08 PM
 */


#include "SimpleMath.h"

//Square plus one function: Squares value then adds one
int SquarePlusOne(int x){
    //declare local temporary variable
    int temp;
    
    //set equal to x for math operations
    temp = x;
    
    //square temp
    temp = temp * temp;
    
    //add one
    temp++;
    
    //return temp
    return temp;
}

//DoubleLargest: doubles the largest of both values
int DoubleLargest(int y, int x){
    //declare local temporary variable
    int temp;
    
    //if x is greater than y
    if(x > y){
        //set temporary equal to greater value
        temp = x;
        
        //double the value
        temp = 2 * temp;
        
        //return value
        return temp;
    }
    //else if y is greater than x
    else if(y > x){
        //set temporary equal to greater value
        temp = y;
        
        //double the value
        temp = 2 * temp;
        
        //return value
        return temp;
    }
    //if y and x are equal print message
    else if(y == x){
        printf("y and x are the same");
        return;
    }
}

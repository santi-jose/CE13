//Jose Santiago  jlsantia

// Standard libraries
#include <stdio.h>
#include <math.h>
#include <xc.h>

//User libraries:
#include "BOARD.h"


// **** Declare function prototypes ****
double Add(double operand1, double operand2);
double Multiply(double operand1, double operand2);
double AbsoluteValue(double operand);
double FahrenheitToCelsius(double operand);
double Tangent(double operand);



void CalculatorRun(void)
{
    printf("\n\nWelcome to Jose's calculator program! Compiled at %s %s\n",__DATE__, __TIME__);
    while(1){
    //Infinite prompt message for operations
    printf("Choose one of the following operations:( '*' , '/' , '+' , '-' , 'm' , 'a' , 'c' , 'f' , 't' )\n");
    char operation;     //variable to store user operation input
    scanf(" %c",&operation);    //getting operation user input
    double operand1; //operand 1 and 2 used for binary arithmetic functions
    double operand2;
    //checking for valid binary operations
    if(operation == '*' || operation == '/'|| operation=='+'||operation=='-'){
        //prompt user for operands necessary for binary arithmetic operations
        printf("You input: %c\n",operation);    //printing operation input
        printf("Enter operand:\n"); //prompt first operand
        scanf(" %f",&operand1); //take first operand
        printf("Enter second operand:\n");  //prompt second operand
        scanf(" %f",&operand2); //take second operand
        printf("You entered:%f %c %f\n",operand1,operation,operand2);   //print whole operation
        
        //perform appropriate binary arithmetic operations
        if(operation=='*'){
            double result = operand1 *operand2;
            printf("Your result is:%f\n",result);
        }
        if(operation=='/'){
            double result = operand1/operand2;
            printf("Your result is:%f\n",result);
        }
        if(operation=='+'){
            double result = Add(operand1,operand2);
            printf("Your result is:%f\n",result);
        }
        if(operation=='-'){
            double result = operand1 - operand2;
            printf("Your result is:%f\n",result);
        }
        
    }
    //checking for valid unary operations
    else if(operation=='m'||operation=='a'||operation=='c'||operation=='f'||operation=='t'){
        //prompt user to enter single operant
        printf("Enter operand:\n");
        scanf(" %f",&operand1);
        //print the operation they have requested
        printf("You entered:%c %f\n",operation,operand1);
        if(operation=='m'){
           
        }
        if(operation=='a'){
            double result = AbsoluteValue(operand1);
            printf("Your result is:%f", result);
        }
        if(operation=='c'){
            
        }
        if(operation=='f'){
            
        }
        if(operation=='t'){
            
        }
    }
    else{
        printf("error invalid operator\n");
    }
    }
    while (1);
}


/********************************************************************************
 * Define the Add function here.
 ********************************************************************************/
double Add(double operand1, double operand2){
    double result = operand1 + operand2;
    return result;
}
/********************************************************************************
 * Define the Subtract function here.
 ********************************************************************************/
double Subtract(double operand1, double operand2)
{
    double result = operand1 - operand2;
    return result;
}

/********************************************************************************
 * Define the Multiply function here.
 ********************************************************************************/
double Multiply(double operand1, double operand2){
    double result = operand1 * operand2;
    return result;
}
/********************************************************************************
 * Define the Divide function here.
 ********************************************************************************/
double Divide(double operand1, double operand2)
{
    double result = operand1/operand2;
    return result;
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double operand){
    if(operand<0){
        double result = operand * -1;
        return result;
    }
    else{
        return operand;
    }
}
/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
double CelsiusToFahrenheit(double operand)
{
    //  Your code here
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/

/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/
double Average(double operand1, double operand2)
{
    //  Your code here
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees.
 ********************************************************************************/


/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
double Round(double operand)
{
    //  Your code here
}


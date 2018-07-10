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
double Divide(double opearand1, double operand2);
double Subtract(double operand1, double operand2);
double CelsiusToFahrenheit(double operand);
double Average(double operand1, double operand2);
double DegreesToRadians(double operand);

//Macros, constants defined for arithmetic and error values
#define PI 3.141592
#define STANDARD_ERROR 0

void CalculatorRun(void)
{
    printf("\n\nWelcome to Jose's calculator program! Compiled at %s %s\n", __DATE__, __TIME__);
    while (1) {
        //Infinite prompt message for operations
        printf("Choose one of the following operations:( '*' , '/' , '+' , '-' , 'm' , 'a' , 'c' , 'f' , 't' )\n");
        char operation; //variable to store user operation input
        scanf(" %c", &operation); //getting operation user input
        double operand1; //operand 1 and 2 used for binary arithmetic functions
        double operand2;
        //checking for valid binary operations
        if (operation == '*' || operation == '/' || operation == '+' || operation == '-' || operation == 'm') {
            //prompt user for operands necessary for binary arithmetic operations
            printf("You input: %c\n", operation); //printing operation input
            printf("Enter operand:\n"); //prompt first operand
            scanf(" %lf", &operand1); //take first operand
            printf("Enter second operand:\n"); //prompt second operand
            scanf(" %lf", &operand2); //take second operand
            printf("You entered:%f %c %f\n", operand1, operation, operand2); //print whole operation

            //perform appropriate binary arithmetic operations
            if (operation == '*') {
                double result = Multiply(operand1, operand2);
                printf("Your result is:%f\n", result);
            }
            if (operation == '/') {
                double result = Divide(operand1, operand2);
                printf("Your result is:%f\n", result);
            }
            if (operation == '+') {
                double result = Add(operand1, operand2);
                printf("Your result is:%f\n", result);
            }
            if (operation == '-') {
                double result = Subtract(operand1, operand2);
                printf("Your result is:%f\n", result);
            }
            if (operation == 'm') {
                double result = Average(operand1, operand2);
                printf("The average is:%f\n", result);
            }

        }//checking for valid unary operations
        else if (operation == 'm' || operation == 'a' || operation == 'c' || operation == 'f' || operation == 't') {
            //prompt user to enter single operand
            printf("Enter operand:\n");
            scanf(" %lf", &operand1);
            //print the operation they have requested
            printf("You entered:%c %f\n", operation, operand1);
            //perform absolute value calculation and print result
            if (operation == 'a') {
                double result = AbsoluteValue(operand1);
                printf("The absolute value is:%f\n", result);
            }
            if (operation == 'c') {
                //perform celsius to fahrenheit conversion and print result with message
                double result = CelsiusToFahrenheit(operand1);
                printf("Your result (from C->F) is:%f degrees Fahrenheit\n", result);
            }
            //perform fahrenheit to celsius conversion and print result with message
            if (operation == 'f') {
                double result = FahrenheitToCelsius(operand1);
                printf("Your result (from F->C) is:%f degrees Celsius\n", result);
            }
            //perform tangent operation with degrees as input and print out result with message
            if (operation == 't') {
                double result = Tangent(operand1);
                printf("Tan(%f)= %f\n", operand1, result);
            }
            //if no valid characters entered print error invalid operator
        } else {
            printf("error invalid operator\n");
        }
    }
    while (1);
}

/********************************************************************************
 * Define the Add function here.
 ********************************************************************************/
double Add(double operand1, double operand2)
{
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
double Multiply(double operand1, double operand2)
{
    double result = operand1 * operand2;
    return result;
}

/********************************************************************************
 * Define the Divide function here.
 ********************************************************************************/
double Divide(double operand1, double operand2)
{
    //check for invalid denominator
    if (operand2 == 0) {
        printf("Error invalid denominator\n");
        return STANDARD_ERROR;
        //else perform division
    } else {
        double result = operand1 / operand2;
        return result;
    }
}

/********************************************************************************
 * Define the Absolute Value function here.
 ********************************************************************************/
double AbsoluteValue(double operand)
{
    //if the number is negative multiply by -1 to get absolute value
    if (operand < 0) {
        double result = operand * -1;
        return result;
        //else return the operand as it is, 0 or positive
    } else {
        return operand;
    }
}

/*********************************************************************************
 * Define the Celsius to Fahrenheit function here.
 ********************************************************************************/
double CelsiusToFahrenheit(double operand)
{
    double result = (9.0 / 5.0) * operand + 32;
    return result;
}

/*********************************************************************************
 * Define the Fahrenheit to Celsius function here.
 ********************************************************************************/
double FahrenheitToCelsius(double operand)
{
    double result = (5.0 / 9.0)*(operand - 32.0);
    return result;
}

/********************************************************************************
 * Define the Average function here.
 *******************************************************************************/
double Average(double operand1, double operand2)
{
    double result = (operand1 + operand2) / 2;
    return result;
}

/*********************************************************************************
 * Define the Tangent function that takes input in degrees.
 ********************************************************************************/
double Tangent(double operand)
//Takes the tangent of the converted degree user input
{
    //check if tangent is invalid at degree input(90N)
    if (((int) operand % (int) 90.0) == 0) {
        printf("Tangent is undefined here\n");
        return STANDARD_ERROR;
    }
        //else turn into radians, then take tangent, and return result
    else {
        double result = DegreesToRadians(operand);
        result = tan(result);
        return result;
    }
}

/*********************************************************************************
 * Define the Round function here.
 * In order to receive the extra credit your calculator MUST ALSO CORRECTLY utilize
 * this function.
 ********************************************************************************/
//double Round(double operand)
//{
//    //  Your code here
//}

//degrees to radians helper function, converts degrees user input into radians for tangent function

double DegreesToRadians(double operand)
{
    double result = operand * (PI / 180);
    return result;
}

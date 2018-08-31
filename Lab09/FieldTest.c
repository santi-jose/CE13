// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>


// User libraries
#include "Field.h"




int main(void)
{
BOARD_Init();
    

    Field *MyField;
    Field *OppField;
    
    MyField = ( Field *)malloc(sizeof(Field));
    OppField = ( Field *)malloc(sizeof(Field));
    
    //FieldInit() Test #1:
    //MyField = MyField->grid[FIELD_ROWS][FIELD_COLS];
    //OppField = OppField->grid[FIELD_ROWS][FIELD_COLS];
    
    
    FieldInit(MyField, OppField);
    
    if (MyField->grid[0][0] == FIELD_SQUARE_EMPTY)
    {
        printf("SUCCESS!! your field square with location (0,0) is empty and hence the field has been initialized!\n");
    }
    else
    {
        printf("ERROR: FieldInit() did not initialize your field");
    }
    if(OppField->grid[0][0] == FIELD_SQUARE_UNKNOWN)
    {
        printf("SUCCESS!! Opponent field square with location (1,1) is empty and thus field has been initialized\n");
    }
    else
    {
        printf("ERROR: FieldInit() did not initialize opponent field");
    }


    //FieldGetSquareStatus() Test 1:
    static int SquareStatus1;
    
    uint8_t row1 = 0;
    uint8_t col1 = 0;
    
    MyField->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
    MyField->grid[row1][col1] = MyField->smallBoatLives;
            
    SquareStatus1 = FieldGetSquareStatus(MyField, row1, col1);
    
    if (SquareStatus1 == FIELD_SQUARE_SMALL_BOAT)
    {
        printf("\n\nSUCCESS! FieldGetSquareStatus returned the square status for a small boat present");
    }
    else
    {
        printf("\n\nERROR: FieldGetSquareStatus() does not work!");
    }
    
    
    static int SquareStatus2;
    uint8_t row2 = 1;
    uint8_t col2 = 1;
    
    MyField->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
    MyField->grid[row2][col2] = MyField->mediumBoatLives;
    
    SquareStatus2 = FieldGetSquareStatus(MyField, row2, col2);
    
    if (SquareStatus2 == FIELD_SQUARE_MEDIUM_BOAT)
    {
        printf("\n\nSUCCESS! FieldGetSquareDtatus returned square status for large boat present");
    }
    else 
    {
        printf("\n\nERROR\n");
    }
    
    
    
    
    //FieldAddBoat() Test 1:
    
    uint8_t AddBoat;
    uint8_t row3 = 0;
    uint8_t col3 = 0;
    AddBoat = FieldAddBoat(MyField, row3, col3, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_MEDIUM);
    if (AddBoat == SUCCESS)
    {
        printf("SUCCESS!! FieldAddBoat() works!");
    }
    else
    {
        printf("ERROR: FieldAddBoat() does not work!");
    }
    
    
    
    //FieldRegisterEnemyAttack() Test 1:
    SquareStatus EnAttack1;
//    EnAttack1 = FieldRegisterEnemyAttack(MyField, );
    
while (1);
}
    #include <stdint.h>
#include "BOARD.h"
#include "Field.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <xc.h>

#include <math.h>


//static Field FieldStatus;


/**
 * This function is optional, but recommended.   It prints a representation of both
 * fields, similar to the OLED display.
 * @param f The field to initialize.
 * @param p The data to initialize the entire field to, should be a member of enum
 *                     SquareStatus.
 */
void FieldPrint_UART(Field *own_field, Field * opp_field);


/**
 * FieldInit() will initialize two passed field structs for the beginning of play.
 * Each field's grid should be filled with the appropriate SquareStatus.
 * Additionally, your opponent's field's boatLives parameters should be filled
 *  (your own field's boatLives will be set when boats are added)
 * 
 * FieldAI_PlaceAllBoats() should NOT be called in this function.
 * 
 * @param own_field     //A field representing the agents own ships
 * @param opp_field     //A field representing the opponent's ships
 */
void FieldInit(Field *own_field, Field * opp_field)
{
    int i = 0;
    int j = 0;
    
    //Each field's grid should be filled with the right SquareStatus
    for (i = 0; i < FIELD_ROWS; i++)
    {
        for (j = 0; j < FIELD_COLS; j++)
        {
            own_field->grid[i][j] = FIELD_SQUARE_EMPTY;         
            opp_field->grid[i][j] = FIELD_SQUARE_UNKNOWN;
        }
    }
    
    //Opponent's field boatlives parameters should be filled, unsure but BoatSize gives number of lives that each boat has. 
    opp_field->hugeBoatLives = FIELD_BOAT_SIZE_HUGE;
    opp_field->largeBoatLives = FIELD_BOAT_SIZE_LARGE;
    opp_field->mediumBoatLives = FIELD_BOAT_SIZE_MEDIUM;
    opp_field->smallBoatLives = FIELD_BOAT_SIZE_SMALL;
    
}

/**
 * Retrieves the value at the specified field position.
 * @param f     //The Field being referenced
 * @param row   //The row-component of the location to retrieve
 * @param col   //The column-component of the location to retrieve
 * @return  SQUARE_STATUS_INVALID if row and col are not valid field locations
 *          Otherwise, return the status of the referenced square 
 */
SquareStatus FieldGetSquareStatus(const Field *f, uint8_t row, uint8_t col)
{
    if (row > FIELD_ROWS)
    {
        if (col > FIELD_COLS)
        {
            return FIELD_SQUARE_INVALID;
        }
    }
    
    
    if (f->grid[row][col] == f->smallBoatLives)
    {
        return FIELD_SQUARE_SMALL_BOAT;
    }
    if (f->grid[row][col] == f->mediumBoatLives)
    {
        return FIELD_SQUARE_MEDIUM_BOAT;
    }
    if(f->grid[row][col] == f->largeBoatLives)
    {
        return FIELD_SQUARE_LARGE_BOAT;
    }
    if(f->grid[row][col] == f->hugeBoatLives)
    {
        return FIELD_SQUARE_HUGE_BOAT;
    }
    
    return 0;
}

/**
 * This function provides an interface for setting individual locations within a Field struct. This
 * is useful when FieldAddBoat() doesn't do exactly what you need. For example, if you'd like to use
 * FIELD_SQUARE_CURSOR, this is the function to use.
 * 
 * @param f The Field to modify.
 * @param row The row-component of the location to modify
 * @param col The column-component of the location to modify
 * @param p The new value of the field location
 * @return The old value at that field location
 */
SquareStatus FieldSetSquareStatus(Field *f, uint8_t row, uint8_t col, SquareStatus p)
{
    SquareStatus Local;
    Local = f->grid[row][col];
    f->grid[row][col] = p;
    return Local;
}

/**
 * FieldAddBoat() places a single ship on the player's field based on arguments 2-5. Arguments 2, 3
 * represent the x, y coordinates of the pivot point of the ship.  Argument 4 represents the
 * direction of the ship, and argument 5 is the length of the ship being placed. All spaces that
 * the boat would occupy are checked to be clear before the field is modified so that if the boat
 * can fit in the desired position, the field is modified as SUCCESS is returned. Otherwise the
 * field is unmodified and STANDARD_ERROR is returned. There is no hard-coded limit to how many
 * times a boat can be added to a field within this function.
 *
 * So this is valid test code:
 * {
 *   Field myField;
 *   FieldInit(&myField,FIELD_SQUARE_EMPTY);
 *   FieldAddBoat(&myField, 0, 0, FIELD_BOAT_DIRECTION_EAST, FIELD_BOAT_TYPE_SMALL);
 *   FieldAddBoat(&myField, 1, 0, FIELD_BOAT_DIRECTION_EAST, FIELD_BOAT_TYPE_MEDIUM);
 *   FieldAddBoat(&myField, 1, 0, FIELD_BOAT_DIRECTION_EAST, FIELD_BOAT_TYPE_HUGE);
 *   FieldAddBoat(&myField, 0, 6, FIELD_BOAT_DIRECTION_SOUTH, FIELD_BOAT_TYPE_SMALL);
 * }
 *
 * should result in a field like:
 *      0 1 2 3 4 5 6 7 8 9
 *     ---------------------
 *  0 [ 3 3 3 . . . 3 . . . ]
 *  1 [ 4 4 4 4 . . 3 . . . ]
 *  2 [ . . . . . . 3 . . . ]
 *  3 [ . . . . . . . . . . ]
 *  4 [ . . . . . . . . . . ]
 *  5 [ . . . . . . . . . . ]
 *     
 * @param f The field to grab data from.
 * @param row The row that the boat will start from, valid range is from 0 and to FIELD_ROWS - 1.
 * @param col The column that the boat will start from, valid range is from 0 and to FIELD_COLS - 1.
 * @param dir The direction that the boat will face once places, from the BoatDirection enum.
 * @param boatType The type of boat to place. Relies on the FIELD_SQUARE_*_BOAT values from the
 * SquareStatus enum.
 * @return SUCCESS for success, STANDARD_ERROR for failure
 */
uint8_t FieldAddBoat(Field *f, uint8_t row, uint8_t col, BoatDirection dir, BoatType boat_type)
{
    BoatType Type = boat_type;                  //Here I am defining a variable of datatype BoatType, set equal to input
    int BoatSize;                               //declare an integer called BoatSize
    
    
    if (Type == FIELD_BOAT_TYPE_SMALL)          /*Check for input*/
    {                                       
        BoatSize = FIELD_BOAT_SIZE_SMALL;
        Type = FIELD_SQUARE_SMALL_BOAT;         //set squarestatus and set
    }
    else if (Type == FIELD_BOAT_TYPE_MEDIUM)
    {
        BoatSize = FIELD_BOAT_SIZE_MEDIUM;
        Type = FIELD_SQUARE_MEDIUM_BOAT;
    }
    else if (Type == FIELD_BOAT_TYPE_LARGE)
    {
        BoatSize = FIELD_BOAT_SIZE_LARGE;
        Type = FIELD_SQUARE_LARGE_BOAT;
    }
    else if(Type == FIELD_BOAT_TYPE_HUGE)
    {
        BoatSize = FIELD_BOAT_SIZE_HUGE;
        Type = FIELD_SQUARE_HUGE_BOAT;
    }
    else 
    {
        BoatSize = 0;
        return STANDARD_ERROR;
    }
    
 

    int i = 0;
//do the boat direction conditions
    if (dir == FIELD_DIR_SOUTH)                     //if the input for direction is set to south,
    {                                               /*Since direction is south, we begin at top of grid,  the input: row determines start location, and end at row + size of boat*/
        while(i < BoatSize)
        {
            i++;                                    /*while integer i is less than the boatsize*/
            if (row + i < FIELD_ROWS)              //Check if input location and boatsize added together exits the grid range; return error if it does
            {
               
                if (f->grid[row + i][col] == FIELD_SQUARE_EMPTY)    //check if the square where we want to place boat is empty
                {
                    f->grid[row+i][col] = Type;
                    
                }
                return SUCCESS;
            }
            else
            {
                return STANDARD_ERROR;
            }
        }
    }
    if (dir == FIELD_DIR_EAST)                      //if input for direction is set to east,
    {
        while(i < BoatSize)                         /*direction is set to east therefore we begin at left hand side of grid and depending on input column, that is our start location; we end at col + size of boat*/
        {
            
            i++;
            if (col + i < FIELD_COLS)
            {
                if (f->grid[row][col + i] == FIELD_SQUARE_EMPTY)
                {
                    f->grid[row][col + i] = Type;
                    
                }
                return SUCCESS;
            }
            else
            {
                return STANDARD_ERROR;
            }
        }
    }    
    return 0;
}

/**
 * This function registers an attack at the gData coordinates on the provided field. This means that
 * 'f' is updated with a FIELD_SQUARE_HIT or FIELD_SQUARE_MISS depending on what was at the
 * coordinates indicated in 'gData'. 'gData' is also updated with the proper HitStatus value
 * depending on what happened AND the value of that field position BEFORE it was attacked. Finally
 * this function also reduces the lives for any boat that was hit from this attack.
 * @param f The field to check against and update.
 * @param gData The coordinates that were guessed. The result is stored in gData->result as an
 *               output.
 * @return The data that was stored at the field position indicated by gData before this attack.
 */
SquareStatus FieldRegisterEnemyAttack(Field *f, GuessData *gData)
{
    int position;
    position = FieldGetSquareStatus(f, gData->row, gData->col);      //attack gets registered at the guessed coordinates   
    
    if (position == FIELD_SQUARE_SMALL_BOAT)                          //the square status gives that there is a small boat
    {
        f->smallBoatLives--;                                        //boat is hit therefore life is reduced
        f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;         //grid gets updated with FIELD_SQUARE_HIT, dependent on coordinates indicated in gData
        gData->result = FIELD_SQUARE_HIT;                           //gData gets updated with proper hitstatus value
    }

   if (position == FIELD_SQUARE_MEDIUM_BOAT)
   {
       f->mediumBoatLives--;
       f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
       gData->result = FIELD_SQUARE_HIT;
   }
    if (position == FIELD_SQUARE_LARGE_BOAT)
    {
        f->largeBoatLives--;
        f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
        gData->result = FIELD_SQUARE_HIT;
    }
    if (position == FIELD_SQUARE_HUGE_BOAT)
    {
        f->hugeBoatLives--;
        f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT;
        gData->result = FIELD_SQUARE_HIT;
    }
    if(position == FIELD_SQUARE_EMPTY)
    {
        f->grid[gData->row][gData->col] = FIELD_SQUARE_MISS;
        gData->result = FIELD_SQUARE_MISS;
    }
    return position;
}


/**
 * This function updates the FieldState representing the opponent's game board with whether the
 * guess indicated within gData was a hit or not. If it was a hit, then the field is updated with a
 * FIELD_SQUARE_HIT at that position. If it was a miss, display a FIELD_SQUARE_EMPTY instead, as
 * it is now known that there was no boat there. The FieldState struct also contains data on how
 * many lives each ship has. Each hit only reports if it was a hit on any boat or if a specific boat
 * was sunk, this function also clears a boats lives if it detects that the hit was a
 * RESULT_*_BOAT_SUNK.
 * @param f The field to grab data from.
 * @param gData The coordinates that were guessed along with their HitStatus.
 * @return The previous value of that coordinate position in the field before the hit/miss was
 * registered.
 */
SquareStatus FieldUpdateKnowledge(Field *f, const GuessData *gData)
{
    SquareStatus Status;
    Status = f->grid[gData->row][gData->col];
    
    if (gData->result == RESULT_HIT)                            //check if the guess data result gives a RESULT HIT
    {
        if (gData->result == RESULT_SMALL_BOAT_SUNK)            //check type of boat that was sunk
        {
            f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT; //field updated
            f->smallBoatLives = 0;                              //small boat lives are cleared since boat was sunk
        }
        if (gData->result == RESULT_MEDIUM_BOAT_SUNK)
        {
            f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT; //guess data resulted in the medium boat sunk, thus update fielt
            f->mediumBoatLives = 0;                             //clear medium boat lives
        }
        if(gData->result == RESULT_LARGE_BOAT_SUNK)
        {
            f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT; //update field after checking that large boat sunk
            f->largeBoatLives = 0;                              //clear large boat lives
        }
        if(gData->result == RESULT_HUGE_BOAT_SUNK)
        {
            f->grid[gData->row][gData->col] = FIELD_SQUARE_HIT; //update field after checking huge boat sinking
            f->hugeBoatLives = 0;                               //clear huge boat lives
        }
    }
    else
    {
        f->grid[gData->row][gData->col] = FIELD_SQUARE_EMPTY;   //if result was not a HIT, display FIELD_SQUARE_EMPTY
    }
    
    return Status;                                              //return status, where value of coordinate position in field before hit/miss was registered was stored 

}

/**
 * This function returns the alive states of all 4 boats as a 4-bit bitfield (stored as a uint8).
 * The boats are ordered from smallest to largest starting at the least-significant bit. So that:
 * 0b00001010 indicates that the small boat and large boat are sunk, while the medium and huge boat
 * are still alive. See the BoatStatus enum for the bit arrangement.
 * @param f The field to grab data from.
 * @return A 4-bit value with each bit corresponding to whether each ship is alive or not.
 */
uint8_t FieldGetBoatStates(const Field *f)
{
    uint8_t LifeStatus;//the 4bit value with each bit corresponding to whether each ship is alive or not
    /*To obtain a 4bit value indicating the alive states of all 4boats, XOR is used since:
     * FIELD_BOAT_STATUS_SMALL = 0b00000000 (small boat sunk)
     * LifeStatus = 0b00001110 (all boat statuses OR with each other, small boat status is sunk; i.e. 0)
     * LifeStatus = 0b00001110 XOR 0b00000000 = 0b00001110 (return)*/
    
    LifeStatus = FIELD_BOAT_STATUS_SMALL | FIELD_BOAT_STATUS_MEDIUM | FIELD_BOAT_STATUS_LARGE | FIELD_BOAT_STATUS_HUGE;
    
    if (f->smallBoatLives == 0)                 //checking if the small boat has been sunk by checking boat lives
    {
        LifeStatus ^= FIELD_BOAT_STATUS_SMALL;      //XOR with small boat status
    }
    if (f->mediumBoatLives == 0)                //checking if medium boat was sunk by checking life equal to zero
    {
        LifeStatus ^= FIELD_BOAT_STATUS_MEDIUM; //XOR with medium boat status
    }
    if (f->largeBoatLives == 0)                 //checking if large boat was sunk by checking life equal to zero
    {
        LifeStatus ^= FIELD_BOAT_STATUS_LARGE;  //XOR with large boat status
    }
    if (f->hugeBoatLives == 0)                  //checking if huge boat was sunk by checking life to zero
    {
        LifeStatus ^= FIELD_BOAT_STATUS_HUGE;   //XOR with huge boat status
    }
    return LifeStatus;                          //4bit value with alive states of all 4 boats   
}


/**
 * This function is responsible for placing all the boats on a field.
 * 
 * @param f         //agent's own field, to be modified in place.
 * @return SUCCESS if all boats could be placed, STANDARD_ERROR otherwise.
 * 
 * This function should never fail when passed a properly initialized field!
 */
uint8_t FieldAIPlaceAllBoats(Field *f);

/**
 * Given a field, decide the next guess.
 *
 * This function should not attempt to shoot a square which has already been guessed.
 *
 * You may wish to give this function static variables.  If so, that data should be
 * reset when FieldInit() is called.
 * 
 * @param f an opponent's field.
 * @return a GuessData struct whose row and col parameters are the coordinates of the guess.  The 
 *           result parameter is irrelevant.
 */
GuessData FieldAIDecideGuess(const Field *f);

/** 
 * For Extra Credit:  Make the two "AI" functions above 
 * smart enough to beat our AI in more than 55% of games.
 */


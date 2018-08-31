//Karla Alvarado            email: kaaalvar@ucsc.edu


#include "Agent.h"
#include "Oled.h"
#include "Buttons.h"
#include "Field.h"
#include "BattleBoats.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>



typedef enum {
    START,
    CHALLENGING,
    ACCEPTING,
    WAITING_TO_SEND,
    ATTACKING,
    DEFENDING,
    END_SCREEN,
            
} AgentStates;


static Field ownField;
static Field oppField;


static AgentState state;

/**
 * The Init() function for an Agent sets up everything necessary for an agent before the game
 * starts.  At a minimum, this requires:
 *      Initializing both fields
 *      Placing boats on your field
 *      Setting the start state of the Agent SM
 * If you are using any other persistent data in Agent SM, that should be reset as well.
 * 
 * The agent can assume that stdlib's rand() function has been seeded properly, so it is not needed
 * to call srand() inside AgentInit().
 *  */
void AgentInit(void)
{
    FieldInit(&ownField, &oppField);                //initializing both fields
                                                                            
    FieldAddBoat(&ownField, 0, 0, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_SMALL);      //Here we place boats on myfield
    FieldAddBoat(&ownField, 0, 1, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_MEDIUM);
    FieldAddBoat(&ownField, 0, 2, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_LARGE);
    FieldAddBoat(&ownField, 0, 3, FIELD_DIR_SOUTH, FIELD_BOAT_TYPE_HUGE);

    state = AGENT_STATE_START;                      //set the start state of Agent SM
}

/**
 * AgentRun evolves the Agent state machine in response to an event.
 * 
 * @param  The most recently detected event
 * @return Message, a Message struct to send to the opponent. 
 * 
 * If the returned Message struct is a valid message
 * (that is, not of type MESSAGE_NONE), then it will be
 * passed to the transmission module and sent via UART.
 * This is handled at the top level! AgentRun is ONLY responsible 
 * for generating the Message struct, not for encoding or sending it.
 */
Message AgentRun(BB_Event event)
{
    switch(state)
    {
        
    }
}

/** * 
 * @return Returns the current state that AgentGetState is in.  
 * 
 * This function is very useful for testing AgentRun.
 */
AgentState AgentGetState(void);

/** * 
 * @param Force the agent into the state given by AgentState
 * 
 * This function is very useful for testing AgentRun.
 */
void AgentSetState(AgentState newState);

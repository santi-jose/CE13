/*
 * File:   Morse.c
 * Author: Jose Luis Santiago jlsantia@ucsc.edu
 *
 * Created on August 17, 2018, 5:00 PM
 */

//include user libraries
#include "Morse.h"
#include "BinaryTree.h"
#include "Buttons.h"

//include public libraries


//create MorseTree and give it valid contents
static Node * MorseTree;
static Node * root;

//STATE enum for MorseCheckEvents state machine

enum MorseState {
    WAITING_FOR_WORD,
    WAITING_FOR_LETTER,
    WAITING_FOR_PULSE,
    DOT,
    DASH
};

//state enum for dashTimer

enum TimerState {
    COUNTDOWN,
    IDLE
};

//helper function prototypes

//timers
void dashTimer(void);
void wordTimer(void);
void letterTimer(void);

//dashTimer event and counter
static enum TimerState dashState = IDLE;
static int dashTimerEvent = FALSE;
static int dashCounter;

//wordTimerEvent and counter
static enum TimerState wordState = IDLE;
static int wordTimerEvent = FALSE;
static int wordCounter;

//letterTimerEvent and counter
static enum TimerState letterState = IDLE;
static int letterTimerEvent = FALSE;
static int letterCounter;


static enum MorseState morseState = WAITING_FOR_WORD; //variable to store state for MorseCheckEvents State Machine 

int MorseInit(void)
{
    //initialize buttons for MorseCheckEvents
    ButtonsInit();

    //five MorseTree it's contents
    MorseTree = TreeCreate(6, "#EISH54V#3UF####2ARL#####WP##J#1TNDB6#X##KC##Y##MGZ7#Q##O#8##90");
    root = MorseTree; //saving root node

    if (MorseTree == NULL) { //if MorseTree gives back an invalid pointer return STANDARD_ERROR
        return STANDARD_ERROR;
    } else { //else return SUCCESS
        return SUCCESS;
    }
}

MorseEvent MorseDecode(MorseEvent input_event)
{

    //decode character via MorseEvents
    if (input_event.type == MORSE_EVENT_DOT) { //dot = LEFT
        if (((MorseTree->leftChild == NULL) || (MorseTree->rightChild == NULL)) || ((MorseTree->leftChild->data == '#')&&(MorseTree->rightChild->data == '#'))) { //if at a leaf or at a node where no more possible characters are available
            input_event.type = MORSE_EVENT_ERROR;
            return input_event;
        }
        MorseTree = GetLeftChild(MorseTree);
    }
    if (input_event.type == MORSE_EVENT_DASH) { //dash = RIGHT
        if (((MorseTree->leftChild == NULL) || (MorseTree->rightChild == NULL)) || ((MorseTree->data == '#')&&((MorseTree->leftChild->data == '#')&&(MorseTree->rightChild->data == '#')))) { //if at a leaf or at a node where no more possible characters are available
            input_event.type = MORSE_EVENT_ERROR;
            return input_event;
        }
        MorseTree = GetRightChild(MorseTree);
    }
    if ((input_event.type == MORSE_EVENT_NEW_LETTER) || (input_event.type == MORSE_EVENT_NEW_WORD)) {
        if (MorseTree->data == '#') { //check to see if appropriate char was decoded
            input_event.type = MORSE_EVENT_ERROR;
            input_event.parameter = MorseTree->data;
            MorseTree = root;
            return input_event;
        }
        input_event.parameter = MorseTree->data;
        input_event.type = MORSE_EVENT_CHAR_DECODED;
        MorseTree = root; //reset tree using root pointer
        return input_event;
    }

    //input_event.type = MORSE_EVENT_NONE; //MORSE_EVENT_NONE if no decoding or traversal error
    return input_event; //return after successful traversal
}

MorseEvent MorseCheckEvents()
{
    uint16_t buttonEvent = ButtonsCheckEvents(); //storing buttonEvent value
    MorseEvent checkEventsReturn; //MorseEvent variable to return
    
        //call timers
        dashTimer();

        wordTimer();

        letterTimer();



    switch (morseState) {
        
    case (WAITING_FOR_WORD):
        if ((buttonEvent & BUTTON_EVENT_4DOWN) == BUTTON_EVENT_4DOWN) { //while WAITING_FOR_WORD, if BUTTON_EVENT_4DOWN set dashTimer to decode dot or dash
            dashTimerEvent = TRUE;
            dashTimer();
            morseState = DOT; //go to DOT state to determine DOT event or DASH event
        }
        break;
    case (WAITING_FOR_LETTER):
        if (wordTimerEvent == FALSE) { //if wordTimerEvent counts down change to WAITING_FOR_WORD state and return MORSE_EVENT_NEW_WORD
            checkEventsReturn.type = MORSE_EVENT_NEW_WORD;
            morseState = WAITING_FOR_WORD;
            return checkEventsReturn;
        }
        if ((buttonEvent & BUTTON_EVENT_4DOWN) == BUTTON_EVENT_4DOWN) { //while WAITING_FOR_LETTER and BUTTON_EVENT_4DOWN start dashTimer and go to DOT state
            dashTimerEvent = TRUE;
            dashTimer();
            morseState = DOT; //go to DOT state to determine DOT or DASH event
        }
        break;
    case (WAITING_FOR_PULSE):
        if (letterTimerEvent == FALSE) { //if letterTimer counts down 
            checkEventsReturn.type = MORSE_EVENT_NEW_LETTER; //store event in struct for return
            morseState = WAITING_FOR_LETTER; //change state to WAITING_FOR_LETTER
            return checkEventsReturn; //return checkEventsReturn
        }
        if ((buttonEvent & BUTTON_EVENT_4DOWN) == BUTTON_EVENT_4DOWN) { //if BUTTON4 pressed down
            dashTimerEvent = TRUE; //turn dashTimer on
            dashTimer(); //call dashTimer state machine
            morseState = DOT; //go to DOT state to determine DOT or DASH event
        }
        break;

    case (DOT):
        if (dashTimerEvent == FALSE) {
            morseState = DASH; //if our dashTimer counts down before we get a BUTTON_EVENT_4UP we go to DASH state
        }
        if ((dashTimerEvent == TRUE) && ((buttonEvent & BUTTON_EVENT_4UP) == BUTTON_EVENT_4UP)) {
            wordTimerEvent = TRUE; //set wordTimer
            letterTimerEvent = TRUE; //set letterTimer
            wordTimer(); //call wordTimer
            letterTimer(); //call letterTimer
            morseState = WAITING_FOR_PULSE; //change state to WAITING_FOR_PULSE
            checkEventsReturn.type = MORSE_EVENT_DOT; //store MORSE_EVENT_DOT in struct.type
            return checkEventsReturn; //return checkEventsReturn with determined buttonevent result in DOT
        }
        break;
    case (DASH):
        if ((buttonEvent & BUTTON_EVENT_4UP) == BUTTON_EVENT_4UP) { //if we get our BUTTON_4UP signal
            wordTimerEvent = TRUE; //turn wordTimer on
            letterTimerEvent = TRUE; //turn letterTimer on
            wordTimer(); //call wordTimer state machine
            letterTimer(); //call letterTimer state machine
            wordState = IDLE;   //set wordTimer state
            morseState = WAITING_FOR_PULSE; //change state to WAITING_FOR_PULSE
            checkEventsReturn.type = MORSE_EVENT_DASH; //store MORSE_EVENT_DASH for return
            return checkEventsReturn; //return checkEventsReturn 
        }
        break;
    }
    checkEventsReturn.type = MORSE_EVENT_NONE; //if nothing happens set to MORSE_EVENT_NONE
    return checkEventsReturn; //return MorseEvent variable type
}

void dashTimer(void)
{
    switch (dashState) {
    case(COUNTDOWN):
        if (dashCounter > 0) { //if there is time left in the COUNTDOWN, COUNTDOWN
            dashCounter--;
            dashState = COUNTDOWN;
        } else { //COUNTDOWN is over go to IDLE
            dashTimerEvent = FALSE;
            dashState = IDLE;
        }
        break;
    case(IDLE):
        if (dashTimerEvent == TRUE) { //if timerEvent triggered, give dashCounter it's initial value, and go to COUNTDOWN state
            dashCounter = MORSE_DOT_TIMEOUT; //store dot timeout for countdown
            dashState = COUNTDOWN;
        } else {
            dashState = IDLE;
        }
        break;
    }
}

void wordTimer(void)
{

    switch (wordState) {
    case(COUNTDOWN):
        if (wordCounter > 0) { //if there is time left in the COUNTDOWN, COUNTDOWN
            wordCounter--;
            wordState = COUNTDOWN;
        } else { //COUNTDOWN is over go to IDLE
            wordTimerEvent = FALSE;
            wordState = IDLE;
        }
        break;
    case(IDLE):
        if (wordTimerEvent == TRUE) { //if timerEvent triggered, give dashCounter it's initial value, and go to COUNTDOWN state
            wordCounter = MORSE_WORD_TIMEOUT; //store word timeout for countdown
            wordState = COUNTDOWN;
        } else {
            wordState = IDLE;
        }
        break;
    }
}

void letterTimer(void)
{
    switch (letterState) {
    case(COUNTDOWN):
        if (letterCounter > 0) { //if there is time left in the COUNTDOWN, COUNTDOWN
            letterCounter--;
            letterState = COUNTDOWN;
        } else { //COUNTDOWN is over go to IDLE
            dashTimerEvent = FALSE;
            letterState = IDLE;
        }
        break;
    case(IDLE):
        if (letterTimerEvent == TRUE) { //if timerEvent triggered, give dashCounter it's initial value, and go to COUNTDOWN state
            letterCounter = MORSE_LETTER_TIMEOUT; //store letter timeout for countdown
            letterState = COUNTDOWN;
        } else {
            letterState = IDLE;
        }
        break;
    }
}
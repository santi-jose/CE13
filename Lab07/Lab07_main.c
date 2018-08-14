//Jose Santiago jlsantia@ucsc.edu

// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "Adc.h"
#include "Ascii.h"
#include "BOARD.h"
#include "Buttons.h"
#include "Leds.h"
#include "Oled.h"
#include "OledDriver.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>
#include <stdint.h>

// **** Set any macros, preprocessor directives, and typedefs here ****
//macros
#define LONG_PRESS 5    //long press is 1 second. 5HZ conversion = 5
#define TIME 10
#define TEMP 11

//Oled display print string array
char printHUD[100];

//STATE enum

typedef enum {
    SETUP, SELECTOR_CHANGE_PENDING, COOKING, RESET_PENDING
} OvenState;

//MODE enum

typedef enum {
    TOAST, BAKE, BROIL
} OvenMode;

//OvenData struct

typedef struct {
    OvenState state;
    char * mode;
    int temp; //storage for temperature value for updateOLED()
    int minutes; //storage for minutes value for updateOLED()
    int seconds; //storage for seconds value for updateOLED()
    int cookTimeLeft; //cook time that is changing with time(cooktime)
    int initialCookTime;
    int globalTime; //global timer for ISR
    int adcRead; //AdcRead() data storage
    int buttonEvent; //button event flag
    int buttonDownTime; //storage for total button3 down time
    int buttonEventStart; //globalTime storage when button3 is pressed
    int timerEvent; //timer event flag
    int selectOption; //stores our current select option: TIME or TEMP

    //add more members to this struct
} OvenData;

// **** Define any module-level variables here ****
//module-level OvenData variable where I'll be storing the oven data
static OvenData ovenData;


// **** Put any helper functions here ****
void printBakeHUD(OvenData); //function that prints BAKE HUD
void printBroilHUD(OvenData); //function that prints BROIL HUD
void printToastHUD(OvenData); //function that prints TOAST HUD
void buttonEvent3Down(void); //function that performs transition for buttonEvent3Down flag
void longPress(void); //performs long press operation: change SELECT OPTION
void shortPress(void); //performs short press operation: changes MODES
void ADCchanged(void); //function that updates OLED with user input from ADC. Determines whether to update TIME or TEMP as well
void buttonEvent4Down(void); //perform buttonEvent4Down operations
void countdown(void); //performs countdown operation
void reset(void); //function resets ovenData
void button4Pending(void);  //function performs transition from COOKING to PENDING_RESET via btnEvent flag

/*This function will update your OLED to reflect the state .*/
void updateOLED(OvenData ovenData)
{
    //check for ovenData.mode to know what HUD to print

    if (ovenData.mode == "BAKE") {
        printBakeHUD(ovenData);
    }
    if (ovenData.mode == "TOAST") {
        printToastHUD(ovenData);
    }
    if (ovenData.mode == "BROIL") {
        printBroilHUD(ovenData);
    }
}

/*This function will execute your state machine.  
 * It should ONLY run if an event flag has been set.*/
void runOvenSM(void) //state machine
{
    //write your SM logic here.
    switch (ovenData.state) {
    case (COOKING):
        if (ovenData.timerEvent == TRUE) { //check for timer event
            countdown();
            ovenData.timerEvent = FALSE; //reset timerEvent flag
        }
        if (ovenData.buttonEvent == BUTTON_EVENT_4DOWN) {
            button4Pending();
        }
        break;

    case (RESET_PENDING):
        if (ovenData.buttonEvent == BUTTON_EVENT_4UP) {
            ovenData.state = COOKING;   //go back to cooking if just pressed btn4
        }
        if (ovenData.timerEvent == TRUE) {
            ovenData.buttonDownTime = ovenData.globalTime - ovenData.buttonEventStart; //store value of time button4 was down
            if (ovenData.buttonDownTime >= LONG_PRESS) {    //if buttonDownTime >= 1 SEC
                reset();    //reset the ovenData
                ovenData.timerEvent = FALSE;    //reset timerEvent flag
                ovenData.state = SETUP; //go back to SETUP state
            } else {
                updateOLED(ovenData);
            }
        }

        break;

    case (SELECTOR_CHANGE_PENDING):
        if (ovenData.buttonEvent == BUTTON_EVENT_3UP) {
            ovenData.buttonDownTime = ovenData.globalTime - ovenData.buttonEventStart; //calculate btn3 down time
            if (ovenData.buttonDownTime < LONG_PRESS) { //if button was down for a short press
                shortPress();
            } else {
                longPress();
            }
            updateOLED(ovenData); //update OLED
            ovenData.state = SETUP; //change state back to SETUP
        }
        break;

    case (SETUP):
        //check to see if ADC has been changed
        if (AdcChanged() == TRUE) { //if TRUE update adcRead value for either mode, time or temp
            ADCchanged();
        }
        if (ovenData.buttonEvent == BUTTON_EVENT_3DOWN) {
            buttonEvent3Down();
        }
        if (ovenData.buttonEvent == BUTTON_EVENT_4DOWN) {
            buttonEvent4Down();
        } else {
            updateOLED(ovenData); //updateOLED when in SETUP
        }
        break;
    }
}

int main()
{
    BOARD_Init();

    //initalize timers and timer ISRs:
    // <editor-fold defaultstate="collapsed" desc="TIMER SETUP">

    // Configure Timer 2 using PBCLK as input. We configure it using a 1:16 prescalar, so each timer
    // tick is actually at F_PB / 16 Hz, so setting PR2 to F_PB / 16 / 100 yields a .01s timer.
    OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_16, BOARD_GetPBClock() / 16 / 100);

    // Set up the timer interrupt with a medium priority of 4.
    INTClearFlag(INT_T2);
    INTSetVectorPriority(INT_TIMER_2_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_2_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T2, INT_ENABLED);

    // Configure Timer 3 using PBCLK as input. We configure it using a 1:256 prescalar, so each timer
    // tick is actually at F_PB / 256 Hz, so setting PR3 to F_PB / 256 / 5 yields a .2s timer.
    OpenTimer3(T3_ON | T3_SOURCE_INT | T3_PS_1_256, BOARD_GetPBClock() / 256 / 5);

    // Set up the timer interrupt with a medium priority of 4.
    INTClearFlag(INT_T3);
    INTSetVectorPriority(INT_TIMER_3_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_3_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T3, INT_ENABLED);

    // </editor-fold>

    printf("Welcome to jlsantia's Toaster Oven.  Compiled on %s %s\n", __DATE__, __TIME__);

    //INITIALIZING HARDWARE
    OledInit();
    LEDS_INIT();
    AdcInit();

    //give ovenData initial values
    ovenData.mode = "BAKE";
    ovenData.temp = 0;
    ovenData.minutes = 0;
    ovenData.seconds = 0;
    ovenData.state = SETUP;
    ovenData.selectOption = TIME;

    while (1) {
        // Add main loop code here
        runOvenSM();

    }
}

/*The 5hz timer is used to update the free-running timer and to generate TIMER_TICK events*/
void __ISR(_TIMER_3_VECTOR, ipl4auto) TimerInterrupt5Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 12;

    //set TIMER_TICK event
    ovenData.timerEvent = TRUE;

    //increment global timer to keep track of time
    ovenData.globalTime++;
}

/*The 100hz timer is used to check for button and ADC events*/
void __ISR(_TIMER_2_VECTOR, ipl4auto) TimerInterrupt100Hz(void)
{
    // Clear the interrupt flag.
    IFS0CLR = 1 << 8;

    ovenData.buttonEvent = ButtonsCheckEvents();
}

void printBakeHUD(OvenData ovenData)
{
    //print HUD for bake mode

    //add check for time or temp (if ovenData.select == TIME)
    if (ovenData.selectOption == TIME) {

        //Bake HUD with user input on TIME
        sprintf(printHUD,
                "|****|\tMode:%s \n"
                "|____|\t>Time:%d:%d \n"
                "|----|\tTemp:%d F    \n"
                "|____|\t\n",
                ovenData.mode,
                ovenData.minutes, ovenData.seconds,
                ovenData.temp);
        OledDrawString(printHUD);
        OledUpdate();
    }
    if (ovenData.selectOption == TEMP) {
        //Bake HUD with user input on TEMP
        sprintf(printHUD,
                "|****|\tMode:%s \n"
                "|____|\tTime:%d:%d \n"
                "|----|\t>Temp:%d   F\n"
                "|____|\t\n",
                ovenData.mode,
                ovenData.minutes, ovenData.seconds,
                ovenData.temp);
        OledDrawString(printHUD);
        OledUpdate();
    }
}

void printBroilHUD(OvenData ovenData)
{

    //print broil HUD, no option to change temp, just time, temp is static and visible
    sprintf(printHUD,
            "|****|\tMode:%s \n"
            "|____|\t>Time:%d:%d \n"
            "|----|\tTemp:350 F   \n"
            "|____|\t\n",
            ovenData.mode,
            ovenData.minutes, ovenData.seconds);
    OledDrawString(printHUD);
    OledUpdate();
}

void printToastHUD(OvenData ovenData)
{
    //print Toast HUD, only user input is time, temp not visible
    sprintf(printHUD,
            "|****|\tMode:%s \n"
            "|____|\t>Time:%d:%d \n"
            "|----|              \n"
            "|____|              \n",
            ovenData.mode,
            ovenData.minutes, ovenData.seconds,
            ovenData.temp);
    OledDrawString(printHUD);
    OledUpdate();
}

void buttonEvent3Down(void)
{//function that is called when buttonEvent3Down is true
    ovenData.buttonEventStart = ovenData.globalTime; //store time when button 3 pressed
    ovenData.state = SELECTOR_CHANGE_PENDING; //change states from 
}

void shortPress(void)
{
    if (ovenData.mode == "BAKE") { //cycle through modes
        ovenData.selectOption = TIME; //set to default select option when going to BAKE
        ovenData.mode = "TOAST";
    } else if (ovenData.mode == "TOAST") {
        ovenData.mode = "BROIL";
    } else {
        ovenData.mode = "BAKE";
    }
}

void longPress(void)
{
    if (ovenData.mode == "BAKE") {
        if (ovenData.selectOption == TIME) { //if TIME currently selected
            ovenData.selectOption = TEMP; //change to TEMP
        } else if (ovenData.selectOption == TEMP) { //else if TEMP currently selected
            ovenData.selectOption = TIME; //change to TIME
        }
    } else { //if ovenData.mode is not in BAKE just update the OLED again
        updateOLED(ovenData);
    }
}

void ADCchanged(void)
{
    ovenData.adcRead = AdcRead();
    ovenData.adcRead >> 2;

    //check for selection option 
    if (ovenData.selectOption == TIME) {
        ovenData.adcRead + 1;
        ovenData.initialCookTime = ovenData.adcRead;
        ovenData.minutes = ovenData.adcRead / 60;
        ovenData.seconds = ovenData.adcRead % 60;
        ovenData.state = SETUP;
    } else if (ovenData.selectOption == TEMP) {
        ovenData.temp = ovenData.adcRead + 300;

    }
    ovenData.state = SETUP;
    updateOLED(ovenData);
}

void buttonEvent4Down(void)
{
    ovenData.buttonEventStart = ovenData.globalTime; //store button4Down event start time
    updateOLED(ovenData); //update OLED
    ovenData.state = COOKING; //change state to COOKING
}

void countdown(void)
{
    if (ovenData.initialCookTime > 0) {
        ovenData.initialCookTime--; //decrement cook time
        ovenData.minutes = ovenData.initialCookTime / 60; //convert minutes
        ovenData.seconds = ovenData.initialCookTime % 60; //convert seconds
        updateOLED(ovenData); //updateOLED
        ovenData.state = COOKING; //go to COOKING state to continue countdown
    } else { //countdown is over
        reset();
        updateOLED(ovenData);
        ovenData.state = SETUP; //go back to SETUP
    }
}

void reset(void)
{ //resetting ovenData to initial values
    ovenData.temp = 0;
    ovenData.minutes = 0;
    ovenData.seconds = 0;
    ovenData.state = SETUP;
    ovenData.selectOption = TIME;
}

void button4Pending(void)
{
    ovenData.buttonEventStart = ovenData.globalTime; //store time for buttonEventStart
    ovenData.state = RESET_PENDING; //change to RESET_PENDING
}
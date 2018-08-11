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

/*This function will update your OLED to reflect the state .*/
void updateOLED(OvenData ovenData)
{
    //check for ovenData.mode to know what HUD to print

    //GOTTA FIX THE MODE ENUM TO BE ABLE TO CHANGE MODES WITH BUTTONS

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
    case(COOKING):
        break;

    case (RESET_PENDING):
        break;

    case (SELECTOR_CHANGE_PENDING):
        if (ovenData.buttonEvent == BUTTON_EVENT_3UP) {
            ovenData.buttonDownTime = ovenData.globalTime - ovenData.buttonEventStart; //calculate btn3 down time
            if (ovenData.buttonDownTime < LONG_PRESS) { //if button was down for a short press
                if (ovenData.mode == "BAKE") { //cycle through modes
                    ovenData.mode = "TOAST";
                } else if (ovenData.mode == "TOAST") {
                    ovenData.mode = "BROIL";
                } else {
                    ovenData.mode = "BAKE";
                }
            }
            updateOLED(ovenData); //update OLED
            ovenData.state = SETUP; //change state back to SETUP
        }
        break;

    case (SETUP):
        //check to see if ADC has been changed
        if (AdcChanged() == TRUE) { //if TRUE update adcRead value for either mode, time or temp
            ovenData.adcRead = AdcRead();
            ovenData.adcRead >> 2;
            ovenData.minutes = ovenData.adcRead / 60;
            ovenData.seconds = ovenData.adcRead % 60;
            ovenData.state = SETUP;
            updateOLED(ovenData);
        }
        if (ovenData.buttonEvent == BUTTON_EVENT_3DOWN) {

            buttonEvent3Down();
        }
        //            else{
        //                updateOLED(ovenData);
        //            }
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

    //Bake HUD with possible user input for time and temp
    sprintf(printHUD,
            "|****|\tMode:%s \n"
            "|____|\t>Time:%d:%d \n"
            "|----|\tTemp:%d F\n"
            "|____|\t\n",
            ovenData.mode,
            ovenData.minutes, ovenData.seconds,
            ovenData.temp);
    OledDrawString(printHUD);
    OledUpdate();
}

void printBroilHUD(OvenData ovenData)
{
    //print broil HUD, no option to change temp, just time, temp is static and visible
    sprintf(printHUD,
            "|****|\tMode:%s \n"
            "|____|\t>Time:%d:%d \n"
            "|----|\tTemp:350 F\n"
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
            "|----|\t\n"
            "|____|\t\n",
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
//Jose Santiago jlsantia@ucsc.edu

// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"
#include "Oled.h"
#include "OledDriver.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

//Macros
#define ADC_average ((ADC1BUF0 + ADC1BUF1 + ADC1BUF2 + ADC1BUF3 + ADC1BUF4 + ADC1BUF5 + ADC1BUF6 + ADC1BUF7)/8)

//define struct to store ADC event data

struct eventData {
    uint16_t value;
    uint8_t event;
};

int window;

//declare module level struct for ADC data storage
static struct eventData AdcResult;

int main(void)
{
    BOARD_Init();

    printf("Welcome to jlsantia's bounce adc.  Compiled at %s %s", __DATE__, __TIME__);

    // Enable interrupts for the ADC
    ConfigIntADC10(ADC_INT_PRI_2 | ADC_INT_SUB_PRI_0 | ADC_INT_ON);

    // Set B2 to an input so AN0 can be used by the ADC.
    TRISBCLR = 1 << 2;

    // Configure and start the ADC
    // Read AN0 as sample a. We don't use alternate sampling, so setting sampleb is pointless.
    SetChanADC10(ADC_CH0_NEG_SAMPLEA_NVREF | ADC_CH0_POS_SAMPLEA_AN2);
    OpenADC10(
            ADC_MODULE_ON | ADC_IDLE_CONTINUE | ADC_FORMAT_INTG16 | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_ON,
            ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_8 |
            ADC_BUF_16 | ADC_ALT_INPUT_OFF,
            ADC_SAMPLE_TIME_29 | ADC_CONV_CLK_PB | ADC_CONV_CLK_51Tcy2,
            ENABLE_AN2_ANA,
            SKIP_SCAN_ALL
            );
    EnableADC10();

    //initialize OLED
    OledInit();

    //event checker initial values
    AdcResult.event = FALSE;
    AdcResult.value = 0;

    //print statement variables
    char print_statement[100];
    while (1) {
        if (AdcResult.event == TRUE) {
            float percent;
            percent = (AdcResult.value * 100) / 1023;
            sprintf(print_statement, "ADC raw value:%d \nADC percent: %0.0f \n", AdcResult.value, (double) percent); //turn percentage into string
            OledDrawString(print_statement); //print string
            OledUpdate();
            AdcResult.event = FALSE; //update event flag
        }
    }





    while (1);
}

/**
 * This is the ISR for the ADC1 peripheral. It runs continuously triggered by the hardware directly
 * and not called by any code, as all interrupts are. During each run it reads all 8 samples from
 * the ADC (registers ADC1BUF0 through ADC1BUF7), averages them, and stores them in a module-level
 * AdcResult struct. If this averaged ADC value has changed between this run and the last one, the
 * event flag in the AdcResult struct is set to true.
 */
void __ISR(_ADC_VECTOR, IPL2AUTO) AdcHandler(void)
{
    // Clear the interrupt flag.
    INTClearFlag(INT_AD1);

    //store previous ADC average value
    uint16_t avg = ADC_average;
    

    //compare to current ADC average value
    if (AdcResult.value != avg) { //if current ADC_average is different than last one, and leaves our window threshold
        //check for window threshold
        if ((AdcResult.value > avg + 3) || (AdcResult.value < avg - 3)) {
            AdcResult.event = TRUE; //set ADC event to true
            AdcResult.value = ADC_average; //set value to new average
        }
    }

}
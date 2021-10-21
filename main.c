#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "LEDarray.h"
#include "ADC.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void) 
{
    LEDarray_init();
    ADC_init();
    unsigned int max = 0;
    char numdelays = 0; //variable to keep track of number of delays
    
    while (1) {
        if (ADC_getval() > max) {max = ADC_getval();} //get the max value
        if (max > 90) {max = 90;} //saturation
        
        LEDarray_disp_PPM(ADC_getval(),max); //display the current and max value
        
        __delay_ms(100); //10 * 100 ms delays add up to 1 s. 100 ms chosen so the human eye does not really notice the interruption
        numdelays++;
        if (numdelays == 10) {
            max = max - 10; //each drop of 10 turns off 1 LED
            numdelays = 0; //reset delay counter
        }
    }
}
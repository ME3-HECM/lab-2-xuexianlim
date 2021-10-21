#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "LEDarray.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void) 
{
	unsigned int count=0;
    LEDarray_init();
    button_init();
    short int release=1; //variable to check if button has been released
    
    while (1) {
		if (!PORTFbits.RF2 && release) {
            count++;  //increment count every time button pressed and was released from previous press
            release = 0;
            if (count > 511) {count = 0;} //reset if number gets too big
            LEDarray_disp_bin(count); //output a number on the LED array in binary
            
            __delay_ms(500);
            
            while (!PORTFbits.RF2 && !release) {
                count++;
                __delay_ms(50); //delay so human eye can see
                if (count > 511) {count = 0;} //reset if number gets too big
                LEDarray_disp_bin(count); //output a number on the LED array in binary  
            }
            if (PORTFbits.RF2) {
                release = 1;
            }
        }    
    }
}
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "LEDarray.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void) 
{
	unsigned int count=1;
    LEDarray_init();
    short int forward = 0; //1 = scan forwards, 0 = scan backwards
  
    while (1) {
		LEDarray_disp_bin(count); //output a number on the LED array in binary
		__delay_ms(50); // Delay so human eye can see change
        if (count == 1 || count == 256) { //LEDs can only display 2^0 to 2^8
            forward = !forward; //flip scan direction
        }
        if (forward) {count = count * 2;} else {count = count / 2;} //powers of 2 so only a single bit is 1 in binary
    }
}

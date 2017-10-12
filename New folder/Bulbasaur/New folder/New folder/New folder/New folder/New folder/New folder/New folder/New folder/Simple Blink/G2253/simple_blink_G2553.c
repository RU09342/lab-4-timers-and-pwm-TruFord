/*
 * simple_blink_G2553.c
 *
 *  Created on: Oct 10, 2017
 * 	Last Edited: Oct 10, 2017
 *  Original Author: Uknown
 *  Josh Ford
 */

 #include <msp430.h>

 int main(void) {
	WDTCTL = WDTPW | WDTHOLD;		//  watchdog timer

	P1DIR |= 0x01;					// Set P1.0 to output direction


	for(;;) {                       //loop forever
		volatile unsigned int i;	// volatile to prevent optimization

		P1OUT ^= 0x01;				// Toggle P1.0 using exclusive-OR

		i = 10000;					// SW Delay
		do i--;
		while(i != 0);
	}
}

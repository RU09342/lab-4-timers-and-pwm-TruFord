/*
 * off_board_blink_G2553.c
 *
 *  Created on: Oct 10, 2017
 * 	Last Edited: Oct 10, 2017
 *  Original Author: Uknown
 *  Josh Ford
 */

 #include <msp430.h>

 int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;            // watchdog timer
    P1DIR |= (BIT0);                    // Tells the processor that we want to write
        while (1)                      // INFINITE LOOP
        {
           P1OUT ^= (BIT0);          // Exclusive OR so that every time it loops it alternates between being on and off.
           __delay_cycles(100000);  // Delays the clock so that the blinking is actually visible
        }
}

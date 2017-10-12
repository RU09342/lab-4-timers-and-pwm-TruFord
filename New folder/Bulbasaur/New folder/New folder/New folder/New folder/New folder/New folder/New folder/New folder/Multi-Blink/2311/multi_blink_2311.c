/*
 * multi_blink_2311.c
 *
 *  Created on: Oct 10, 2017
 * 	Last Edited: Oct 10, 2017
 *  Original Author: Uknown
 *  Josh Ford
 */

 #include <msp430.h>

 void main(void) {
     WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
     PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on High-Z mode

     P1DIR |= 0x01;                          // Set P1.0, LED1, as an output
     P2DIR |= 0x01;                          // Sets P2.0, LED2, as an output

     for(;;)                                 // For loop runs forever
     {
         volatile unsigned int i;            // volatile to prevent optimization

         P1OUT ^= 0x01;                      // Toggle P1.0, LED1, using XOR
         P2OUT ^= 0x01;                      // Toggle P2.0, LED2, using XOR

         i = 10000;                          // Delay toggling LEDs by running through do-while statement
         do i--;
         while(i != 0);
     }
 }

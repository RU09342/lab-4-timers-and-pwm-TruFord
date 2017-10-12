/*
 * software_pwm_G2553.c
 *
 *  Created on: Oct 10, 2017
 * 	Last Edited: Oct 10, 2017
 *  Original Author: Uknown
 *  Josh Ford
 */


 #include <msp430.h>
 int count = 0;

 void main(void)
 {
     WDTCTL = WDTPW | WDTHOLD;                   // disable watchdog timer
     //PM5CTL0 &= ~LOCKLPM5;                       //disables high impedence mode
 //LED lead
     P1DIR |= BIT0;                              //sets the direction of pin 1 to output
     P1OUT &= ~(BIT0);                           //sets output high


 //Button Jazz
     P1DIR &= ~BIT3;                             //Sets button2, pin1.2 as an input
     P1REN |=  BIT3;                             //Enables the pullup/down resistor
     P1OUT |=  BIT3;                             //Set the resistor to be a pullup resistor

 //Timer Jingle
     TA0CTL = TASSEL_2 + MC_1;                   //Sets Timer A0 to SMCLK, Upmode

     TA0CCTL0 = CCIE;                            //Enables CCR0 interrupt
     TA0CCR0 = 3200;                             //Sets CCR0 to 1 kHz

     TA0CCTL1 = CCIE;                            //Enables CCR1 interrupt
     TA0CCR1 = 1600;                             //Sets CCR1 to .5 kHz

 // Interrupt Enable Jawn
     P1IE |=BIT3;                                //enable the interrupt on Port 1.1
     P1IES |=BIT3;                               //set as falling edge
     P1IFG &=~(BIT3);                            //clear interrupt flag

     _BIS_SR(LPM0_bits+GIE);                     //Enter low power mode, general interrupt enable

 }

 #pragma vector=PORT1_VECTOR
 __interrupt void Port_1(void)
 {

         if(count==10)
         {
             count=0;                            //resets count
             TA0CCR1=0;                          //resets capture compare for Timer A0 (timer counter)
         }
         else
         {
             count++;
             TA0CCR1 = count*420;                //increments but jubluh
         }

     P1OUT ^= BIT0;                              //toggle led
     P1IFG &=~(BIT3);                            //clear interrupt flag
 }

 #pragma vector=TIMER0_A0_VECTOR
 __interrupt void TA0_ISR (void)
 {
     if(count!=0)                                //LED is on while
     {
         P1OUT |= (BIT0);                        //sets output high
     }
 }
 #pragma vector=TIMER0_A1_VECTOR
 __interrupt void TA1_ISR (void)
 {
     if(count!=10)
     {
         P1OUT &= ~(BIT0);                           //sets output high
     }
     TA0IV=0;
 }

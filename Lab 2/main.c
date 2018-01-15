
#include "msp.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define DELAY_COUNT (32) //Delay used for button debounce
#define Proc2 //Button interrupt to LED
#define Proc3 //Interrupt latency test
#define Proc4 //Button interrupts to 8 stage LED
#define Proc5 //Timer Counter Compare interrupt test
#define Proc9 //5Hz LED test
#define Proc10 //Button interrupt to timer interrupt to LED
#define Proc11 //Encoder test

void configure_pins();
void Port1Handler();
void configure_timer_interrupts();
void TimerA0_Handler();

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD; //Stop watchdog timer

    configure_pins(); //Call configure pins function
    configure_timer_interrupts(); //Call configure timer interrupts

    __enable_interrupt(); //Global interrupt enable
    NVIC_EnableIRQ(PORT1_IRQn); //NVIC Port 1 interrupt enable

    while(1){ //Infinite loop for interrupt testing
#ifdef Proc3
        P1OUT |= BIT6; //Output high [pin1.6]
    	P1IFG |= BIT1; //Manually trigger pin1.1 interrupt flag
#endif
    }
}

void configure_pins(){
	//Configures buttons for interrupts
	//Note: pin1.1 is left button, pin 1.4 is right button
	//Note: pin1.7 is activated for interrupts during Encoder test
	P1DIR &= ~(BIT1 | BIT4 | BIT7); //Input direction [pin1.1, 1.4, 1.7]
	P1OUT |= BIT1 | BIT4 | BIT7; //Pullup resistor input [pin1.1, 1.4, 1.7]
	P1REN |= BIT1 | BIT4 | BIT7; //Enable resistor input [pin1.1, 1.4, 1.7]
	P1IFG &= ~(BIT1 | BIT4 | BIT7); //Clear interrupt flags [pin1.1, 1.4, 1.7]
	P1IES |= BIT1 | BIT4 | BIT7; //Falling edge interrupt trigger [pin1.1, 1.4, 1.7]
	P1IE |= BIT1 | BIT4 | BIT7; //Enable interrupts [pin1.1, 1.4, 1.7]

#ifdef Proc2
	//Configures LED which will be toggled by button interrupt
	//Note: pin1.0 is a red LED
	P1DIR |= BIT0; //Output direction [pin1.0]
	P1OUT &= ~BIT0; //Output low [pin1.0]
#endif
#ifdef Proc3
	//Configures pin which will be toggled by button interrupt
    P1DIR |= BIT6; //Output direction [pin1.6]
#endif
#ifdef Proc4
    //Configures RGB LED which will be controlled by button interrupts
    //Note: pin2.0, 2.1, 2.2 are the RGB LED
	P2DIR |= BIT0 | BIT1 | BIT2; //Output direction [pin2.0, 2.1, 2.2]
#endif
#ifdef Proc5
	//Configures LED which will be toggled by timer interrupt
	P1DIR |= BIT0; //Output direction [pin1.0]
#endif
#ifdef Proc9
	//Configures LED and output pin which will be toggled by timer interrupt
	P1DIR |= BIT0 | BIT6; //Output direction [pin1.0, 1.6]
#endif
#ifdef Proc10
	//Configures RGB LED which will be controlled by timer interrupts
	P2DIR |= BIT0 | BIT1 | BIT2; //Output direction [pin2.0, 2.1, 2.2]
#endif
}

void Port1Handler(void){
	volatile uint32_t i;
	if(P1IFG & BIT1){ //Interrupt handler for left button [pin1.1]

#ifdef Proc2
		//Turns LED on/off on button interrupt
		P1OUT ^= BIT0; //Toggle output [pin1.0]
#endif
#ifdef Proc3
		//Turns pin1.6 output low on button interrupt
		//Note: For this procedure the interrupt is triggered in main
		P1OUT &= ~BIT6; //Output low [pin1.6]
#endif
#ifdef Proc4
		//Changes state of RGB LED on button interrupt (left button advance)
		uint8_t temp = P2OUT; //Store value of P2OUT in temporary variable
		temp &= 0b00000111; //Clear all bits unrelated to RGB LED

		if (temp < 7){
			P2OUT++; //Advance RGB LED to next state
		}
		else if (temp == 7){
			P2OUT ^= 0x07; //Rollover RGB LED to first state
		}
#endif
#ifdef Proc10
		//Enable timer interrupts, procedure continued in timer interrupt handler
		TA0CCTL0 |= BIT4; //Capture compare interrupt enabled
		P2OUT |= BIT0; //Activate RGB LED first state
#endif
		for(i=0;i<DELAY_COUNT;i++); //Delay for button debounce
		P1IFG &= ~BIT1; //Clear left button interrupt flag
	}
	else if(P1IFG & BIT4){ //Interrupt handler for right button [pin1.4]

#ifdef Proc4
		//Changes state of RGB LED on button interrupt (right button reverse)
		uint8_t temp = P2OUT; //Store value of P2OUT in temporary variable
		temp &= 0b00000111; //Clear all bits unrelated to RGB LED

		if (temp > 0){
			P2OUT--; //Decrease RGB LED to previous state
		}
		else if (temp == 0){
			P2OUT = 0x07; //Rollover RGB LED to final state
		}
#endif

		for(i=0;i<DELAY_COUNT;i++); //Delay for button debounce
		P1IFG &= ~BIT4; //Clear right button interrupt flag
	}
	else if(P1IFG & BIT7){ //Interrupt handler for pin1.7

#ifdef Proc11
		//Square signal applied to pin1.7 by Waveform Generator triggers interrupts

		static uint32_t irtcount = 0; //Create static counter variable
		irtcount++; //Increment counter when interrupt is triggered
		printf("%d\n",irtcount); //Print value of interrupt counter
#endif
		P1IFG &= ~BIT7; //Clear pin1.7 interrupt flag
	}
}
void configure_timer_interrupts(){
	NVIC_EnableIRQ(TA0_0_IRQn); //NVIC Timer0 interrupt enable
	TA0R = 0; //Reset timer counter
	TA0CTL |= BIT9 | BIT4; //Timer control: SMCLK source, Mode-Control Up mode
	TA0CCTL0 |= BIT4; //Capture compare interrupt enabled

#ifdef Proc5
	//Test timer interrupts for compare values of 1000, 20000, 40000, 65000
	TA0CCR0 = 20000; //Compare value (triggers interrupt when timer matches value)
#endif
#ifdef Proc9
	//Configure capture compare interrupts to trigger at 5 Hz frequency
	TA0CCR0 = 37750; //Compare value set for 5 Hz
	TA0CTL |= BIT6 | BIT7; //Timer control: 1/8 Clock Divider
#endif
#ifdef Proc10
	//Configure capture compare interrupts to trigger every 250ms
	TA0CCR0 = 47188; //Compare value set for 250ms
	TA0CTL |= BIT6 | BIT7; //Timer control: 1/8 Clock Divider
#endif
}

void TimerA0_Handler(void) {
	if(TA0CCTL0 & CCIFG){ //Handler for Capture compare interrupt
		TA0CCTL0 &= ~CCIFG; //Clear capture compare interrupt flag

#ifdef Proc5
		//Turns LED on/off on timer interrupt
		P1OUT ^= BIT0; //Toggle output [pin1.0]
#endif
#ifdef Proc9
		//Turns LED on/off and pin1.6 high/low on timer interrupt
		P1OUT ^= BIT0 | BIT6;
#endif
#ifdef Proc10
		//Button interrupt activates this timer interrupt
		//Button interrupts are disabled
		//Timer interrupts occur every 250ms
		//Every 500ms the RGB LED will advance to next state
		//After final RGB LED state, timer interrupts are disabled
		//Button interrupts are re-enabled

		P1IE &= ~BIT1; //Temporarily disable port 1 interrupts (disable buttons)

		static uint8_t intcount = 0; //Create static interrupt counter variable
		intcount++; //Increment interrupt counter on timer interrupt (every 250ms)

		if(intcount % 2){ //True every 2 timer interrupts (500ms)
			uint8_t temp = P2OUT; //Store value of P2OUT in temporary variable
			temp &= 0b00000111; //Clear bits unrelated to RGB LED

			if (temp < 7){
				P2OUT++; //Advance RGB LED to next state
				TA0CCTL0 &= ~CCIFG; //Clear timer interrupt flag
			}
			else if (temp == 7){
				P2OUT ^= 0x07; //Rollover RGB LED to first state
				TA0CCTL0 &= ~CCIFG; //Clear timer interrupt flag
				TA0CCTL0 &= ~BIT4; //Disable timer interrupts
				P1IE |= BIT1; //Re-enable port 1 interrupts (re-enable buttons)
			}
		}
#endif
	}
}



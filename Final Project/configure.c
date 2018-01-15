/*
 * configure.c
 *
 *  Created on: Dec 4, 2016
 *      Author: Savio
 */
#include "msp.h"
#include "configure.h"

void configure_clock(void){
	//Configure clock
	CS->KEY = 0x695A; //Unlock CS module for register access
	CS->CTL0 = 0; //Reset tuning parameters
	CS->CTL0 = CS_CTL0_DCORSEL_1; //Setup DCO clock (3 MHz)
	//Select ACLK = REFO, SMCLK = MCLK = DCO
	CS->CTL1 = CS_CTL1_SELA_2 | CS_CTL1_SELS_3 | CS_CTL1_SELM_3;
	CS->KEY = 0; //Lock CS module for register access
}

void configure_timer(void){
	//Timer source: SMCLK; Up mode; Prescalar: 1/8
	TIMER_A0->CTL |= TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP | TIMER_A_CTL_ID_3;
	TIMER_A0->R = 0; //reset counter
	TIMER_A0->CCR[0] = 50000; //capture compare value
	NVIC_EnableIRQ(TA0_0_IRQn); //enable timer interrupt
}

void configure_port(void){
	 //pin 5.1 (upper button) configuration
	 P5DIR &= BIT1; //input direction
	 P5OUT |= BIT1; //pullup resistor
	 P5REN |= BIT1;  //enable resistor
	 P5IFG &= ~BIT1; //reset flag
	 P5IES |= BIT1; //falling edge trigger
	 P5IE |= BIT1; //enable interrupt

	 //pin 3.5 (lower button) configuration
	 P3DIR &= BIT5; //input direction
	 P3OUT |= BIT5; //pullup resistor
	 P3REN |= BIT5; //enable resistor
	 P3IFG &= ~BIT5; //reset flag
	 P3IES |= BIT5; //falling edge trigger
	 P3IE |= BIT5; //enable interrupt

     NVIC_EnableIRQ(PORT3_IRQn); //enable port interrupts
	 NVIC_EnableIRQ(PORT5_IRQn);

	//joystick: pin 4.4(y axis); pin 6.0(x axis)
	P6->SEL0 |= BIT0; //Primary mode (ADC)
	P4->SELC |= BIT4; //Tertiary mode (ADC)
}

void configure_ADC(void){
	//Configure ADC - Pulse sample mode; ADC14SC trigger
	//ADC ON, sample period > 30us
	ADC14->CTL0 |= ADC14_CTL0_SHT0_5 | ADC14_CTL0_ON | ADC14_CTL0_SHP;
	ADC14->CTL0 |= ADC14_CTL0_CONSEQ_1;
	//Configure res (10 bit)
	ADC14->CTL1 |= ADC14_CTL1_RES_1;
	//Map joystick analog channels to (x)MEM1/MCTL1 and (y)MEM2/MCTL2
	ADC14->MCTL[0] |= ADC14_MCTLN_INCH_15| ADC14_MCTLN_VRSEL_0;
	ADC14->MCTL[1] |= ADC14_MCTLN_INCH_9 | ADC14_MCTLN_VRSEL_0;
	ADC14->CTL0 |= ADC14_CTL0_ENC; //Enable conversions
	NVIC_EnableIRQ(ADC14_IRQn); //Enable ADC interrupts
}

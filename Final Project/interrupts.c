/*
 * buttoninterrupts.c
 *
 *  Created on: Dec 4, 2016
 *      Author: Savio
 */
#include "msp.h"
#include <stdint.h>
#include "interrupts.h"

extern uint8_t bul_req; //global request counters from main
extern uint8_t mov_req;
extern uint8_t bul_mov_req;

void PORT5_IRQHandler(void){
	//pin 5.1 (upper button)
	if(P5IFG & BIT1){
		P5IE &= BIT1; //disable button interrupt.  Note, this will be enabled again once the bullet is destroyed
		bul_req++; //increment create bullet request counter
		P5IFG &= ~BIT1; //clear flag
	}
}

void PORT3_IRQHandler(void){
	//pin 3.5 (lower button)
	if(P3IFG & BIT5){
		P3IFG &= ~BIT5; //clear flag
		mov_req++; //increment move request counter
	}
}

void TA0_0_IRQHandler(void){
	if(TIMER_A0->CCTL[0] & TIMER_A_CCTLN_CCIFG){
		TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG; //clear flag
		bul_mov_req++; //increment bullet move request counter
	}
}

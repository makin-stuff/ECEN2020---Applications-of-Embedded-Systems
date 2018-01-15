
#include "msp.h"
#include "CircBuff.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define Proc2 //Single character transmit test

void configure_clocks();
void configure_serial_port();
void EUSCIA0_IRQHandler();
void uart_putchar(uint8_t data);

void main(void)
{

    WDTCTL = WDTPW | WDTHOLD; //Stop watchdog timer
    configure_clocks();
    configure_serial_port();

    __enable_interrupt(); //Global interrupt enable


#ifdef Proc2 //Transmit character 0xAA repeatedly
    uint8_t proc2data = 0xAA; //Set character data for transmission
    //uint8_t data = itoa(proc2data);
    while(1){
    	uart_putchar(0xAA); //Pass in data to uart_putchar
    }
#endif
	
}

void configure_clocks(void){
	CS->KEY = 0x695A; //Unlock CS module for register access
	CS->CTL0 = 0; //Reset tuning parameters
	CS->CTL0 = CS_CTL0_DCORSEL_3; //Setup DCO clock (16 MHz)
	//Select ACLK = REFO, SMCLK = MCLK = DCO
	CS->CTL1 = CS_CTL1_SELA_2 | CS_CTL1_SELS_3 | CS_CTL1_SELM_3;
	CS->KEY = 0; //Lock CS module for register access
}

void configure_serial_port(void) {
	//Configure UART pins, set 2-UART pin as primary function
	P1SEL1 &= ~(BIT2 | BIT3);
	P1SEL0 |= BIT2 | BIT3;

	//Configure UART
	UCA0CTLW0 |= UCSWRST; //Put eUSCI in reset
	//Select Frame parameters and clock source
	UCA0CTLW0 &= ~(UCPEN | UCMSB | UC7BIT | UCSPB | UCMODE0 | UCMODE1);
	UCA0CTLW0 |= UCSSEL0 | UCSSEL1; //Set SMCLK = BRCLK

	UCA0BRW = 8; //Set Baud Rate (115200)
	UCA0MCTLW = 0xF7A1; //Set Baud Rate
	UCA0CTLW0 &= ~UCSWRST; //Initialize eUSCI

	UCA0IE |= UCRXIE | UCTXIE; //Enable USCI_A0 RX and TX interrupts

	NVIC->ISER[0] = 1 << ((EUSCIA0_IRQn) & 31); //Enable eUSCIA0 interrupt in NVIC
}

void uart_putchar(uint8_t tx_data){
	while(!(UCA0IFG & UCTXIFG)); //Wait for transmitter ready
	printf("Transmitting...\n");
	UCA0TXBUF = tx_data; //Load data onto buffer for transmission
}

void EUSCIA0_IRQHandler(void){
	uint8_t data;
	if (UCA0IFG & UCRXIFG) { //RX interrupt handler
//		printf("Input get\n");
//		data = UCA0RXBUF;
//		printf("%d\n",data);
//		uart_putchar(data);
	}
	if (UCA0IFG & UCTXIFG) { //TX interrupt handler
		UCA0TXBUF = 0xAA;
	}
}

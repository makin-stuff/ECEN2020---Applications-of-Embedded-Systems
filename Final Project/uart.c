/*
 * uart.c
 *
 *  Created on: Dec 5, 2016
 *      Author: Zach
 */
#include "uart.h"
#include <stdint.h>
#include "msp.h"

void uart_putchar(uint8_t tx_data){
	while(!(UCA0IFG & UCTXIFG)); //Wait for transmitter ready
	UCA0TXBUF = tx_data; //Load data onto buffer for transmission
}

void uart_putchar_n(uint8_t *data, uint32_t length){
	uint32_t i;
	for(i = 0; i< length;i++){ //Iterate through data
		//Transmit 1 character per iteration using putchar function
		uart_putchar(data[i]);
	}
}

void configure_serial_port(void) {
	//Configure UART pins: primary function
	P1SEL0 |= BIT2 | BIT3;
	//Configure UART: SMCLK src
	UCA0CTLW0 |= UCSWRST; //Put eUSCI in reset
	UCA0CTLW0 |= UCSSEL_2;
	UCA0BRW = 26; //Set Baud Rate (115200)
	UCA0CTLW0 &= ~UCSWRST; //Initialize eUSCI
}

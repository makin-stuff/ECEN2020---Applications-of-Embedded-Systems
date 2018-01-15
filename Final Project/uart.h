/*
 * uart.h
 *
 *  Created on: Dec 5, 2016
 *      Author: Zach
 */
#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void uart_putchar(uint8_t tx_data);
//Transmits a single character over UART interface
// by loading data onto TX buffer

void uart_putchar_n(uint8_t *data, uint32_t length);
//Transmits multiple characters over UART interface
// by iterating through data and using single character function

void configure_serial_port(void);
//msp432 configuration for UART

#endif /* UART_H_ */

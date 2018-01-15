//*****************************************************************************
//
// MSP432 main.c template - Empty main
//
//****************************************************************************
#include "msp.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#include "enumerations.h"
#include "structs.h"

//declares functions
#include "logging.h"
#include "configure.h"
#include "initializegame.h"
#include "bulletandtank.h"
#include "interrupts.h"
#include "uart.h"

uint8_t endgame = 1; //global counters
uint8_t mov_req = 0;
uint8_t bul_req = 0;
uint8_t bul_mov_req = 0;


void main(void){

	WDTCTL = WDTPW | WDTHOLD;
	configure_clock();
	configure_timer();
	configure_port();
	configure_serial_port();
	configure_ADC();
	__enable_interrupts();

	objects matrix[100] = {emptyspace}; //define a 10 by ten matrix of zeros
	objects * mat_ptr[100]; //array of pointers to use in functions
	int i;
	for (i=0; i<100; i++){
		mat_ptr[i] = &matrix[i];
	} //assign each element of the array of pointers to the corresponding matrix element
	init_matrix(mat_ptr);  //initialize matrix

	tankstate tank1state; //initialize structs for the two tanks
	tankstate tank2state;
	init_tanks(&tank1state, &tank2state);

	bulletstate tank1bullet;
	bulletstate tank2bullet; //each tank will have a structure for their bullet

	movement index_array[8] = {
			MV_NORTH,
			MV_NORTHEAST,
			MV_EAST,
			MV_SOUTHEAST,
			MV_SOUTH,
			MV_SOUTHWEST,
			MV_WEST,
			MV_NORTHWEST}; //INDEXARRAY


	uart_putchar_n(matrix,100); //display game field
	log_game_start(); //logs start of game
	while(endgame == 1){
		ADC14->CTL0 |= ADC14_CTL0_SC; //Start joystick ADC conversion
		//check counters for control requests
		if(mov_req>0){ //move request
			mov_req--; //decrement counter
			change_dir(&tank1state); //call change direction function
			movetank(mat_ptr, &tank1state, index_array); //call move tank function
			uart_putchar_n(matrix,100); //update game field
		}
		if(bul_req>0){ //shoot request
			bul_req--; //decrement counter
			create_bullet(index_array, mat_ptr, &tank1state, &tank1bullet); //call create bullet
			uart_putchar_n(matrix,100); //update game field
		}
		if(bul_mov_req>0){ //bullet movement request
			bul_mov_req--; //decrement counter
			move_bullet(mat_ptr,&tank1bullet,index_array,&tank1state,&tank2state); //call move bullet
			uart_putchar_n(matrix,100); //update game field
		}

	}
}

/*
 * tank_functions.c
 *
 *  Created on: Dec 4, 2016
 *      Author: Savio
 */
#include "msp.h"
#include <stdint.h>
#include "enumerations.h"
#include "structs.h"
#include "bulletandtank.h"
#include "logging.h"
#define logging

#define THIRD (1023/3) //define area for joystick interpretation
extern uint8_t endgame;

void movetank(objects * mat_ptr[100], tankstate * tank, movement index_array[8]){
	movement index = index_array[tank->dir]; //this index value allows us to move based on the tank's direction
	objects objecttype = *mat_ptr[tank->position + index];  //finds what is in the space tank wants to be move into
	//tank moves into empty space
	if (objecttype == emptyspace ){
		if (tank->tanknumber == tank1){
			*mat_ptr[tank->position] = emptyspace; //set old position to empty
			*mat_ptr[tank->position + index] = tank1; //set new position to tank
#ifdef logging
			log_movement(tank);
#endif
		}
		else if (tank->tanknumber == tank2){
			*mat_ptr[tank->position] = emptyspace;
			*mat_ptr[tank->position + index] = tank2;
#ifdef logging
			log_movement(tank);
#endif
		}
		tank->position += index; //update position in tank struct
	}
	//tank moves into bullet
	else if (objecttype == bullet){
		if (tank->hits < 2){
			tank->hits++; //register as a hit
			TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIE; //disable timer interrupt
			P5IE |= BIT1;	//turn on button interrupt
#ifdef logging
			log_tank_hit(tank);
#endif
			if (tank->tanknumber == tank1){
				*mat_ptr[tank->position] = emptyspace;
				*mat_ptr[tank->position + index] = tank1;
#ifdef logging
				log_movement(tank);
#endif
			}
			else if (tank->tanknumber == tank2){
				*mat_ptr[tank->position] = emptyspace;
				*mat_ptr[tank->position + index] = tank2;
#ifdef logging
				log_movement(tank);
#endif
			}
		}
		else if (tank->hits == 2){
#ifdef logging
			log_game_over(tank);
#endif
			endgame=0; //global to end game loop in main
		}
	}
	//tank moves into barrier or other tank
	else if (objecttype == barrier | objecttype == tank1 | objecttype == tank2) {
#ifdef logging
		log_no_movement(tank);
#endif
	}
}

void change_dir(tankstate * tank){
	ADC14->CTL0 |= ADC14_CTL0_SC; //start ADC conversion
	while(ADC14->CTL0 & ADC14_CTL0_BUSY); //wait for conversion
	xpos = ADC14->MEM[0]; //get data from conversion
	ypos = ADC14->MEM[1];
	//find joystick position using ADC results and update tank direction in struct
	if(ypos >= 2*THIRD){
		if(xpos >= 2*THIRD){
			//northeast
			tank->dir = northeast;
		}
		else if(xpos >= THIRD){
			//north
			tank->dir = north;
		}
		else{
			//northwest
			tank->dir = northwest;
		}
	}
	else if(ypos >= THIRD){
		if(xpos >= 2*THIRD){
			//east
			tank->dir = east;
		}
		else{
			//west
			tank->dir = west;
		}
	}
	else{
		if(xpos >= 2*THIRD){
			//southeast
			tank->dir = southeast;
		}
		else if(xpos >= THIRD){
			//south
			tank->dir = south;
		}
		else{
			//southwest
			tank->dir = southwest;
		}
	}
#ifdef logging
	log_dir_change(tank);
#endif
}

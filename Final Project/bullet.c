/*
 * bullet.c
 *
 *  Created on: Dec 4, 2016
 *      Author: Savio
 */
#include "msp.h"
#include <stdint.h>
#include "bulletandtank.h"
#include "logging.h"
#define logging

extern uint8_t endgame;

void create_bullet(movement index_array[8], objects * mat_ptr[100], tankstate * tank, bulletstate * bul){
	movement index = index_array[tank->dir];  //This will later be added to the position of the tank to get the bullet position
	//tank and bullet in same direction, so tank->dir just gives direction of the bullet
	objects objecttype = *mat_ptr[tank->position + index];  //finds what is in the space bullet wants to be created
	    //bullet created on empty space
		if (objecttype == emptyspace){
				*mat_ptr[tank->position + index] = bullet; //set location as bullet
				bul->dir = tank->dir; //bullet in same direction as tank
				bul->position = tank->position + index; //setting up the bullet struct for movement
				TIMER_A0->CCTL[0] |= TIMER_A_CCTLN_CCIE; //Enable timer interrupt for bullet movement
#ifdef logging
				log_bullet_fired(tank);
#endif
		}
		//bullet created on a barrier
		else if (objecttype == barrier ){
#ifdef logging
			log_bullet_destroyed(bul);
#endif
		}
		//bullet created on another bullet
		else if (objecttype == bullet ){
#ifdef logging
			log_bullet_destroyed(bul);
#endif
		}
		//bullet created on tank 1
		else if (objecttype == tank1 ){
			if (tank->hits < 2){
				tank->hits++; //register as a hit
				tankstate tankhit;
				tankhit.tanknumber = tank1;
#ifdef logging
				log_tank_hit(&tankhit);
#endif
			}
			else if (tank->hits == 2){
				tankstate tankhit;
				tankhit.tanknumber = tank2;
#ifdef logging
				log_game_over(&tankhit);
#endif
				endgame = 0; //global to end game loop in main
			}

		}
		//bullet created on tank 2
		else if (objecttype == tank2 ){
			if (tank->hits < 2){
				tank->hits++; //register as a hit
				tankstate tankhit;
				tankhit.tanknumber = tank2;
#ifdef logging
				log_tank_hit(&tankhit);
#endif
			}
			else if (tank->hits == 2){
				tankstate tankhit;
				tankhit.tanknumber = tank1;
#ifdef logging
				log_game_over(&tankhit);
#endif
				endgame = 0; //global to end game loop in main
			}

		}
}

void move_bullet(objects * mat_ptr[100], bulletstate * bul, movement index_array[8], tankstate * tank_1, tankstate * tank_2){
	movement index = index_array[bul->dir];  //This will later be added to the position of the bullet to get the new bullet position
	objects objecttype = *mat_ptr[bul->position + index];  //finds what is in the space bullet wants to be move into
	    //bullet moves into empty space
		if (objecttype == emptyspace ){
				*mat_ptr[bul->position + index] = bullet; //set new position as bullet
				*mat_ptr[bul->position] = emptyspace; //clear old position
				bul->position += index; //setting up the bullet struct for movement
		}
		//bullet moves into barrier
		else if (objecttype == barrier ){
			TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIE; //disable timer interrupt
			*mat_ptr[bul->position] = emptyspace; //remove bullet
			P5IE |= BIT1; //enable shoot button
#ifdef logging
			log_bullet_destroyed();
#endif

		}
		//bullet moves into another bullet
		else if (objecttype == bullet ){
			TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIE; //disable timer interrupt
			*mat_ptr[bul->position] = emptyspace; //remove bullet
			P5IE |= BIT1; //enable shoot button
#ifdef logging
			log_bullet_destroyed();
#endif
		}
		//bullet moves into tank 1
		else if (objecttype == tank1 ){
			*mat_ptr[bul->position] = emptyspace; //remove bullet
			if (tank_1->hits < 2){
				tank_1->hits ++; //register as a hit
				TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIE; //disable timer interrupt
				P5IE |= BIT1; //enable shoot button
#ifdef logging
				log_tank_hit(tank_1);
#endif

			}
			else if (tank_1->hits == 2){
#ifdef logging
				log_game_over(tank_2); //tank 2 wins
#endif
				endgame = 0; //global to end game loop in main
			}

		}
		//bullet moves into tank 2
		else if (objecttype == tank2 ){
			*mat_ptr[bul->position] = emptyspace; //remove bullet
			if (tank_2->hits < 2){
				tank_2->hits ++; //register as a hit
				TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIE; //disable timer interrupt
				P5IE |= BIT1; //enable shoot button
#ifdef logging
				log_tank_hit(tank_2);
#endif
			}
			else if (tank_2->hits == 2){
#ifdef logging
				log_game_over(tank_1); //tank 1 wins
#endif
				endgame = 0; //global to end game loop in main
			}
		}
}

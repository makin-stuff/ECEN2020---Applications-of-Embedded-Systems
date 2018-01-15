/*
 * initializegame.c
 *
 *  Created on: Dec 4, 2016
 *      Author: Savio
 */
#include "initializegame.h"
#include "msp.h"
#include <time.h>
#include <stdlib.h>
#include "enumerations.h"
#include "structs.h"


void init_matrix(objects * mat_ptr[100]) {
	int i;
	for(i=0; i<10; i++){ //set out edge of playing field to barriers
		*mat_ptr[i]=barrier;
	} //top row barriers
	for(i=10; i<100; i+=10){
		*mat_ptr[i]= barrier;
	} //left side barriers
	for(i=19; i<100; i=i+10){
		*mat_ptr[i] = barrier;
	} //right side barriers
	for(i=91; i<99; i++){
		*mat_ptr[i] = barrier;
	} //bottom barriers

	*mat_ptr[15]= tank1; //initialize tank 1
	*mat_ptr[84]= tank2; //initialize tank 2
	srand(time(NULL)); //initalize for rand
	for(i=0; i<10;i++){
		int pos= rand() % 100; //generate random number
		while (*mat_ptr[pos] != emptyspace) {
			pos= rand() % 100; //reroll if space is occupied
		}
			*mat_ptr[pos]= barrier; // randomly place ten barriers
	}
}

void init_tanks(tankstate * tank1_ptr, tankstate * tank2_ptr) {
	tank1_ptr->tanknumber = tank1;
	tank2_ptr->tanknumber = tank2; //tank number designation
	tank1_ptr->hits = 0;
	tank2_ptr->hits = 0; //both tanks start with 0 hits
	tank1_ptr->dir = south;
	tank2_ptr->dir = north; //initializes direction of tanks
	tank1_ptr->position = 14;
	tank2_ptr->position = 84;// initializes tank's position
}

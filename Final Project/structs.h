/*
 * structs.h
 *
 *  Created on: Nov 28, 2016
 *      Author: Savio
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <stdint.h>

typedef struct tank_state_t{
	volatile uint8_t hits; //tracks how many times the tank has been hit
	volatile direction dir; // tracks what direction the tank is facing
	volatile uint8_t position; // tracks which element of the matrix the tank is in
	objects tanknumber; // identifies the tank (so we can log which tank moved/ got hit)
}tankstate;
// we need to define this struct twice in main for each tank

typedef struct bullet_data_t{
	volatile uint8_t position; //holds current position of bullet
	direction dir; //gives direction bullet will travel in
}bulletstate;

#endif /* STRUCTS_H_ */

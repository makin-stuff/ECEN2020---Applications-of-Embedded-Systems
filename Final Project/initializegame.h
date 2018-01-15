/*
 * initializegame.h
 *
 *  Created on: Nov 28, 2016
 *      Author: Savio
 */

#ifndef initializegame_H_
#define initializegame_H_

#include "enumerations.h"
#include "structs.h"

void init_matrix(objects * mat_ptr[100]);
//takes an array of pointers to the matrix, and initializes the mat_ptr with barriers around the edges
//Also places tanks in the matrix
//Adds 10 random barriers onto the playing field

void init_tanks(tankstate * tank1state, tankstate * tank2state);
// sets each tank's hit value to 0
//also starts the first player facing south and the second player facing north

#endif /* initializegame_H_ */

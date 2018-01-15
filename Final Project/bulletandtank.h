/*
 * bullet.h
 *
 *  Created on: Dec 1, 2016
 *      Author: Savio
 */

#ifndef BULLETANDTANK_H_
#define BULLETANDTANK_H_

//all of these functions will log what they do via uart

//Note, the matrix is 10 by 10, so it is an array with 100 elements.
//So, we just need to interpret the array as a matrix.  So, positions
//0 through 9 would be the first row of the matrix, and 10 through 19
//make up the second row.  This goes on until the last row, of positions 90
//through 99.  So, moving in the matrix is equivalent to changing positions
//in the array

#include "enumerations.h"
#include "structs.h"

void movetank(objects * mat_ptr[100], tankstate * tank, movement index_array[8]);
//this function checks the tankstate structure which tank is moving to move the proper tank.
//Then, it checks which direction and moves the tank accordingly.  To move
// we need to check that the new position is an empty space, then, if it is
//the function sets the new space equal to the tank, and makes it's former position
//an empty space.  It also updates the position variable.

void change_dir(tankstate * tank);
//takes a direction that the tank will change to and a pointer to the tank (that wants to change direction) structure
uint16_t xpos; //data holders for joystick ADC conversions
uint16_t ypos;

void create_bullet(movement index_array[8], objects * mat_ptr[100], tankstate * tank, bulletstate * bul);
//creates a bullet in the matrix using the index array, the matrix of pointers to all the array elements, and
// struct pointers to the tank making the bullet and a bullet structure.
// this function will turn on timer interrupt if the bullet is created in an empty space

void move_bullet(objects * mat_ptr[100], bulletstate * bul, movement index_array[8], tankstate * tank_1, tankstate * tank_2);
//must put pointer to tank 1 and tank 2 in proper order
// takes the index array, the pointer matrix, the bullet's structure, and both tank's structures to move the bullet
//note, this function will propagate the bullet one position each time it is called by the timer interrupt.
//However, once a bullet is destroyed, it will disable the timer interrupt, and enable the button interrupt

#endif /* BULLETANDTANK_H_ */

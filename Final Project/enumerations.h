/*
 * enumerations.h
 *
 *  Created on: Nov 16, 2016
 *      Author: Savio
 */

#ifndef ENUMERATIONS_H_
#define ENUMERATIONS_H_

typedef enum objects_in_matrix_t{
	emptyspace = 0,
	tank1 = 1,
	tank2 = 2,
	bullet = 3,
	barrier = 4,

} objects;

typedef enum direction_t{
	north = 0,
	northeast = 1,
	east = 2,
	southeast = 3,
	south = 4,
	southwest = 5,
	west = 6,
	northwest = 7,
} direction;

typedef enum pos_move_t{
       MV_NORTH = -10,
       MV_NORTHEAST = -9,
	   MV_EAST = 1,
	   MV_SOUTHEAST = 11,
	   MV_SOUTH = 10,
	   MV_SOUTHWEST = 9,
	   MV_WEST = -1,
	   MV_NORTHWEST = -11,
    } movement;

#endif /* ENUMERATIONS_H_ */

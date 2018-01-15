/*
 * logging.h
 *
 *  Created on: Nov 28, 2016
 *      Author: Savio
 */
// We need to log changes of direction of the tanks,  a tank being moved,
// a bullet being fired, a bullet being destroyed, and a tank being hit.  These are in real time,
// so data should be logged as it comes in. The functions transmit the data through uart
#ifndef LOGGING_H_
#define LOGGING_H_

#include "enumerations.h"
#include "structs.h"

void log_dir_change(tankstate * state); //logs direction changes
void log_movement(tankstate *state); //logs movement
void log_bullet_fired(tankstate * tank); //logs bullet fired
void log_bullet_destroyed(); //logs bullet destroyed
void log_tank_hit(tankstate * tank); //logs tank hit
void log_game_start(void); //logs game start
void log_game_over(tankstate * tank); //logs game over
void log_no_movement(tankstate * state); //logs no movement

#endif /* LOGGING_H_ */

/*
 * logging.c
 *
 *  Created on: Dec 4, 2016
 *      Author: Savio
 */
#include "enumerations.h"
#include "structs.h"
#include "logging.h"
#include "uart.h"

void log_dir_change(tankstate * state){
	direction dir_tank = state->dir;
	if(state->tanknumber == tank1){
		switch (dir_tank) {
		case north :
			uart_putchar_n("Tank 1 now facing North\n", 25);
			break;
		case northeast :
			uart_putchar_n("Tank 1 now facing Northeast\n", 9);
			break;
		case east :
			uart_putchar_n("Tank 1 now facing East\n", 24);
			break;
		case southeast :
			uart_putchar_n("Tank 1 now facing southeast\n", 29);
			break;
		case south :
			uart_putchar_n("Tank 1 now facing South\n", 25);
			break;
		case southwest :
			uart_putchar_n("Tank 1 now facing southwest\n", 29);
			break;
		case west :
			uart_putchar_n("Tank 1 now facing west\n", 24);
			break;
		case northwest :
			uart_putchar_n("Tank 1 now facing Northwest\n", 29);
			break;
		}
	}
	else if(state->tanknumber == tank2){
		switch(dir_tank){
		case north :
			uart_putchar_n("Tank 2 now facing North", 23);
			break;
		case northeast :
			uart_putchar_n("Tank 2 now facing Northeast", 27);
			break;
		case east :
			uart_putchar_n("Tank 2 now facing East", 22);
			break;
		case southeast :
			uart_putchar_n("Tank 2 now facing Southeast", 27);
			break;
		case south :
			uart_putchar_n("Tank 2 now facing South", 23);
			break;
		case southwest :
			uart_putchar_n("Tank 2 now facing Southwest", 27);
			break;
		case west :
			uart_putchar_n("Tank 2 now facing West", 22);
			break;
		case northwest :
			uart_putchar_n("Tank 2 now facing Northwest", 27);
			break;
		}
	}
}

void log_no_movement(tankstate * state){
	if(state->tanknumber == tank1){
		uart_putchar_n("Tank 1 cannot move\n", 20);
	}
	else if(state->tanknumber == tank2){
		uart_putchar_n("Tank 2 cannot move\n", 20);
	}
}

void log_movement(tankstate * state){
	direction dir_tank = state->dir;
	if(state->tanknumber == tank1){
		switch(dir_tank){
		case north :
			uart_putchar_n("Tank 1 moved North\n", 20);
			break;
		case northeast :
			uart_putchar_n("Tank 1 moved Northeast\n", 24);
			break;
		case east :
			uart_putchar_n("Tank 1 moved East\n", 19);
			break;
		case southeast :
			uart_putchar_n("Tank 1 moved Southeast\n", 24);
			break;
		case south :
			uart_putchar_n("Tank 1 moved South\n", 25);
			break;
		case southwest :
			uart_putchar_n("Tank 1 moved Southwest\n", 29);
			break;
		case west :
			uart_putchar_n("Tank 1 moved west\n", 19);
			break;
		case northwest :
			uart_putchar_n("Tank 1 moved Northwest\n", 24);
			break;
		}
	}
	else if(state->tanknumber == tank2){
		switch(dir_tank){
		case north :
			uart_putchar_n("Tank 2 moved North", 18);
			break;
		case northeast :
			uart_putchar_n("Tank 2 moved Northeast", 22);
			break;
		case east :
			uart_putchar_n("Tank 2 moved East", 17);
			break;
		case southeast :
			uart_putchar_n("Tank 2 moved Southeast", 22);
			break;
		case south :
			uart_putchar_n("Tank 2 moved East", 18);
			break;
		case southwest :
			uart_putchar_n("Tank 2 moved southwest", 22);
			break;
		case west :
			uart_putchar_n("Tank 2 moved west", 17);
			break;
		case northwest :
			uart_putchar_n("Tank 2 moved Northwest", 22);
			break;
		}
	}
}


void log_bullet_fired(tankstate * tank){
	if (tank->tanknumber == tank1){
		uart_putchar_n("Tank 1 fired a bullet\n", 23);
	}
	else if (tank->tanknumber == tank2){
		uart_putchar_n("Tank 2 fired a bullet\n", 23);
	}
}
void log_bullet_destroyed(void){
	uart_putchar_n("Bullet has been destroyed\n", 27);
}

void log_tank_hit(tankstate * state){

	if (state->tanknumber == tank1){
		uart_putchar_n("Tank 1 has been hit\n", 21);
	}
	else if (state->tanknumber == tank2){
		uart_putchar_n("Tank 2 has been hit\n", 21);
	}
}

void log_game_start(void){
	uart_putchar_n("Game has been started\n", 23);
}

void log_game_over(tankstate * tank){
	//input loser
	if (tank->tanknumber == tank1){
		uart_putchar_n("Tank 1 won the game.  Press reset button for new game\n", 55);
	}
	else if (tank->tanknumber == tank2){
		uart_putchar_n("Tank 2 won the game.  Press reset button for new game\n", 55);
	}
}

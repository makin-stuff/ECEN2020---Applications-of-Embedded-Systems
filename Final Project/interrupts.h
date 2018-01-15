/*
 * configure_button_interrupts.h
 *
 *  Created on: Nov 16, 2016
 *      Author: Savio
 */
#ifndef CONFIGURE_BUTTON_INTERRUPTS_H_
#define CONFIGURE_BUTTON_INTERRUPTS_H_
// All handlers will increment request counters when interrupts occur.
// Request counters are read in main and appropriate functions will be called.
void PORT5_IRQHandler(void);
// Increases bullet request counter. Game loop will call create bullet function.
// This needs to enable a timer interrupt that will then control the movement
// of the bullet.  This should disable port 5 button interrupts, and then
// once the bullet is destroyed, we can enable this button interrupt again

void PORT3_IRQHandler(void);
// Increases movement request counter. Game loop will call change direction and move functions.

void TA0_0_IRQHandler(void);
// Increases bullet movement request counter. Game loop will call move bullet function.

#endif /* CONFIGURE_BUTTON_INTERRUPTS_H_ */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef CIRCBUFF_H_
#define CIRCBUFF_H_
	typedef struct CircBuff_t{
		volatile uint8_t*head;
		volatile uint8_t*tail;
		volatile uint32_t num_items;
		volatile uint32_t length;
		uint8_t * anchor;
	} CircBuff;



#endif /* CIRCBUFF_H_ */

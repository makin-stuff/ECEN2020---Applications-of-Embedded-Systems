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

void InitializeBuffer(CircBuff*buf, uint32_t size){
		buf->length = size;
		buf->anchor = (uint8_t*)malloc(buf->length);
		if(buf->anchor == NULL){
			printf("Allocation FAILED");
		}
		buf->head = buf->anchor;
		buf->tail = buf->anchor;
		buf->num_items = 0;
	}

void ClearBuffer(CircBuff*buf){
	uint32_t i;
	buf->head = buf->anchor;
	for(i=0;i<buf->length;i++){
		*(buf->head) = 0;
		buf->head += 0x02;
	}
}

void DeleteBuffer(CircBuff*buf){
	free((void*)buf->anchor);
}

int8_t BufferFull(CircBuff*buf){
	if(buf->num_items == buf->length){
		return 0;
	}
	return -1;

}

int8_t BufferEmpty(CircBuff*buf){
	if(buf->head == buf->tail){
		if(buf->num_items == 0){
			return 0;
		}
		return -1;
	}
	return -1;
}

void AddItemToBuffer(CircBuff*buf, uint8_t data){
	if(buf->head == buf->tail){
		if(buf->num_items == 0){
			*(buf->head) = data;
			buf->head += 0x02;
			buf->num_items++;
		}
		else{
			printf("Error: Overwriting tail");
		}
	}
	else if(buf->head == (buf->anchor +(0x02 * buf->length))){
		*(buf->head) = data;
		buf->head = buf->anchor;
		buf->num_items++;
	}
	else{
		*(buf->head) = data;
		buf->head += 0x02;
		buf->num_items++;
	}
}

uint8_t RemoveItemFromBuffer(CircBuff*buf){
	uint8_t data;
	if(buf->head == buf->tail){
		if(buf->num_items == 0){
			return NULL;
		}
		else{
			data = *(buf->tail);
			buf->num_items--;
			return data;
		}
	}
	else if(buf->tail == (buf->anchor +(0x02 * buf->length))){
			data = *(buf->tail);
			buf->tail = buf->anchor;
			buf->num_items--;
			return data;
	}
	else{
		data = *(buf->tail);
		buf->tail += 0x02;
		buf->num_items--;
		return data;
	}
}

#endif /* CIRCBUFF_H_ */

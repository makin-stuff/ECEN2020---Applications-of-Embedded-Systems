
#include "CircBuff.h"

void InitializeBuffer(CircBuff*buf, uint32_t size){
		buf->length = size; //Set length value of buffer
		//Set address of buffer start in the heap using malloc
		buf->anchor = (uint8_t*)malloc(buf->length);
		if(buf->anchor == NULL){ //Conditional for failed allocation
			printf("Allocation FAILED");
		}
		buf->head = buf->anchor; //Set head to buffer start
		buf->tail = buf->anchor; //Set tail to buffer start
		buf->num_items = 0; //Set count of items in buffer to 0
	}

void ClearBuffer(CircBuff*buf){
	uint32_t i;
	buf->head = buf->anchor; //Set head to buffer start
	for(i=0;i<buf->length;i++){ //Iterate through entire buffer
		*(buf->head) = 0;  //Clear value held at address
		buf->head += 0x02; //Increment to next address
	}
}

void DeleteBuffer(CircBuff*buf){
	free((void*)buf->anchor); //Free memory allocation of buffer start
}

int8_t BufferFull(CircBuff*buf){ //Returns non-zero value if full
	if(buf->num_items == buf->length){
		return -1;
	}
	return 0;

}

int8_t BufferEmpty(CircBuff*buf){ //Returns non-zero value if empty
	if(buf->head == buf->tail){
		if(buf->num_items == 0){
			return -1;
		}
		return 0;
	}
	return 0;
}

void AddItemToBuffer(CircBuff*buf, uint8_t data){ //Adds data to buffer
	if(buf->head == buf->tail){
		//Conditional for first case after buffer initialization
		if(buf->num_items == 0){
			*(buf->head) = data; //Record data at head location
			buf->head += 0x02; //Increment head location
			buf->num_items++; //Increment counter
		}
		//Conditional for head overlapping tail
		else{
			printf("Error: Overwriting tail");
		}
	}
	//Conditional for head at the 'end' of buffer capacity
	else if(buf->head == (buf->anchor +(0x02 * buf->length))){
		*(buf->head) = data; //Record data
		buf->head = buf->anchor; //Wrap head location to start of buffer
		buf->num_items++; //Increment counter
	}
	//All other cases
	else{
		*(buf->head) = data; //Record data
		buf->head += 0x02; //Increment head location
		buf->num_items++; //Increment counter
	}
}

uint8_t RemoveItemFromBuffer(CircBuff*buf){ //Gather data from buffer
	uint8_t data;
	if(buf->head == buf->tail){
		//Conditional for empty buffer, returns NULL data
		if(buf->num_items == 0){
			return NULL;
		}
		//Conditional for removing data when head and tail match
		else{
			data = *(buf->tail); //Read data held at tail
			*(buf->tail) = 0; //Clear data held at tail
			buf->num_items--; //Decrement counter
			return data; //Return data for use
		}
	}
	//Conditional for tail at end of buffer capacity
	else if(buf->tail == (buf->anchor +(0x02 * buf->length))){
			data = *(buf->tail); //Read data
			*(buf->tail) = 0; //Clear data held at tail
			buf->tail = buf->anchor; //Wrap tail location to buffer start
			buf->num_items--; //Decrement counter
			return data; //Return data for use
	}
	//All other cases
	else{
		data = *(buf->tail); //Read data
		*(buf->tail) = 0; //Clear data held at tail
		buf->tail += 0x02; //Increment tail location
		buf->num_items--; //Decrement counter
		return data; //Return data for use
	}
}

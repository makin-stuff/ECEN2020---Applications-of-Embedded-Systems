#define BLINK_LED
#define SIZE
#define RATE (13721)
#define RATE_TEST
#define FREQ_TEST
#define FUNC
#define DUTY_CYCLE_FUNC
#define DUTY_CYCLE (99)

#include "msp.h"
#include <stdio.h>
#include <stdint.h>

void configure_duty(uint8_t dutyCycle,uint16_t rate, uint8_t *ptrout2);

void main(void){
  WDTCTL = WDTPW | WDTHOLD;       	// Stop watchdog timer

  uint8_t*ptrdir1 = (uint8_t*)0x40004c04; //pointer for P1 direction
  uint8_t*ptrout1 = (uint8_t*)0x40004c02; //pointer for P1 output
  uint8_t*ptrin1 = (uint8_t*)0x40004c00; // pointer for P1 input
  uint8_t*ptrdir2 = (uint8_t*)0x40004c05; // pointer for P2 direction
  uint8_t*ptrout2 = (uint8_t*)0x40004c03; //pointer for P2 out
  uint8_t*ptrin2 = (uint8_t*)0x40004c01;  //pointer for p2 input
// Pointer declarations
  *ptrin1 = 0b00000001;
  *ptrin2 = 0b00000001;

#ifdef BLINK_LED
 int count =0;
 int i, j;

 *ptrdir1 = 0b00000001; //Set pin 1.0 to output direction
 *ptrdir2 = 0b00000010; //Set pin 2.1 to output direction
 while(1) {
    *ptrout1 ^= 0x01; //Toggle pin 1.0 output
    for(j = 0; j < 10000; j++); //Delay
    *ptrout2 ^= 0x02; //Toggle pin 2.1 output
    for(j = 0; j < 10000; j++); //Delay

  count++;
  for (i = 3000; i > 0; i--);
  printf("Testing %d\n", count); //Counter for debug purposes
 }
#endif

#ifdef RATE_TEST
 int i;

 *ptrdir2 = 0b00100000; //Set pin 2.5 to output direction
  while(1){
   *ptrout2 ^= 0b00100000; //Toggle pin 2.5 output
   for(i=0;i<RATE;i++); //Delay with predefined iterations
  }
#endif

#ifdef FREQ_TEST
  int i;

  *ptrdir1 = 0b10000000; //Set pin 1.7 to output direction
  while(1){
   *ptrout1 ^= 0b10000000; //Toggle pin 1.7 output
   for(i=0;i<RATE;i++); //Delay with predefined iterations
  }
#endif

#ifdef DUTY_CYCLE_FUNC

  *ptrdir2 = 0b00100000; //Set pin 2.5 to output direction
  configure_duty((uint8_t)DUTY_CYCLE,(uint16_t)RATE, ptrout2);

#endif

#ifdef SIZE

 int size = sizeof(char);

 printf("Size of a char: %d \n", size);

 size = sizeof(int);

 printf("Size of an int: %d \n", size);

 size = sizeof(short);

 printf("Size of a short: %d \n", size);

 size = sizeof(long);

 printf("Size of a long: %d \n", size);

 size = sizeof(float);

 printf("Size of a float: %d \n", size);

 size = sizeof(double);

 printf("Size of double: %d \n", size);

 size = sizeof(long double);

 printf("Size of a long double: %d \n", size);


 size = sizeof(int8_t);

 printf("Size of an int8_t: %d \n", size);

 size = sizeof(int16_t);

 printf("Size of an int16_t: %d \n", size);

 size = sizeof(int32_t);

 printf("Size of an int32_t: %d \n", size);

 size = sizeof(int64_t);

 printf("Size of an int64_t: %d \n", size);

 size = sizeof(uint8_t);

 printf("Size of an uint8_t: %d \n", size);

 size = sizeof(uint16_t);

 printf("Size of an uint16_t: %d \n", size);

 size = sizeof(int32_t);

 printf("Size of an uint32_t: %d \n", size);

 size = sizeof(uint64_t);

 printf("Size of an uint64_t: %d \n", size);


 size = sizeof(uint8_t*);

 printf("Size of an uint8_t*: %d \n", size);

 size = sizeof(char*);

 printf("Size of an char*: %d \n", size);

 size = sizeof(int*);

 printf("Size of an int*: %d \n", size);

 size = sizeof(unsigned int*);

 printf("Size of an unsigned int*: %d \n", size);

 size = sizeof(uint16_t*);

 printf("Size of an uint16_t*: %d \n", size);
#endif
}

#ifdef FUNC
 void configure_duty(uint8_t dutyCycle,uint16_t rate, uint8_t *ptrout2) {
	 uint16_t iterations = ((rate*2) * dutyCycle)/100;
	 uint16_t i,j;
	 while(1){
		 *ptrout2 = 0b00100000;
	 	for(i=0;i<iterations;i++);
	 	printf("Testing %d, %d\n", i, iterations);
	 	*ptrout2 = 0b00000000;
	 	for(j=0;j<((rate*2)-iterations);j++);
	 	printf("Testing %d\n", j);
	  }
 }
#endif

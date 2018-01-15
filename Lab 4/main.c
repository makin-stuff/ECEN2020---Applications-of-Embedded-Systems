
#include "msp.h"
#include "core_cm4.h"
#define SCB_SCR_ENABLE_SLEEPONEXIT (0x00000002)

void configure_ADC();
void ADC14_IRQHandler();


void main(void)
{
	
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
	configure_ADC();
	__enable_interrupt();
	//Wake up on exit from ISR
	SCB->SCR &= ~SCB_SCR_ENABLE_SLEEPONEXIT;
	
	while(1){
		ADC14->CTL0 |= ADC14_CTL0_SC; //Start conversion
		__sleep(); //Block until conversion finish
		__no_operation(); //No-operation

	}

}

void configure_ADC() {
	//Initialize shared reference module
	//Wait for ref generator to be not busy
	while(REF_A->CTL0 & REF_A_CTL0_GENBUSY);
	//Enable internal 1.2v ref
	REF_A->CTL0 = REF_A_CTL0_VSEL_0 | REF_A_CTL0_ON;
	//Turn on Temperature sensor
	REF_A->CTL0 &= ~REF_A_CTL0_TCOFF;

	//Configure ADC - Pulse sample mode; ADC14SC trigger
	//ADC ON, temperature sample period > 30us
	ADC14->CTL0 |= ADC14_CTL0_SHT0_5 | ADC14_CTL0_ON | ADC14_CTL0_SHP;
	//Configure internal temp sensor channel, set res
	ADC14->CTL1 |= ;
	//Map temp analog channel to MEM0/MCTL0, set 3.3v ref
	ADC14->MCTL0 = ;
	//Enable MCTL0/MEM0 interrupts
	ADC14->IER0 = ;

	//Wait for ref generator to settle
	while(!(REF_A->CTL0 & REF_A_CTL0_GENRDY));
	ADC14->CTL0 |= ADC14_CTL0_ENC; //Enable conversions
	NVIC_EnableIRQ(ADC14_IRQn); //Enable ADC interrupts in NVIC
}

void ADC14_IRQHandler(void){
	if(ADC14->IFGR0 & ADC14IFG0){
		//
	}
}

#include "LPC17xx.h"

#define REDLED      (1<<22)
#define GREENLED    (1<<25)


void configGPIO(void);
void delay();

int main(void) {
	configGPIO();
	/**
	 * Setup
	 */	
	while(1) {
	/**
	 * Polling
	 */
	}
	return 0 ;
}

void configGPIO(void) {
    LPC_PINCON->PINSEL1 &= ~(0x3<<12);      // P0.22 as GPIO
    LPC_GPIO3->FIODIR |= GREENLED;          // Set P3.26 as output
	/**
	 * cfg
	 * LPC_PINCON -> PINSEL0 - PINSEL10
	 * LPC_PINCON->PINMODE4
	 * LPC_GPIO0 -> FIODIR 
	 * 
	 */
}
	
void delay() {
    for(uint32_t i=0; i<DELAY; i++)
        for(uint32_t j=0; j<DELAY; j++);
}

/* Ej 4 GPIO como entrada
 * Entradas P0.1 y P0.0 con pullup
 * identificar en una variables cual o cuales pulsadores han sido presionados
 */

#include "LPC17xx.h"

#include <cr_section_macros.h>

// TODO: insert other include files here
#include <stdio.h>
#include <stdint.h>

// TODO: insert other definitions and declarations here
enum Identificacion {
	ninguno = 3,
	pulsador_1 = 2,
	pulsador_2 = 1,
	pulsador_1y2 = 0
};

uint32_t retardo=600000;

void LPC_config(void);
//void mostrar_Presionados(enum Identificacion);
void delay(uint32_t);
int main(void) {

    // TODO: insert code here
	LPC_config();

	enum Identificacion que_se_pulso = ninguno;
	uint32_t valor_puerto = 0;

    while(1) {
    	while((LPC_GPIO0 -> FIOPIN )==0){
    	}
    	delay(retardo);
    	que_se_pulso = (LPC_GPIO0 -> FIOPIN )& 0b00000011;
    	while((LPC_GPIO0 -> FIOPIN )!=0){
    	}
    	delay(retardo);

    	//mostrar_Presionados(que_se_pulso);
        // "Dummy" NOP to allow source level single
        // stepping of tight while() loop
        __asm volatile ("nop");
    }
    return 0 ;
}

void LPC_config(){
	LPC_PINCON -> PINSEL0 &= ~(0b1111); //P0.1 a P0.0 como GPIO
	LPC_PINCON -> PINMODE0 &= ~(0b1111);//P0.1 a P0.0 con PULLUP
	LPC_GPIO0 -> FIODIR &= ~(0b11);	//P0.4 a P0.0 como entradas digitales
	return;
}

/*
void mostrar_Presionados(enum Identificacion p){
	switch (p){
	case ninguno:
		printf("No se pulso ningun boton");
	case pulsador_1:
		printf("Se pulso el boton 1");
	case pulsador_2:
		printf("Se pulso el boton 2");
	case pulsador_1y2:
		printf("Se pulsaron ambos botones");
	}
	return;
}
*/

void delay(uint32_t t)
{
	uint32_t i;
	for(i=0; i<t; i++);
}

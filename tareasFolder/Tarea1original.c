#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdio.h>
#include <stdint.h>
#include <cr_section_macros.h>

volatile int in_pin_botones;

void delay(void);
void cfgPines(void);
int main(void) {
	cfgPines();
	int mapa[8] = { -1, 0, 1, -1, 2, -1, -1, -1 };
	int jugada_usuario;
	int resultado_partida;
	int resultado[3][3] = {
	        { 0, -1, 1},
	        { 1, 0, -1},
	        {-1, 1, 0}};

	int contador=0;
	int jugada_cpu=0;

    while(1)
    {
    	do{
			jugada_cpu= contador%3;
    		contador++;
    		in_pin_botones = LPC_GPIO0-> FIOPIN & (0b111);
    	}while(in_pin_botones==0);

    	jugada_usuario=mapa[in_pin_botones];

    	if(jugada_usuario==-1){
    		continue;
    	}
    resultado_partida = resultado[jugada_usuario][jugada_cpu];
    if(resultado_partida==1){
    	LPC_GPIO0 -> FIOSET = (1 << 5);
    	delay();
    	LPC_GPIO0 -> FIOCLR = (1 << 5);
    }
    if (resultado_partida==0){
    	LPC_GPIO0 -> FIOSET = (1 << 4);
    	delay();
    	LPC_GPIO0 -> FIOCLR = (1<<4);
    }
    if(resultado_partida==-1){
    	LPC_GPIO0 -> FIOSET = (1<< 6);
    	delay();
    	LPC_GPIO0 -> FIOCLR = (1 <<6);
    }
    printf("Jugada usuario:%d | Jugada CPU:%d | Resultado: %d \n",jugada_usuario,jugada_cpu,resultado_partida);
    while((LPC_GPIO0->FIOPIN & 0b111) != 0);
    }

    return 0 ;
}
void cfgPines(){
    LPC_PINCON -> PINSEL0 &= ~(0x3FFF);
    LPC_PINCON -> PINMODE0 |= (0x3F);
    LPC_GPIO0 -> FIODIR &= ~(0x7);
    LPC_GPIO0 -> FIODIR |= (0b111 << 4);
}

void delay(){
	for(uint32_t i=0;i<4000000;i++);
	for(uint32_t i=0; i<4000000; i++);
}

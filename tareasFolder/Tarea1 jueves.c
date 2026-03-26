/* TP1: implementar juego de piedra, papel o tijera
 * un solo puerto de entradas y salidas
 * 3 salidas P0.6-P0.4
 * 3 entradas P0.2-P0.0
 * 3 botones y 3 leds
 * logica positiva
 *
 */

/* - generacion de random: generar en el while para que no sea predecible
 * - ledResultado: funcion para mostrar resultado con los leds
 * - printf comentado para buildear
 * - usar P0.5-P0.3 como salidas a pesar del enunciado
 * - configurar P0.5-P0.3 como salidas
 * - funcion lecturaPines
 * - funcion configPines
 * - funcion delayShowResult
 * - funcion delayRebote
 * - funcion ledResultado
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdio.h>
#include <cr_section_macros.h>

// TODO: insert other include files here
// TODO: insert other definitions and declarations here
int volatile zbrun;

void configPines(void);
void delayShowResult();
void delayRebote();
void ledResultado(int);
uint8_t lecturaPines();
int main(void) {

	int cata=0;
	int random=0;
	int mapa[8] = { -1, 0, 1, -1, 2, -1, -1, -1 };
	int bruno;
	int resultado[3][3] = {
	        { 0, -1, 1},
	        { 1, 0, -1},
	        {-1, 1, 0}};
	int emi;

	configPines();

    while(1)
    {
    	do{
    		zbrun = lecturaPines();
			cata++;
    		random= cata%3;
    	}while(zbrun==0);
    	delayRebote();
    	if (zbrun != lecturaPines()){
    		continue;
    	}
    	bruno=mapa[zbrun];
    	if(bruno==-1){
    		continue;
    	}
		emi= resultado[bruno][random];

		ledResultado(emi);

		//printf("Jugada usuario:%d | Jugada CPU:%d | Resultado: %d \n",bruno,random,emi  );
		while((lecturaPines()) != 0);
		delayRebote();
    }
    return 0 ;
}

uint8_t lecturaPines(){
	return LPC_GPIO0-> FIOPIN0 & (0b111);
}

void configPines(){
    LPC_PINCON -> PINSEL0 &= ~(0x3FFF);	//GPIO en los primeros 6 pines
    LPC_PINCON -> PINMODE0 |= (0x3F);   //pull down res en los primeros 3 pines - logica positiva
    LPC_GPIO0 -> FIODIR &= ~(0x7);		//entrada en los primeros 3 pines
    LPC_GPIO0 -> FIODIR |= (0b111 << 4);	//salida en los segundos 3 pines
}

void ledResultado(int x){
	LPC_GPIO0 -> FIOSET = (1 << 5+x);
	delayShowResult();
	LPC_GPIO0 -> FIOCLR = (1 << 5+x);
}

void delayShowResult(){
	for(uint32_t i=0;i<4000000;i++);
}

void delayRebote(){
	for(uint32_t i=0;i<40000;i++);
}

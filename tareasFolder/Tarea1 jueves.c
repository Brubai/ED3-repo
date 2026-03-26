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
 *
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdio.h>
#include <cr_section_macros.h>

// TODO: insert other include files here
// TODO: insert other definitions and declarations here
int zbrun;

void delay();
void ledResultado(int);
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


    LPC_PINCON -> PINSEL0 &= ~(0xFFF);	//GPIO en los primeros 6 pines

    LPC_PINCON -> PINMODE0 |= (0x3F);   //pull down res en los primeros 3 pines - logica positiva

    LPC_GPIO0 -> FIODIR &= ~(0x7);		//entrada en los primeros 3 pines
    LPC_GPIO0 -> FIODIR |= (0b111 << 4);	//salida en los segundos 3 pines

    while(1)
    {
    	do{
    		zbrun = LPC_GPIO0-> FIOPIN & (0b111);
			cata++;
    		random= cata%3;
    	}while(zbrun==0);
    	bruno=mapa[zbrun];
    	if(bruno==-1){
    		continue;
    	}
		emi= resultado[bruno][random];

		ledResultado(emi);

		//printf("Jugada usuario:%d | Jugada CPU:%d | Resultado: %d \n",bruno,random,emi  );
		while((LPC_GPIO0->FIOPIN & 0b111) != 0);
    }
    return 0 ;
}
void ledResultado(int x){
	LPC_GPIO0 -> FIOSET = (1 << 4+x);
	delayShowResult();
	LPC_GPIO0 -> FIOCLR = (1 << 4+x);
}

void delayShowResult(){
	for(uint32_t i=0;i<4000000;i++);
}

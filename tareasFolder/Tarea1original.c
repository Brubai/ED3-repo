#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdio.h>
#include <cr_section_macros.h>

int zbrun;
// TODO: insert other include files here
void delay();
// TODO: insert other definitions and declarations here

int main(void) {


	int mapa[8] = { -1, 0, 1, -1, 2, -1, -1, -1 };
	int bruno;
	int emi;
	int resultado[3][3] = {
	        { 0, -1, 1},
	        { 1, 0, -1},
	        {-1, 1, 0}};

	int cata=0;
    LPC_PINCON -> PINSEL0 &= ~(0xFFF);

    LPC_PINCON -> PINMODE0 |= (0x3F);

    LPC_GPIO0 -> FIODIR &= ~(0x7);
    LPC_GPIO0 -> FIODIR |= (0b111 << 4);

    while(1)
    {
    	cata++;
    	int random= cata%3;
    	do{
    		zbrun = LPC_GPIO0-> FIOPIN & (0b111);
    	}while(zbrun==0);
    	bruno=mapa[zbrun];
    	if(bruno==-1){
    		continue;
    	}
    emi= resultado[bruno][random];
    if(emi==1){
    	LPC_GPIO0 -> FIOSET = (1 << 5);
    	delay();
    	LPC_GPIO0 -> FIOCLR = (1 << 5);
    }
    if (emi==0){
    	LPC_GPIO0 -> FIOSET = (1 << 4);
    	delay();
    	LPC_GPIO0 -> FIOCLR = (1<<4);
    }
    if(emi==-1){
    	LPC_GPIO0 -> FIOSET = (1<< 6);
    	delay();
    	LPC_GPIO0 -> FIOCLR = (1 <<6);
    }
    printf("Jugada usuario:%d | Jugada CPU:%d | Resultado: %d \n",bruno,random,emi  );
    while((LPC_GPIO0->FIOPIN & 0b111) != 0);
    }

    return 0 ;
}

void delay(){
	for(uint32_t i=0;i<4000000;i++);

}

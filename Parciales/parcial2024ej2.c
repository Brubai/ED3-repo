/**
Se debe implementar un programa en la **LPC1769 Rev. D**, operando a una frecuencia de **CCLK 
de 100 MHz**,
 para que genere una **forma de onda en la salida analógica (DAC)** en un generador de ondas, 
 utilizando un 
 **botón** para cambiar entre **dos valores de frecuencia** de forma de onda diferentes.
El sistema debe usar la **menor cantidad de memoria posible** y **optimizar el uso de los 
recursos del
 microcontrolador**. La frecuencia de la forma de onda debe ser modificable entre **200 Hz y 
 400 Hz** 
 mediante un botón conectado a un **puerto de entrada**.
El diseño debe incluir la implementación de **técnicas para minimizar el consumo de energía**
 durante 
la generación de la onda, haciendo uso de los **modos de bajo consumo** y **optimización del DAC**.
*/
#include "LPC17xx.h"
#include "lpc17xx_adc.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"

//señal triangular
uint8_t señal* = 0x20000000; //puntero a la señal triangular
señal[muestras] {
    0, 51, 102, 153, 204, 255, 204, 153, 102, 51
};
void cfg_dac(void);
void cfg_ext(void);
void cfg_dma(void);
int main(void){
    SystemInit();
    cfg_dac();

    while(1){
        __WFI();
    }

}
void cfg_dma(void){
    


}
void cfg_dac(void){
    //DAC_init();//seteo pin para salida de dac y configuro bios maximo. en este caso no lo uso porque pide minimo consumo
    PINSEL_CFG_Type cfg;
    cfg.funcNum = PINSEL_FUNC_1;//funcion 1 para dac 
    cfg.pinMode = PINSEL_TRISTATE;//sin pullup ni pulldown
    cfg.openDrain = PINSEL_OD_NORMAL;
    cfg.portNum = PINSEL_PORT_0;
    cfg.pinNum = PINSEL_PIN_26;//p0.26
    PINSEL_ConfigPin(&cfg);
    GPIO_SetDir(0, (1<<26), 1);//salida
    
    DAC_SetBias(DAC_350uA);//seteo bios minimo para menor consumo
    DAC_UpdateValue(0);
    DAC_CONVERTER_CFG_Type cfgdac;
    cfgdac.counterEnable = DISABLE;
    cfgdac.dmaEnable = ENABLE;//habilito dma
    cfgdac.doubleBufferEnable = DISABLE;
    DAC_ConfigDAConverterControl(&cfgdac);

    DAC_SetDMATimeOut();//TIME OUT PARA DMA . (100Mhz/4)/(frecuencia*muestras)
    // (1000000000/4)(400/)
    
}
void cfg_ext(void){//CONFIGURO INTERRUPCION PARA BOTON. 
    PINSEL_CFG_Type cfg;
    cfg.Funcnum = PINSEL_FUNC_0;//gpio
    cfg.OpenDrain = PINSEL_OD_NORMAL;
    cfg.Pinmode = PINSEL_TRISTATE;
    cfg.Portnum = PINSEL_PORT_2;
    cfg.Pinnum = PINSEL_PIN_10;
    PINSEL_ConfigPin(&cfg);
    GPIO_SetDir(2, (1<<10), 0);//entrada
    GPIO_IntCmd(2, (1<<10), 1);
    NVIC_EnableIRQ(EINT3_IRQn);//habilito interripcion
    NVIC_SetPendingIRQ(EINT3_IRQn,1);//seteo la interrupcion
}

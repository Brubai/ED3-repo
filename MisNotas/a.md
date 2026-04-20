
---

- [[#Bloques lógicos|Bloques lógicos]]
- [[#Números|Números]]
- [[#Funciones|Funciones]]
- [[#Interrupciones|Interrupciones]]
- [[#Registros|Registros]]
	- [[#Registros#Control de pines|Control de pines]]
	- [[#Registros#Control de Interrupciones por GPIO|Control de Interrupciones por GPIO]]
	- [[#Registros#Control del Módulo Systick|Control del Módulo Systick]]
	- [[#Registros#Control del Módulo TIMER|Control del Módulo TIMER]]
	- [[#Registros#Control del Módulo ADC|Control del Módulo ADC]]
- [[#Configuración de Puertos a Nivel de Hardware|Configuración de Puertos a Nivel de Hardware]]
	- [[#Configuración de Puertos a Nivel de Hardware#PINSEL (Pin Function Select register)|PINSEL (Pin Function Select register)]]
	- [[#Configuración de Puertos a Nivel de Hardware#PINMODE (Pin Mode Select register)|PINMODE (Pin Mode Select register)]]
	- [[#Configuración de Puertos a Nivel de Hardware#PINMODE_OD (Open Drain Pin Mode Select register)|PINMODE_OD (Open Drain Pin Mode Select register)]]
- [[#Configuración de Puertos a Nivel de Software|Configuración de Puertos a Nivel de Software]]
	- [[#Configuración de Puertos a Nivel de Software#Registros FIO|Registros FIO]]
	- [[#Configuración de Puertos a Nivel de Software#Configuración de Interrupciones por GPIO|Configuración de Interrupciones por GPIO]]
- [[#NVIC functions|NVIC functions]]
- [[#Librerías|Librerías]]
- [[#Repositorios|Repositorios]]


- [Bloques lógicos](#Bloques%20l%C3%B3gicos)
- [Números](#N%C3%BAmeros)
- [Funciones](#Funciones)
- [Interrupciones](#Interrupciones)
- [Registros](#Registros)
	- [Control de pines](#Control%20de%20pines)
	- [Control de Interrupciones por GPIO](#Control%20de%20Interrupciones%20por%20GPIO)
	- [Control del Módulo Systick](#Control%20del%20M%C3%B3dulo%20Systick)
	- [Control del Módulo TIMER](#Control%20del%20M%C3%B3dulo%20TIMER)
	- [Control del Módulo ADC](#Control%20del%20M%C3%B3dulo%20ADC)
- [Configuración de Puertos a Nivel de Hardware](#Configuraci%C3%B3n%20de%20Puertos%20a%20Nivel%20de%20Hardware)
	- [PINSEL (Pin Function Select register)](#PINSEL%20(Pin%20Function%20Select%20register))
	- [PINMODE (Pin Mode Select register)](#PINMODE%20(Pin%20Mode%20Select%20register))
	- [PINMODE_OD (Open Drain Pin Mode Select register)](#PINMODE_OD%20(Open%20Drain%20Pin%20Mode%20Select%20register))
- [Configuración de Puertos a Nivel de Software](#Configuraci%C3%B3n%20de%20Puertos%20a%20Nivel%20de%20Software)
	- [Registros FIO](#Registros%20FIO)
	- [Configuración de Interrupciones por GPIO](#Configuraci%C3%B3n%20de%20Interrupciones%20por%20GPIO)
- [NVIC functions](#NVIC%20functions)
- [Librerías](#Librer%C3%ADas)
- [Repositorios](#Repositorios)

[Bloques](#Bloques%20lógicos)
# Bloques lógicos
Core ^115660
- DMA - (Direct Memory Access)
- MPU - (Memory Protection Unit)
- ITM - (Instrumentation Trace Macrocell)
- PLL - (Phase-Locked Loop)
- WIC - (Wake-up Interrupt Controller)
- SCS - (System Control Space)
- NVIC - (Nested Vectored Interrupt Controller)
- SCB - (System Control Block)
- Systick Timer - (System Tick Timer)

Core outside - periféricos
- GPIO - (General Purpose Input/Output)
- TIMER0
- ADC

Otras definiciones
- CMSIS - (Cortex Microcontroller Software Interface Standard)
- NMI - (Non-Maskable Interrupt)
- IRQ - (Interrupt Request)
- EXTI - (External Interrupt)
- PWM - (Pulse Width Modulation)

# Números
- La LPC1769 cuenta con 4 Timers de 32 bits

- La LPC1769 cuenta con un solo bloque conversor AD0CR
	- presenta una tasa de conversion de 12-bit
	- frecuencia máxima de muestreo de 200 KHz
	- 8 canales de entrada
	- Las conversiones se realizan en 64 ciclos de reloj en modo de Disparo continuo - Ráfaga -> frecuencia de trabajo del ADC de 12,5 MHz
	- Si está en modo Controlado por algun Trigger, las conversiones se realizan en 65 ciclos de reloj -> frecuencia de trabajo del ADC de 13 MHz
	

---
# Funciones
```c
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif
#include <stdio.h>

void cfgGPIO(void);
void cfgIntExt(void);
void cfgSysTick(void);

int main(void)
{
	cfgGPIO();
	cfgIntExt();
	cfgSysTick();
	while(1){};
    return 0 ;
}

void cfgGPIO(void)
{
	//...
	return;
}

void cfgIntGPIO(void)
{
	// P0.15 - Habilitar Interrupcion - Rising Edge
	LPC_GPIOINT->IO0IntEnR |= (1<<15);
	
	// P0.15 - Limpiar flag
	LPC_GPIOINT->IO0IntClr |= (1<<15);
	
	// Prioridad - 1 - Interr Externa EINT3
	NVIC_SetPriority(EINT3_IRQn,1);
	
	// Habilitar Interr - EINT3
	NVIC_EnableIRQ(EINT3_IRQn);
	
	return;
}

void cfgIntExt(void)
{
	
}

void cfgSysTick(void)
{
	/* 	Algunos ejercicios piden 
			- sacar la señal de systick por un pin como salida
			- Setear una prioridad 
			- pasar valores por parámetro de función, para LOAD y CTRL
	*/
	// LPC_GPIO0->FIOSET |= (1<<22);

	// Valor del registro RELOAD - numero de cuentas max de 12 bits
	SysTick->LOAD = nticks_1ms;

	// Valor del registro de contador actual - generalmente se asigna 0
	SysTick->VAL = 0;

	// Registro de control de SysTick - Habilitar contador - Habilitar interrupt - CPU clock como fuente de reloj
	SysTick->CTRL |= (7<<0);
	
	// Prioridad - 1 - Interr de Systick
	NVIC_SetPriority(SysTick_IRQn, 1);
	
	return;
}

void EINT0_IRQHandler(void)
{
	// Consulta si hay una interrupción pendiente - en el puerto 0
	if (LPC_GPIOINT->IntStatus & (1<<0))
	{
		// Consulta si ocurrió una interrupción - en el pin 15
		if (LPC_GPIOINT->IO0IntStatR & (1<<15))
		{
			// servicio de interrupción

			// Limpiar flag al terminar el servicio
			LPC_GPIOINT->IO0IntClr |= (1<<15);
		}
	}

	return;
}
void SysTick_IRQHandler(void)
{
	// Linea que recomienda poner el fabricante - antes de terminar el handler del SysTick
	SysTich->CTRL &= Systick->CTRL;

	return;
}
```

^c69d58

---

# Interrupciones 
- Representan un número del enum definido en el archivo LPC17xx.h, como tipo IRQn
	- EINT0_IRQn
	- EINT1_IRQn
	- EINT2_IRQn
	- EINT3_IRQn
	- SysTick_IRQn

---

# Registros 

^e76ac2

>Se listan los nombres de los miembros de las estructuras, podemos acceder a ellos con el operador `->` sobre el puntero de la estructura
>Y arriba de cada lista, los nombres con que se definieron el puntero a la propia estructura

>fuente:	librería:	CMSISv2p00_LPC17xx

>Por Favor ver antes los registros en el MANUAL DE USUARIO, este es solo un resúmen esquemático
## Control de pines 

>Revisar manual de Usuario para ver mapeo de pines en los registros

>Revisar manual de Usuario para ver todos los registros 
> - PINSEL0:PINSEL9 (5 puertos mitad alta y mitad baja)* => Cada pin se controla con 2 bits
> - PINMODE0:PINMODE9 (5 puertos mitad alta y mitad baja)* => Cada pin se controla con 2 bits
> - PINMODE_OD0 (5 puertos) => Cada pin se controla con 1 bit
> - LPC_GPIO0:LPC_GPIO4 (5 puertos) => Cada pin se controla con 1 bit para todos los Registros de la Estructura

> - \* no todos los registros son completamente accesibles, habrá registros, pines y bits reservados

- ### Configuración a nivel de hardware 

	- #### Puntero de estructura para configuración de pines `LPC_PINCON`
	  `LPC_PINCON ->` __Pin Connect__

	- Registros por Puerto
		
		- `PINSEL0` __Pin Select-0__ 
		  >Puerto 0 mitad baja - Selección de función de cada pin -> 2 bits por pin (`PINSEL9` : `PINSEL0`) -> dos registros por puerto (Mitad Alta y Baja)
		
		- `PINMODE0` __Pin Mode-0__ 
		  >Puerto 0 mitad baja - Modo de entrada de cada pin -> 2 bits por pin (`PINMODE9` : `PINMODE0`) -> dos registros por puerto (Mitad Alta y Baja)
		
		- `PINMODE_OD0` __Pin Mode-OpenDrain-0__ 
		  >Puerto 0 - Modo Open drain de cada pin (`PINMODE_OD4` : `PINMODE_OD0`) -> un registro por puerto

- ### Configuracion a nivel de software

	- #### Puntero de estructura por Puerto  `LPC_GPIO0`
	  `LPC_GPIO0 ->` __General Purpose Input/Output Port-0__ 
	  (`LPC_GPIO4 : LPC_GPIO0`) Para cada puerto, están los siguientes registros:

	- `FIODIR` __Fast GPIO Port Direction control register__

	- `FIOMASK` __Fast Mask register for port__

	- `FIOPIN` __Fast GPIO port Pin value register__

	- `FIOSET` __Fast GPIO port output Set register__

	- `FIOCLR` __Fast GPIO port output Clear register__



## Control de Interrupciones por GPIO

- ### Puntero base de estructura `LPC_GPIOINT` :
   `LPC_GPIOINT ->` __General Purpose Input/Output Interrution__

- __Enable Register for GPIO Interrupt__ - for port 0 and 2 - for Rising and Falling edge
	- `IO0IntEnR`
	- `IO2IntEnR`
	- `IO0IntEnF`
	- `IO2IntEnF`

- __Status Register for GPIO Interrupt__ - for port 0 and 2 - for Rising and Falling edge
	- `IO0IntStatR`
	- `IO2IntStatR`
	- `IO0IntStatF`
	- `IO2IntStatF`

- __Clear Register for GPIO Interrupt__ - for port 0 and 2
	- `IO0IntClr`
	- `IO2IntClr`

- __Overall Status Register for GPIO Interrupt__
	- `IOIntStatus`

- __External Interrupt__
	- `EXTINT` __Flag register__
	- `EXTMODE` __Mode register__
	- `EXTPOLAR` __Polarity register__

## Control del Módulo Systick

- ### Puntero a base de estructura `Systick`
   `Systick ->` System Timer

- System Timer Registers 
	- `CTRL` __Control and Status__
		- bit-0 - ENABLE -  Habilitar el contador
		- bit-1 - TICKINT - Habilitar el interrupt del contador
		- bit-2 - CLKSOURCE - Selección de la fuente del clock 
		- bit-16 - COUNTFLAG - Bandera del contador cuando llega a `0` 
		  Se limpia autom. a  `0` cuando se lee el registro

	- `LOAD` __Reload Value__ (23 bits) #Register - El valor que será cargado en el Timer cuando llega a `0` 
	- `VAL` __Current Value__ (23 bits) #Register - Su lectura devuelve el valor del Contador en el momento
	- `CALIB` __Calibration__ (23 bits) #Register 
	  está inicializado por el código de Boot con un valor de fábrica para generar una interrupción cada 10 milisegundos con un clock de 100 MHz 

## Control del Módulo TIMER

- ### Puntero a la base de la estructura `LPC_TIM0` : 
   `LPC_TIM0->` Timer 0 
   (`LPC_TIM0 - LPC_TIM3`) Hay 4 Timers, cada uno contiene los siguientes registros: 
---

- `CTCR` __Count Control Register__ 
  selects between Timer and Counter mode, and in Counter mode selects the signal and edge(s) for counting.
	- bit-1:0		- Counter/Timer mode
	- bit-3:2		- Count Input Select 
	  >Cual pin CAP-TURE es muestreado como reloj 

- `PR` __Prescale Register__ 
  Maximum value for the _Prescale Counter_ (`PC`) 

- `TCR` __Timer Control Register__ 
  Contiene los bits Counter Enable y Counter Reset

- `IR` __Interrupt Register__ 
  Flags de las interrupciones Match y Capture. - Escribir `1` en sus bits baja la bandera

---

- `MR0` __Match Register 0__ (`MR0 - MR3`)
 >  - Cada Timer tiene 4 registros Match. 
  > - El March Register es el valor comparado constantemente con el valor en __Timer counter__ (`TC`) 
  > - Cuando ambos sean iguales se dispara una acción 
  > - las acciones son controladas con el __Match Control Register__ (`MCR`)

---

- `MCR` __Match Control Register__ 
  Controla que tipo de operaciones se realizan cuando matchean los registros __Match Register m__ `MRm` (`MR0 - MR3`) con el __Timer counter__ `TC`

	- *bit-MRmI* 
	  Interrupt on match-3:0 - Generar interrupción cuando `MRm` matches `TC`

	- *bit-MRmR* 
	  Reset on match-3:0 - Resetear `TC` si `MRm` lo matchea
	
	- *bit-MRmS*
	  Stop on match-3:0 - `TC` y `PC` se detendrán y en __Timer Control Register__ `TCR` se escribe `0` en el bit-Counter Enable si `MRm` matchea con `TC`

---



- `EMR` __External Match Register__ provides control and status of the external match pins

	- *bit-3:0 - EMm*
	  > EMm - External Match match-3:0 - Este bit puede escribirse en el pin con la función MATn.m (n=timer-3:0 y m=match-3:0) seleccionada en `PINSEL` - Realiza la funcionalidad seleccionada con los dos bits EMCm
	
	- *bit-11:4 - EMCm*

		>External Match Control match-3:0 - Determina la funcionalidad (una de cuatro) del bit External Match m (EMm), controlando qué acción realiza el bit cuando sucede un match entre `TC` y `MRm`
		>- `00` => No hacer nada
		>- `01` => Limpia a `0` el bit/output-EMm correspondiente 
		>- `10` => Setea a `1` el bit/output-EMm correspondiente
		>- `11` => Togglea el bit/output-EMm correspondiente


---

## Control del Módulo ADC

- ### Puntero a base de la estructura __System Control__
	- `LPC_SC ->` __System Control__

- `PCONP` __Power Control for Peripherals__
	- *bit-12 - PCADC* 
	   A/D power/clock control 

- `PCLKSEL0` __Peripheral Clock Selection__ 
	- *bit-25:24 - PCLK_ADC*
	  Peripheral Clock for ADC

---

- ### Puntero a base de la estructura __Analog to Digital Converter__
	- `LPC_ADC->` __Analog to Digital Converter__

- `ADCR` __A/D Control Register__
	- *bit-7:0 - SEL*
	  Selección de los 8 canales del ADC - pines que van a ser muestreados y convertidos
	- *bit-15:8 - CLKDIV*
	  Divisor del Clock para periférico ADC (PCLK_ADC) 
	- *bit-16 - BURST*
	  Modo BURST-ráfaga o Modo software controlled
	- *bit-21 - PDN*
	  power-down mode - Activar ADC
	- *bit-27 - EDGE*
	  Flanco del evento que dispara la conversión del ADC
	- *bit-26:24 - START*
	  Evento que dispara la conversión del ADC

- `ADINTEN` __A/D Intterrupt Enable__ 
  Generar un pedido de interrupción luego de completada una conversión
	- *bit-7:0 - ADINTEN-7:0*
	  A/D Interrupt Enable - Habilitar que completar una conversión en el canal-7:0 del ADC pueda generar una interrupción
	- *bit-8 - ADGINTEN*
	  A/D Global Interrupt Enable - Solo la flag global DONE en ADDR-7:0 _ A/D Data Registers _ está habilitada a generar una interrupción

- `ADDR7:0` __A/D Data Register-7:0__ 
  `ADDR7 - ADDR0`  -> channel-7:0
	- *bit-15:4 - RESULT*
	  Representación de 12-bits del voltaje en el pin AD-7:0, Como la fracción entre los voltajes de referencia positivo y negativo
	- *bit-31 - DONE* 
	  This bit is set to 1 when an A/D conversion completes. It is cleared when this register is read

> La habilitación de la interrupción también debe hacerse por NVIC_EnableIRQ(ADC_IDQn);

- Configuración de pines para ADC
	- `LPC_PINCON->PINSELn` 
	  Cambiar función de pin a ADn con `PINSEL`
	- `LPC_PINCON->PINMODEn` Cambiar modo de pin a "Flotante" o "Tristate" sin resistencia de pull-Up o pull-Down => `10` en `PINMODE`


# Configuración de Puertos a Nivel de Hardware

```c
// puntero a estructura
LPC_PINCON ->
```
```c
// miembros que usamos
PINSEL0		// Puerto 0 l
PINSEL1 	// Puerto 0 h
PINSEL2 	// Puerto 1 l
PINSEL3 	// Puerto 1 h
PINSEL4 	// Puerto 2 l
PINSEL7 	// Puerto 3 h
PINSEL9 	// Puerto 4 h

PINMODE0	// Puerto 0 l
PINMODE1	// Puerto 0 h
PINMODE2	// Puerto 1 l
PINMODE3	// Puerto 1 h
PINMODE4	// Puerto 2 l
PINMODE7	// Puerto 3 h
PINMODE9	// Puerto 4 h

PINMODE_OD0		// Puerto 0
PINMODE_OD1		// Puerto 1
PINMODE_OD2		// Puerto 2
PINMODE_OD3		// Puerto 3
PINMODE_OD4		// Puerto 4
```

## PINSEL (Pin Function Select register)

: 2 bits para cada pin; Cada pin tiene hasta 4 funciones seleccionables, revisar manual para ver cada funcion
Cada registro configura hasta 16 pines (mitad baja o alta)

```c
// Registros
PINSEL0		// Puerto 0 l
PINSEL1 	// Puerto 0 h
// bits value
00	// Primera funcion - default
01	// primera funcion alternativa
10	// segunda funcion alternativa
11	// tercera funcion alternativa
```

## PINMODE (Pin Mode Select register)

: Selecciona el modo de entrada de los pines.
2 bits para cada pin; Revisar manual para saber los pines que controla cada registro - y qué bits están reservados.

```c
// Registros
PINMODE0	// Puerto 0 l
PINMODE1	// Puerto 0 h
// bits value
00	// pull-up resistor enabled
01	// repeater mode enabled
10	// pull-up and pull-down disabled
11	// pull-down resistor enabled
```

## PINMODE_OD (Open Drain Pin Mode Select register)

: Cada bit de estos registros controla el modo de operación OD de un pin de un puerto; Algunos pines están reservados, revisar manual.

```c
// Registros
PINMODE_OD0		// Puerto 0
// bit value
0	// Normal mode - not open drain
1	// Open drain mode
```

# Configuración de Puertos a Nivel de Software

```c
// 5 punteros, corresponden al Puerto 0 - Puerto 4
// Apuntan a 5 direcciones. En cada dirección se ubica una estructura con el mismo tipo de miembros.
LPC_GPIO0 ->
LPC_GPIO1 ->
LPC_GPIO2 ->
LPC_GPIO3 ->
LPC_GPIO4 ->
```
```c
// miembros
FIODIR		// (Fast GPIO Port Direction control register)
FIOMASK		// (Fast Mask register for port)
FIOPIN		// (Fast GPIO port Pin value register)
FIOSET		// (Fast GPIO port output Set register)
FIOCLR 		// (Fast GPIO port output Clear register)
```

>Estos registros-miembros de estructura se pueden acceder por sus campos de 32bits (word), 16bits (Half word), y 8bits (byte) 
>```c
>	FIODIR // 31-0
>		FIODIRL // 15-0
>		FIODIRH // 31-16
>			FIODIR0 // 7-0
>			FIODIR1 // 15-8
>			FIODIR2 // 23-16
>			FIODIR3 // 31-24
>```

## Registros FIO

>Cada pin se controla con 1 bit, de cada uno de estos registros.

FIODIR
: El registro `FIODIR` (Fast GPIO Port Direction control register)
controla la dirección de los pines de un puerto. 
```c 
0	// pin is input
1	// pin is output
``` 

FIOMASK
: El registro `FIOMASK` (Fast Mask register for port) permite enmascarar los pines de un puerto. Las funciones de los registros `FIOPIN`, `FIOSET`, `FIOCLR`, solo alteraran al pin del puerto cuando el registro `FIOMASK` tiene un valor de cero para ése pin. En el caso contrario, las lectura del pin devolverá cero sin importar su estado; Y la escritura no afectará el estado del pin.
```c
0	// pin is not masked
1	// pin is masked
``` 

FIOPIN
: El registro `FIOPIN` (Fast GPIO port Pin value register) permite a traves de sus bits obtener el estado del pin en el caso que el pin se encuentre como entrada; Y define el estado del pin si se encuentra configurado como salida.
```c
// pin configurado como entrada
0	// se encuentra en estado bajo
1	// se encuentra en estado alto
// pin configurado como salida
0	// se escribe un 0
1	// se escribe un 1
```

FIOSET
: El registro `FIOSET` (Fast GPIO port output Set register) permite a traves de sus bits, establecer el estado alto `1` de los pines del puerto
```c
// Si el pin tiene 0 en el registro FIOMASK y está configurado como salida:
0	// pin output is unchanged
1	// pin output is set to HIGH
```

FIOCLR
: El registro `FIOCLR` (Fast GPIO port output Clear register) permite a traves de sus bits, establecer el estado bajo `0` de los pines del puerto
```c
// Si el pin tiene 0 en el registro FIOMASK y está configurado como salida:
0	// pin output is unchanged
1	// pin output is set to LOW
```

## Configuración de Interrupciones por GPIO

Registro IO0IntEnR (GPIO Interrupt Enable for port 0 Rising Edge)
Registro IO2IntEnR (GPIO Interrupt Enable for port 2 Rising Edge)
Registro IO0IntEnF (GPIO Interrupt Enable for port 0 Falling Edge)
Registro IO2IntEnF (GPIO Interrupt Enable for port 2 Falling Edge)
Registro IO0IntStatR (GPIO Interrupt Status for port 0 Rising Edge Interrupt)
Registro IO2IntStatR (GPIO Interrupt Status for port 2 Rising Edge Interrupt)
Registro IO0IntStatF (GPIO Interrupt Status for port 0 Falling Edge Interrupt)
Registro IO2IntStatF (GPIO Interrupt Status for port 2 Falling Edge Interrupt)
Registro IO0IntClr (GPIO Interrupt Clear register for port 0)
Registro IO2IntClr (GPIO Interrupt Clear register for port 2)
Registro IOIntStatus (GPIO overall Interrupt Status register)
Registro EXTINT (External Interrupt Flag register)
Registro EXTMODE (External Interrupt Mode register)
Registro EXTPOLAR (External Interrupt Polarity register)


- External Interrupt

	- `EXTINT` Flag register

		- [3,0] bits [EINT3,EINT0] se ponen en `1` si 
			- se selecciono la funcion `EINTX` en el pin 
				- y en level-sensitive mode - el pin está en su estado activo seleccionado
					- activo por `ALTO` o por `BAJO`
				- o en edge-sensitive mode - si el flanco seleccionado sucedió en el pin

		- Se limpia la flag por bit escribiendoles un `1`

	- `EXTMODE` Mode register
		- [3,0] bits
			- `0` Level-sensibility is selected for `EINTX`
			- `1` `EINTX` is edge sensitive

	- `EXTPOLAR` Polarity register
		- [3,0] bits
			- `0` low-active - or - falling-edge sensitive
			- `1` high-active - or - rising-edge sensitive

# NVIC functions
```c
NVIC_SetPriorityGrouping(uint32_t PriorityGroup)

NVIC_GetPriorityGrouping(void)

NVIC_EnableIRQ(IRQn_Type IRQn)

NVIC_DisableIRQ(IRQn_Type IRQn)

NVIC_GetPendingIRQ(IRQn_Type IRQn)

NVIC_SetPendingIRQ(IRQn_Type IRQn)

NVIC_ClearPendingIRQ(IRQn_Type IRQn)

NVIC_GetActive(IRQn_Type IRQn)

NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)

NVIC_GetPriority(IRQn_Type IRQn)

NVIC_SystemReset(void)

```




---

# Librerías

system_LPC17xx.c
* core_cm3.h

# Repositorios
- <https://github.com/dariocastillo11/digital-3>
- Tiene ejemplos con CMSIS
- Parciales con Drivers
	- Blinking_LED
	- Button_one_digit_counter
	- C-Seminars-master
	- Display_autocounter
	- MULTIPLEXADO
	- PARCIALES - Driver
	- multiplexadoconsystick
	- prederle_conentrada
	- systickPARPADEOCADA5SEGUNDOS
	- systick_para_servomotor

- <https://github.com/Mati-Costamagna/Electronica-Digital-III>
- 
	- Ejercicios de Clases - justo los ejercicios de Migliore ⭐
	- Practica Primer Parcial ⭐

- <https://github.com/nicopinera/EDIII>
- Ejemplos de varios profes
- Ejemplos con CMSIS y Drivers
- Parciales
	- 01_Ejercicios_David con CMSIS ⭐
		- Ejercicios de parcial

- <https://github.com/fabiobritez/digital_electronicsIII>
- Ejemplos con Drivers

```c
```

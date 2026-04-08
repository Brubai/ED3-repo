# Clases
#### Semana 1
4-3-sem1 T1:
- ARM-Cortex M3
- Capacidades y clasificación
- Bloques lógicos principales

5-3-sem1 P1:
- Estructuras y otros tipos en lenguaje C 
- Punteros
- campos de bits
- scope
- casteo

#### Semana 2
- 11-3-sem2 T2
	- Pipeline
	- Clock
	- Bloque PLL
	- Características del Core
	- Aplicación de los registros en C

- 12-3-sem2 P2
	- Arquitectura de N-capas
	- Mapa de memoria
	- Módulo GPIO: puertos - registros
	- ejercicio de GPIO

#### Semana 3
- 19-3-sem3 P3
	- Módulo SCS - NVIC
	- NVIC - registros
	- Interrupciones externas
	- Funciones CMSIS para control de NVIC
	- Bases sobre estructuras de código - Branching

- Clase Grabada Teórica 
	- Módulo Systick
	- Funciones Systick y CMSIS
	- Funciones Handler para Interrupciones

#### Semana 4
- 25-3-sem4 T3
	- Interrupciones y excepciones
	- Funcionalidades del NVIC
	- Bloque NVIC en el core
	- Mapeo de memoria de los interrupt vectors

- 26-3-sem4 P4
	- Módulo Systick
	- Ejercicio de interrupción por Systick y externa
	- PWM (Pulse Width Modulation)

#### Semana 5
- 1-4-sem5 T4
	- Periférico ADC características
	- Registros para usar periféricos
	- Registros del ADC
	- Uso de registros en ejercicio
	- Máquina de estados - tp2

#### Semana 6

#### Semana 7

---

#### Bloques lógicos
Core
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
- 

Otras definiciones
- CMSIS - (Cortex Microcontroller Software Interface Standard)
- NMI - (Non-Maskable Interrupt)
- IRQ - (Interrupt Request)
- EXTI - (External Interrupt)
- PWM - (Pulse Width Modulation)

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
void cfgGPIO(void){/*...*/}
void cfgIntExt(void){/*...*/}
void cfgSysTick(void){/*...*/}
void EINT0_IRQHandler(void){/*...*/}
void SysTick_IRQHandler(void){/*...*/}
```

---

# Registros

>Se listan los nombres de los miembros de las estructuras, podemos acceder a ellos con el operador `->` sobre el puntero de la estructura
>Y arriba de cada lista, los nombres con que se definieron el puntero a la propia estructura

>fuente:	file     LPC17xx.h (revisar carpeta inc del proyecto)

Estos son parte de los registros usados para controlar los pines
```c
// configuración a nivel de hardware
LPC_PINCON ->	// (Puntero de estructura para configuración de pines)
PINSEL0				// Selección función de pin del Puerto 0 mitad baja
PINMODE0			// Configuración del modo de entrada de pin del Puerto 0 mitad baja
PINMODE_OD0			// Configuración del modo Open drain del Puerto 0

// configuracion a nivel de software
LPC_GPIO0 ->	// (Puntero de estructura para el Puerto 0)
FIODIR		// (Fast GPIO Port Direction control register)
FIOMASK		// (Fast Mask register for port)
FIOPIN		// (Fast GPIO port Pin value register)
FIOSET		// (Fast GPIO port output Set register)
FIOCLR 		// (Fast GPIO port output Clear register)
```


#### Configuración de Puertos a Nivel de Hardware

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

PINSEL (Pin Function Select register)

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

PINMODE (Pin Mode Select register)

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

PINMODE_OD (Open Drain Pin Mode Select register)

: Cada bit de estos registros controla el modo de operación OD de un pin de un puerto; Algunos pines están reservados, revisar manual.

```c
// Registros
PINMODE_OD0		// Puerto 0
// bit value
0	// Normal mode - not open drain
1	// Open drain mode
```

#### Configuración de Puertos a Nivel de Software

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

##### Registros FIO

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

---

# Librerías

system_LPC17xx.c

```c
```
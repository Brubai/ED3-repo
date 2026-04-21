- [[#Registros|Registros]]
	- [[#Registros#Control de pines|Control de pines]]
		- [[#Control de pines#Configuración a nivel de hardware|Configuración a nivel de hardware]]
			- [[#Configuración a nivel de hardware#Registros por Puerto:|Registros por Puerto:]]
		- [[#Control de pines#Configuracion a nivel de software|Configuracion a nivel de software]]
			- [[#Configuracion a nivel de software#Registros FIO|Registros FIO]]
	- [[#Registros#Control de Interrupciones por GPIO|Control de Interrupciones por GPIO]]
		- [[#Control de Interrupciones por GPIO#Registros GPIO Interrupt|Registros GPIO Interrupt]]
		- [[#Control de Interrupciones por GPIO#Registros External Interrupt|Registros External Interrupt]]
	- [[#Registros#Control del Módulo Systick|Control del Módulo Systick]]
		- [[#Control del Módulo Systick#Registros SysTick|Registros SysTick]]
	- [[#Registros#Control del Módulo TIMER|Control del Módulo TIMER]]
		- [[#Control del Módulo TIMER#Registros de Timer|Registros de Timer]]
	- [[#Registros#Control del Módulo ADC|Control del Módulo ADC]]
		- [[#Control del Módulo ADC#Registros __System Control__|Registros __System Control__]]
		- [[#Control del Módulo ADC#Registros ADC|Registros ADC]]



# Registros 

---

>Se listan los nombres de los miembros de las estructuras, podemos acceder a ellos con el operador `->` sobre el puntero de la estructura
>Y arriba de cada lista, los nombres con que se definieron el puntero a la propia estructura

>fuente:	librería:	CMSISv2p00_LPC17xx

>Por Favor ver antes los registros en el MANUAL DE USUARIO, este es solo un resúmen esquemático

![[Pasted image 20260421022811.png]]







## Control de pines  

---

> [!warning] Revisar manual de Usuario para ver mapeo de pines en los registros  
>  Revisar manual de Usuario para ver todos los registros 
> - PINSEL0:PINSEL9 (5 puertos mitad alta y mitad baja)* => Cada pin se controla con 2 bits
> - PINMODE0:PINMODE9 (5 puertos mitad alta y mitad baja)* => Cada pin se controla con 2 bits
> - PINMODE_OD0 (5 puertos) => Cada pin se controla con 1 bit
> - LPC_GPIO0 - LPC_GPIO4 (5 puertos) => Cada pin se controla con 1 bit para todos los Registros de la Estructura  
> - \* no todos los registros son completamente accesibles, habrá registros, pines y bits reservados

### Configuración a nivel de hardware 

---

Puntero de estructura para configuración de pines:  
`LPC_PINCON ->` — __Pin Connect__ 



#### Registros por Puerto: 

---

 `PINSEL0` __Pin Select-0__  
  Puerto 0 mitad baja - Selección de función de cada pin -> 2 bits por pin (`PINSEL9` : `PINSEL0`) -dos registros por puerto (Mitad Alta y Baja)   
  
 `PINMODE0` __Pin Mode-0__  
  Puerto 0 mitad baja - Modo de entrada de cada pin -> 2 bits por pin (`PINMODE9` : `PINMODE0`) -> dos registros por puerto (Mitad Alta y Baja)   
  
 `PINMODE_OD0` __Pin Mode-OpenDrain-0__  
  Puerto 0 - Modo Open drain de cada pin (`PINMODE_OD4` : `PINMODE_OD0`) -> un registro por puerto 

### Configuracion a nivel de software

---

Puntero de estructura por Puerto  
`LPC_GPIO0 ->` — __General Purpose Input/Output Port-0__  
(`LPC_GPIO4 : LPC_GPIO0`) Para cada puerto, están los siguientes registros: 


#### Registros FIO

---

`FIODIR` __Fast GPIO Port Direction control register__ 

`FIOMASK` __Fast Mask register for port__ 

`FIOPIN` __Fast GPIO port Pin value register__ 

`FIOSET` __Fast GPIO port output Set register__ 

`FIOCLR` __Fast GPIO port output Clear register__ 


![[Pasted image 20260421022937.png]]

## Control de Interrupciones por GPIO

---

Puntero base de estructura:  
`LPC_GPIOINT ->` — __General Purpose Input/Output Interrution__ 


### Registros GPIO Interrupt

---

__Enable Register for GPIO Interrupt__ - for port 0 and 2 - for Rising and Falling edge  
`IO0IntEnR`  
`IO2IntEnR`   
`IO0IntEnF`  
`IO2IntEnF`   

__Status Register for GPIO Interrupt__ - for port 0 and 2 - for Rising and Falling edge  
`IO0IntStatR`  
`IO2IntStatR`  
`IO0IntStatF`  
`IO2IntStatF`   

__Clear Register for GPIO Interrupt__ - for port 0 and 2  
`IO0IntClr`  
`IO2IntClr`   

__Overall Status Register for GPIO Interrupt__  
`IOIntStatus`   


### Registros External Interrupt

---
Puntero base de estructura:  
`LPC_SC ->` — __General Purpose Input/Output Interrution__ 

__External Interrupt__  
`EXTINT` __Flag register__  
`EXTMODE` __Mode register__  
`EXTPOLAR` __Polarity register__ 

![[Pasted image 20260421023039.png]]


## Control del Módulo Systick

---

### Registros SysTick
---
Puntero a base de estructura  
`Systick ->` — **System Timer**  
System Timer Registers   

`CTRL` __Control and Status__    

- *bit-0*  
  ENABLE — Habilitar el contador  
  
+ *bit-1*  
  TICKINT — Habilitar el interrupt del contador  
  
- *bit-2*  
  CLKSOURCE — Selección de la fuente del clock   
  
+ *bit-16*  
  COUNTFLAG — Bandera del contador cuando llega a `0`   
  Se limpia autom. a  `0` cuando se lee el registro   

---

`LOAD` __Reload Value__ (23 bits)  
El valor que será cargado en el Timer cuando llega a `0`    

`VAL` __Current Value__ (23 bits)  
Su lectura devuelve el valor del Contador en el momento   

`CALIB` __Calibration__ (23 bits)   
está inicializado por el código de Boot con un valor de fábrica para generar una interrupción cada 10 milisegundos con un clock de 100 MHz     

![[Pasted image 20260421023137.png]]

## Control del Módulo TIMER

---

### Registros de Timer

---

Puntero a la base de la estructura :  
`LPC_TIM0->` — **Timer 0**   
(`LPC_TIM0 - LPC_TIM3`) Hay 4 Timers, cada uno contiene los siguientes registros:  

`CTCR` __Count Control Register__  
selects between Timer and Counter mode, and in Counter mode selects the signal and edge(s) for counting.   

- *bit-1:0* — Counter/Timer mode  

+ *bit-3:2* — Count Input Select   
  Selecciona qué pin CAP-TURE es muestreado como reloj 

`PR` __Prescale Register__  
  Maximum value for the _Prescale Counter_ (`PC`)  

`TCR` __Timer Control Register__  
  Contiene los bits Counter Enable y Counter Reset 

`IR` __Interrupt Register__  
  Flags de las interrupciones Match y Capture. - Escribir `1` en sus bits baja la bandera 

---

`MR0` __Match Register 0__ (`MR0 - MR3`)   

Cada Timer tiene 4 registros Match.  
El Match Register es el valor comparado constantemente con el valor en Timer counter (TC).  
Cuando ambos sean iguales se dispara una acción.  
las acciones son controladas con el __Match Control Register__ (`MCR`).  

---

 `MCR` __Match Control Register__   

Controla que tipo de operaciones se realizan cuando matchean los registros __Match Register m__ `MRm` (`MR0 - MR3`) con el __Timer counter__ `TC`

- *bit-MRmI*  
Interrupt on match-3:0 — Generar interrupción cuando `MRm` matches `TC`  
+ *bit-MRmR* 
Reset on match-3:0 — Resetear `TC` si `MRm` lo matchea
- *bit-MRmS*
Stop on match-3:0 — `TC` y `PC` se detendrán y en __Timer Control Register__ `TCR` se escribe `0` en el bit-Counter Enable si `MRm` matchea con `TC`

---



`EMR` __External Match Register__ provides control and status of the external match pins 

- *bit-3:0 - EMm*  
  EMm - External Match match-3:0 — Este bit puede escribirse en el pin con la función MATn.m (n=timer-3:0 y m=match-3:0) seleccionada en `PINSEL`  
  
  Realiza la funcionalidad seleccionada con los dos bits EMCm

+ *bit-11:4 - EMCm*  
  External Match Control match-3:0 — Determina la funcionalidad (una de cuatro) del bit External Match m (EMm), controlando qué acción realiza el bit cuando sucede un match entre `TC` y `MRm`
	- `00` => No hacer nada
	- `01` => Limpia a `0` el bit/output-EMm correspondiente 
	- `10` => Setea a `1` el bit/output-EMm correspondiente
	- `11` => Togglea el bit/output-EMm correspondiente

![[Pasted image 20260421023206.png]]

## Control del Módulo ADC

---

### Registros __System Control__

---

Puntero a base de la estructura  
`LPC_SC ->` — __System Control__   

`PCONP` __Power Control for Peripherals__   

- *bit-12 - PCADC*  
  A/D power/clock control 

`PCLKSEL0` __Peripheral Clock Selection__   
- *bit-25:24 - PCLK_ADC*  
  Peripheral Clock for ADC


### Registros ADC

---

Puntero a base de la estructura  
`LPC_ADC->` — __Analog to Digital Converter__ 

`ADCR` __A/D Control Register__   
- *bit-7:0 — SEL*  
  Selección de los 8 canales del ADC - pines que van a ser muestreados y convertidos <br><br>
- *bit-15:8 — CLKDIV*  
  Divisor del Clock para periférico ADC (PCLK_ADC) <br><br>
- *bit-16 — BURST*  
  Modo BURST-ráfaga o Modo software controlled <br><br>
- *bit-21 — PDN*  
  power-down mode - Activar ADC <br><br>
- *bit-27 — EDGE*  
  Flanco del evento que dispara la conversión del ADC<br><br>
- *bit-26:24 — START*  
  Evento que dispara la conversión del ADC <br><br>


`ADINTEN` __A/D Intterrupt Enable__  
  Generar un pedido de interrupción luego de completada una conversión <br><br> 
- *bit-7:0 - ADINTEN-7:0*  
  A/D Interrupt Enable - Habilitar que completar una conversión en el canal-7:0 del ADC pueda generar una interrupción <br><br>
  
- *bit-8 - ADGINTEN*
  A/D Global Interrupt Enable - Solo la flag global DONE en ADDR-7:0 _ A/D Data Registers _ está habilitada a generar una interrupción <br><br>

`ADDR7:0` __A/D Data Register-7:0__  
`ADDR7 - ADDR0`  -> channel-7:0 

- *bit-15:4 - RESULT*  
  Representación de 12-bits del voltaje en el pin AD-7:0, Como la fracción entre los voltajes de referencia positivo y negativo <br><br>
- *bit-31 - DONE*  
  This bit is set to 1 when an A/D conversion completes. It is cleared when this register is read

> [!warning] La habilitación de la interrupción también debe hacerse por NVIC_EnableIRQ(ADC_IDQn);

- Configuración de pines para ADC
	- `LPC_PINCON->PINSELn` 
	  Cambiar función de pin a ADn con `PINSEL`
	- `LPC_PINCON->PINMODEn` Cambiar modo de pin a "Flotante" o "Tristate" sin resistencia de pull-Up o pull-Down => `10` en `PINMODE`

---

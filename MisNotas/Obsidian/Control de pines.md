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

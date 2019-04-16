#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#ifdef __cplusplus
extern "C"
#endif
void MCU_init(void); /* Device initialization function declaration */

void delay(unsigned short n){//Funcion que recibe por parámetro la cantidad de miliseg de delay
  unsigned short temp;
  unsigned short cant;
  /*Aca sabemos que 1a ejecucion del for equivale a 23 ciclos de reloj
  y que hacemos 8000 ciclos por milisegundo, eso equivale a mas o menos
  348 ejecuciones del for por milisegundo*/
  for(cant=n; cant>0; cant--){
	for(temp=348; temp>0; temp--);
  }
}

void main(void) {
  PTBDD = 0xFF;
  PTBD = 0x01;
	
  MCU_init();	/* call Device Initialization */
  /* include your code here */
  
  PTCDD_PTCDD0 = 0;//Posicion de la memoria en la que guardo el valor de entrada
  PTCPE_PTCPE0 = 1;//Seteo la entrada PTCD0 con una resistencia pull up interna

  for(;;) {
	delay(10);//Delay para el polling del boton (No seria necesario en este caso por el delay de los led)
	if(PTBD == 0x00){
	  PTBD = 0x01;
	  delay(500);//Un delay para cuando el led esta en 1
	}
	//Aca se lee a la entrada para el pulsador
	if(PTCD_PTCD0 == 0){
	  PTBD = PTBD<<1;
	  if(PTBD != 0){//Para que no tenga un delay de un segundo con los led apagados
	    delay(500);
	  }
	}
    /* __RESET_WATCHDOG(); By default COP is disabled with device init. When enabling, also reset the watchdog. */
  } /* loop forever */
  /* please make sure that you never leave main */
}

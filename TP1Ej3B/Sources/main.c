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
  PTBD = 0x03;
  
  MCU_init();	/* call Device Initialization */
  /* include your code here */

  

  for(;;) {
    if(PTBD == 0){
    	PTBD = 0x03;
    }
	delay(200);
    
    PTBD=PTBD*4;
	  /* __RESET_WATCHDOG(); By default COP is disabled with device init. When enabling, also reset the watchdog. */
  } /* loop forever */
  /* please make sure that you never leave main */
}

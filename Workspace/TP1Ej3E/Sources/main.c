#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#ifdef __cplusplus
extern "C"
#endif

#define tiempo_leds 150 //El tiempo que queda prendido cada led en milisegundos

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
  unsigned char estado = 0;
  
  PTBDD = 0xFF;
  PTBD = 0x01;
	
  MCU_init();	/* call Device Initialization */
  /* include your code here */
  
  PTCDD_PTCDD0 = 0;//Posicion de la memoria en la que guardo el valor de entrada
  PTCPE_PTCPE0 = 1;//Seteo la entrada PTCD0 con una resistencia pull up interna

  for(;;) {
	//Aca se lee a la entrada para el pulsador
	if(PTCD_PTCD0 == 0){
		delay(20);
		while(PTCD_PTCD0 == 0);
		delay(20);
		estado = ~estado;
	}
	if(estado){
	  if(PTBD == 0x00){
	    PTBD = 0x01;
	    delay(tiempo_leds);//Un delay para cuando el led esta en 1
	  }
	  PTBD = PTBD<<1;
	  if(PTBD != 0){//Para que no tenga un delay de un segundo con los led apagados
	    delay(tiempo_leds);
	  }
	}
	else{
	  if(PTBD == 0x00){
	    PTBD = 0x0080;
	    delay(tiempo_leds);//Un delay para cuando el led esta en 1
      }
	  PTBD = PTBD>>1;
	  if(PTBD != 0){//Para que no tenga un delay de un segundo con los led apagados
	    delay(tiempo_leds);
	  }
	}
    /* __RESET_WATCHDOG(); By default COP is disabled with device init. When enabling, also reset the watchdog. */
  } /* loop forever */
  /* please make sure that you never leave main */
}

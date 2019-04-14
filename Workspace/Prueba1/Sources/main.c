#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#ifdef __cplusplus
extern "C"
#endif
void MCU_init(void); /* Device initialization function declaration */


void main(void) {
  unsigned short temp;
	
  MCU_init();	/* call Device Initialization */
  /* include your code here */

  PTBDD = 0xFF; //Registro de direcciones del puerto B
  PTBD = 0x55; //Registro de 8 bits de datos del puerto B

  for(;;) { //Tener en cuenta que el clock del micro es de 8 MHz, y hace 360694
	  //ciclos para hacer el for y la negacion, si se hace la cuenta, da que los led
	  //estan 45 mseg prendidos antes de cambiar al otro
	  for(temp=0x3FFF; temp>0; temp--);
	  PTBD = ~PTBD;
    /* __RESET_WATCHDOG(); By default COP is disabled with device init. When enabling, also reset the watchdog. */
  } /* loop forever */
  /* please make sure that you never leave main */
}

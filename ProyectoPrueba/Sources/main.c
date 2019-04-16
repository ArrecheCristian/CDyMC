
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
  /*Pongo el puerto 5 como salida*/
  PTBDD=0xFF;
  PTBD=0x55;
  
  
  for(;;) {
	  for(temp=255;temp>0;temp--);
	  PTBD=~PTBD;
	  /* __RESET_WATCHDOG(); By default COP is disabled with device init. When enabling, also reset the watchdog. */
  } /* loop forever */
  /* please make sure that you never leave main */
}

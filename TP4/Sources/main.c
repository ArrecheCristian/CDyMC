#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#ifdef __cplusplus
extern "C"
#endif
void MCU_init(void); /* Device initialization function declaration */


void main(void) {
  MCU_init();	/* call Device Initialization */
  /* include your code here */

  for(;;) {
	  if(ADCSC1_COCO == 1){
		  if(ADCR==0x00){//Se hace un if para que el led se apague completamente
			  TPM1C1VH = 0x01;
		  }
		  else{
			  TPM1C1VH = 0x00;
		  }
		  TPM1C1V = 0xFF - ADCR;
	  }
  }
    /* __RESET_WATCHDOG(); By default COP is disabled with device init. When enabling, also reset the watchdog. */
} /* loop forever */
  /* please make sure that you never leave main */

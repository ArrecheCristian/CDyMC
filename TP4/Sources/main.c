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
	 TPM1MODL = 0x08;
	 TPM1C1VL = 0x05;
    /* __RESET_WATCHDOG(); By default COP is disabled with device init. When enabling, also reset the watchdog. */
  } /* loop forever */
  /* please make sure that you never leave main */
}

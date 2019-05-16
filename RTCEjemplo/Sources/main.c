#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#ifdef __cplusplus
extern "C"
#endif

extern volatile unsigned char RTC_flag;//Extern porque se inicializa en el init, volatile por ser global

void MCU_init(void); /* Device initialization function declaration */



void main(void) {
  MCU_init();	/* call Device Initialization */
  /* include your code here */

  
PTBDD=0xFF;
PTBD=0x55;
  for(;;) {
	  if(RTC_flag==1){
		  PTBD=~PTBD; //Accion cada 100ms
		  RTC_flag=0;
		  //itoa(seg);//Para traerme los ASCII de los segundos, asi lo imprimo en la pantalla
		  //seg va de 0 a 59
		  //dig1 = seg/10;
		  //dig2 = seg%10;
		  //ascii = dig1+'0';
	  }
    /* __RESET_WATCHDOG(); By default COP is disabled with device init. When enabling, also reset the watchdog. */
  } /* loop forever */
  /* please make sure that you never leave main */
}

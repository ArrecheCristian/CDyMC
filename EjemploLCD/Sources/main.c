#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "lcd.h"



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
  MCU_init();	/* call Device Initialization */
  /* include your code here */
  LCD_init(_2_LINES|DISPLAY_8X5,DISPLAY_ON|CURSOR_OFF);
  
  
  for(;;) {
	  LCD_pos_xy(0,0);
	  LCD_write_string("      HOLA   ");
	  LCD_pos_xy(0,1);
	  LCD_write_string("     TODOSS");
	  delay(400);
	  LCD_pos_xy(0,0);
	  LCD_write_string("             ");
	  LCD_pos_xy(0,1);
	  LCD_write_string("           ");
	  delay(400);
    /* __RESET_WATCHDOG(); By default COP is disabled with device init. When enabling, also reset the watchdog. */
  } /* loop forever */
  /* please make sure that you never leave main */
}

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "stdio.h"
#include "lcd.h"


#ifdef __cplusplus
extern "C"
#endif

extern volatile unsigned char RTC_flag;//Extern porque se inicializa en el init, volatile por ser global

void MCU_init(void); /* Device initialization function declaration */


int cont=0;
void main(void) {
  unsigned char dig1=0;
  unsigned char dig2=0;
  unsigned char dig3=0;
  unsigned char dig4=0;
  unsigned char dig5=0;
  unsigned char dig6=0;
  unsigned char seg=0;
  unsigned char min=0;
  unsigned char hora=0;
  MCU_init();	/* call Device Initialization */
  /* include your code here */
  LCD_init(_2_LINES|DISPLAY_8X5,DISPLAY_ON|CURSOR_ON);
  
  LCD_pos_xy(0,0);
  LCD_write_char(dig1);
  LCD_write_char(dig2);
  LCD_write_char(':');
  LCD_write_char(dig3);
  LCD_write_char(dig4);
  LCD_write_char(':');
  LCD_write_char(dig5);
  LCD_write_char(dig6);
  
  for(;;) {
	  if(RTC_flag == 1){
		  cont++;
		  if(cont == 9){
	        seg++;
	        dig5=(seg/10)+'0';
	        dig6=(seg%10)+'0';
	        cont=0;
	        LCD_pos_xy(6,0);
	        LCD_write_char(dig5);
	        LCD_write_char(dig6);
	        if(seg==60){
	        	min++;
	        	seg=0;
	        	dig3=(min/10)+'0';
	        	dig4=(min%10)+'0';
	        	LCD_pos_xy(3,0);
	            LCD_write_char(dig3);
	            LCD_write_char(dig4);
	        	if(min==60){
	        		min=0;
	        		hora++;
	        		dig1=(hora/10)+'0';
	        	    dig2=(hora%10)+'0';
	        	    LCD_pos_xy(0,0);
	        	    LCD_write_char(dig1);
	        	    LCD_write_char(dig2);
	        		if(hora==24){
	        			hora=0;
	        		}  
	        	}
	        }
		  }
	  }//Termina el chequeo de la hora
	  
	  
    /* __RESET_WATCHDOG(); By default COP is disabled with device init. When enabling, also reset the watchdog. */
  } /* loop forever */
  /* please make sure that you never leave main */
}

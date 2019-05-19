#include "lcd.h"

//Declaración de variables
unsigned char dig1='1';
unsigned char dig2='6';
unsigned char dig3='5';
unsigned char dig4='1';
unsigned char dig5='0';
unsigned char dig6='0';
unsigned char seg=0;
unsigned char min=0;
unsigned char hora=0;

//////////////////////////////////////////////////////////////////////////////////////////////////////
void reloj(void){
      seg++;
	  dig5=(seg/10)+'0';
	  dig6=(seg%10)+'0';
	  if(seg!=60){
		  LCD_pos_xy(6,0);
		  LCD_write_char(dig5);
		  LCD_write_char(dig6);
	  }
	  else{
		  LCD_pos_xy(6,0);
		  LCD_write_char(dig5);
		  LCD_write_char(dig6);
		  min++;
		  seg=0;
		  dig3=(min/10)+'0';
		  dig4=(min%10)+'0';
		  if(min != 60){
			  LCD_pos_xy(3,0);
			  LCD_write_char(dig3);
			  LCD_write_char(dig4);
		  }
		  else{
			  min=0;
			  hora++;
			  dig1=(hora/10)+'0';
			  dig2=(hora%10)+'0';
			  if(hora!=24){
				  LCD_pos_xy(0,0);
				  LCD_write_char(dig1);
				  LCD_write_char(dig2);
			  }
			  else{
				  hora=0;
		      }  
		  }
	  }
}

void inicializarReloj(void){
	  LCD_pos_xy(0,0);
	  LCD_write_char(dig1);
	  LCD_write_char(dig2);
	  LCD_write_char(':');
	  LCD_write_char(dig3);
	  LCD_write_char(dig4);
	  LCD_write_char(':');
	  LCD_write_char(dig5);
	  LCD_write_char(dig6);
}

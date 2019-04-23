#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "stdio.h"
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

char devolverTecla(char keyPressed){
	switch(keyPressed){
	  case 0b01110111:
		  return '1';
		  break;
	  case 0b01111011:
	  		  return '2';
	  		  break;
	  case 0b01111101:
	  		  return '3';
	  		  break;
	  case 0b01111110:
	  		  return 'A';
	  		  break;
	  case 0b10110111:
	  		  return '4';
	  		  break;
	  case 0b10111011:
	  	  	  return '5';
	  	  	  break;
	  case 0b10111101:
	  	  	  return '6';
	  	  	  break;
	  case 0b10111110:
		      return 'B';
	  	  	  break;
	  case 0b11010111:
	  	  	  return '7';
	  	  	  break;
	  case 0b11011011:
	  	  	  return '8';
	  	  	  break;
	  case 0b11011101:
	  	  	  return '9';
	  	  	  break;
	  case 0b11011110:
	  	  	  return 'C';
	  	  	  break;
	  case 0b11100111:
	  	  	  return '*';
	  	  	  break;
	  case 0b11101011:
	  	  	  return '0';
	  	  	  break;
	  case 0b11101101:
	  	  	  return '#';
	  	  	  break;
	  case 0b11101110:
	  	  	  return 'D';
	  	  	  break;
	}
}

char KEYPAD_Scan(char * key){
	unsigned short fila_act;
	unsigned short col_act;
	char status = 0;
	char f = 0b00000001;
	char c = 0b00000001;
	char fAux;
	char Aux;
	unsigned char PTBDAux = 0b10001000;
	
	for(col_act=0;col_act<3;col_act++){
		PTBD = ~PTBDAux;
		for(fila_act=0;fila_act<3;fila_act++){
			fAux = f<<4;
			Aux = fAux|c;
			Aux = ~Aux;
			if(PTBD == Aux){
				(*key) = devolverTecla(Aux);
				status = 1;
				return(status);
			}
			f = f<<1;
		}
		c = c<<1;
		PTBDAux = PTBDAux>>1;
		c = 0b00000001;
	}
	return(status);
}

void main(void) {
  unsigned char tecla; 
  PTBDD = 0x0F;
  PTBPE = 0xF0;//Seteo la entrada PTCD0 con una resistencia pull up interna
	
  MCU_init();
  LCD_init(_2_LINES|DISPLAY_8X5,DISPLAY_ON|CURSOR_ON);
  
  for(;;) {
    if(KEYPAD_Scan(&tecla)){
    	LCD_pos_xy(0,0);
    	LCD_write_char('A');
    }
    else{
    	LCD_pos_xy(0,0);
    	LCD_write_char('B');
    }
    delay(200);
	  /* __RESET_WATCHDOG(); By default COP is disabled with device init. When enabling, also reset the watchdog. */
  } /* loop forever */
  /* please make sure that you never leave main */
}


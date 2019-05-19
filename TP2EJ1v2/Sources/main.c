#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "stdio.h"
#include "lcd.h"


#ifdef __cplusplus
extern "C"
#endif

typedef enum{abierto,cerrado,denegado,cambiarClave,nuevaClave,finNuevaClave}state;
#define TIMEOUT 15

extern volatile unsigned char RTC_flag;//Extern porque se inicializa en el init, volatile por ser global

void MCU_init(void); /* Device initialization function declaration */

//Inicializacion de variables globales para el timer
state estado=cerrado;
unsigned char pass[] = "2580";
unsigned char passAux[] = "    ";
unsigned short dimL = 4;
unsigned short indice = 0;
unsigned short indice2 = 0;
unsigned char probando;
unsigned short timeInState = 0;
unsigned short cond = 1;


////////////////////////////////////////////////////////////////////////////////////////////////////
void cambiarEstado(state estadoNuevo){
	estado=estadoNuevo;
	timeInState=0;
	indice=0;
	indice2=0;
	LCD_pos_xy(0,1);
	LCD_write_string("                ");
	cond = 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void comprobarClave(unsigned char tecla){
	probando=pass[indice];
	if (probando!=tecla){
		cond=0;
	}
	if((cond)&&(indice!=(dimL-1))){//Si le pega a la tecla, y el indice sigue siendo valido
		indice++;
	}else{
		if(!cond){
			if(indice == 3){
				cambiarEstado(denegado);
				LCD_pos_xy(0,1);
				LCD_write_char(tecla);
			}
			indice++;
			
		}else{
			if(estado==cerrado){
				cambiarEstado(abierto);
			}else{//Estoy en el estado cambiar clave
				cambiarEstado(nuevaClave);
			}
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void timeOut(){
	if(timeInState == TIMEOUT){
		cambiarEstado(cerrado);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
void setearClave(unsigned char tecla){
	if(tecla == '#'){
		cambiarEstado(cerrado);
	}else{
		if(tecla == 'D' && indice2==4){
			pass[0]=passAux[0];
			pass[1]=passAux[1];
			pass[2]=passAux[2];
			pass[3]=passAux[3];
			cambiarEstado(finNuevaClave);
		}
		else{
			if( (tecla!='*') && (indice2 != 4) ){
				passAux[indice2]=tecla;
				indice2++;
			}else{
				LCD_pos_xy(0,1);
				cambiarEstado(cambiarClave);
			}
		}
			
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////
void ejecutarEstado(){
	unsigned char tecla; 
	switch(estado){
		case cerrado:
			LCD_pos_xy(0,1);
			LCD_write_string("CERRADO         ");
			if(KEYPAD_Scan(&tecla)){
				if(tecla=='D'){
					cambiarEstado(cambiarClave);
				}else{
					comprobarClave(tecla);
					delay(20);
				}
			}
			break;
		case abierto:
			LCD_pos_xy(0,1);
			LCD_write_string("ABIERTO         ");
			if(timeInState == 5){
				cambiarEstado(cerrado);
			}
			break;
		case denegado:
			LCD_pos_xy(0,1);
			LCD_write_string("DENEGADO       ");
			if(timeInState == 2){
				cambiarEstado(cerrado);
			}
			break;
		case cambiarClave:
			//ejecutarCambiarClave();
			LCD_pos_xy(0,1);
			LCD_write_string("Clave act:");
			if(KEYPAD_Scan(&tecla)){
				LCD_pos_xy(indice+10,1);
			    LCD_write_char('*');
				comprobarClave(tecla);
				delay(20);
			}
			break;
		case nuevaClave:
			//ejecutarNuevaClave();
			LCD_pos_xy(0,1);
		    LCD_write_string("Nueva clave:");
			if(KEYPAD_Scan(&tecla)){
				setearClave(tecla);
				delay(20);
				LCD_pos_xy(indice2+11,1);
				LCD_write_char('*');
			}
			break;
		case finNuevaClave:
			//ejecutarFinNuevaClave();
			LCD_pos_xy(0,1);
			LCD_write_string("FIN NUEVA CLAVE");
			if(timeInState == 5){
				cambiarEstado(cerrado);
			}
			break;
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

void main(void) {
  
  PTBDD = 0x0F;
  PTBPE = 0xF0;//Seteo la entrada PTB con una resistencia pull up interna
  
  MCU_init();	/* call Device Initialization */
  LCD_init(_2_LINES|DISPLAY_8X5,DISPLAY_ON|CURSOR_ON);
  inicializarReloj();

  
  for(;;) {
	 
	  if(RTC_flag == 1){
		  RTC_flag=0;
		  timeInState++;
		  reloj();
	  }//Termina el chequeo de la hora
	  ejecutarEstado();
	  timeOut();
  }
}

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
unsigned char dig1='1';
unsigned char dig2='6';
unsigned char dig3='5';
unsigned char dig4='1';
unsigned char dig5='0';
unsigned char dig6='0';
unsigned char seg=0;
unsigned char min=51;
unsigned char hora=16;
int cont=0;
state estado=cerrado;
unsigned char pass[] = "2580";
unsigned char passAux[] = "    ";
unsigned short dimL = 4;
unsigned short indice = 0;
unsigned short indice2 = 0;
unsigned char probando;
unsigned short timeInState = 0;
unsigned short cond = 1;


//////////////////////////////////////////////////////////////////////////////////////////////////////
void reloj(void){
	if(cont == 9){//Para el reloj
      seg++;
	  dig5=(seg/10)+'0';
	  dig6=(seg%10)+'0';
	  cont=0;
	  timeInState++;
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
}

////////////////////////////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////////////////////////////
char devolverTecla(char keyPressed){
	switch(keyPressed){
	  case 0b01110111:
		  return 'D';
		  break;
	  case 0b01111011:
	  		  return 'C';
	  		  break;
	  case 0b01111101:
	  		  return 'B';
	  		  break;
	  case 0b01111110:
	  		  return 'A';
	  		  break;
	  case 0b10110111:
	  		  return '#';
	  		  break;
	  case 0b10111011:
	  	  	  return '9';
	  	  	  break;
	  case 0b10111101:
	  	  	  return '6';
	  	  	  break;
	  case 0b10111110:
		      return '3';
	  	  	  break;
	  case 0b11010111:
	  	  	  return '0';
	  	  	  break;
	  case 0b11011011:
	  	  	  return '8';
	  	  	  break;
	  case 0b11011101:
	  	  	  return '5';
	  	  	  break;
	  case 0b11011110:
	  	  	  return '2';
	  	  	  break;
	  case 0b11100111:
	  	  	  return '*';
	  	  	  break;
	  case 0b11101011:
	  	  	  return '7';
	  	  	  break;
	  case 0b11101101:
	  	  	  return '4';
	  	  	  break;
	  case 0b11101110:
	  	  	  return '1';
	  	  	  break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
char KEYPAD_Scan(char * key){
	unsigned short fila_act;
	unsigned short col_act;
	char f = 0b00000001;
	char c = 0b00000001;
	char cAux;
	char Aux;
	unsigned char PTBDAux = 0b00000001;//C4C3C2C1F4F3F2F1
	
	for(fila_act=0;fila_act<4;fila_act++){
		PTBD = ~(PTBDAux<<fila_act);
		for(col_act=0;col_act<4;col_act++){
			cAux = c<<4;
			Aux = cAux|f;
			Aux = ~Aux;
			if(PTBD == Aux){
				(*key) = devolverTecla(Aux);
				while(PTBD==Aux);//Para que no salga hasta que no se suelte la tecla
				return(1);
			}
			c = c<<1;
		}
		f = f<<1;
		c = 0b00000001;
	}
	return(0);
}


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
			if(KEYPAD_Scan(&tecla)){
				if(tecla=='D'){
					cambiarEstado(cambiarClave);
				}else{
					comprobarClave(tecla);
					delay(20);
				}
			}
			LCD_pos_xy(0,1);
			LCD_write_string("CERRADO         ");
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
		  RTC_flag=0;
		  reloj();
	  }//Termina el chequeo de la hora
	  ejecutarEstado();
	  timeOut();
	  }
}

#include "derivative.h" /* include peripheral declarations */

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

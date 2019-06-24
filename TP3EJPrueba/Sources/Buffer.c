#include "derivative.h"
#define BUFFER_SIZE 150

/*uint8 indice_lectura = 0; //Indice de lectura del buffer
uint8 indice_escritura = 0;//Indice de escritura del buffer
uint8 buffer[BUFFER_SIZE]; // Buffer para transmision
//volatile uint8 flag_ent = FALSE; // flag que advierte que está disponible la nueva entrada
//volatile uint8 Flag_Transmisor = FALSE; // si esta en TRUE indica que el buffer esta ocupado*/

char comando = 0; //Comando recibido por la terminal

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

void escribir_en_buffer(void) {
	if (SCIS1_RDRF == 1) { //Si esta disponible para leer
		comando = SCID;//Leo
	}
}


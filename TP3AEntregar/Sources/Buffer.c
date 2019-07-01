#include "derivative.h"
#define TX_BUFFER_SIZE 150
#define RX_BUFFER_SIZE 150

//Buffer para transmision y sus indices
unsigned short indice_lectura_TX = 0; //Indice de lectura del buffer TX
unsigned short indice_escritura_TX = 0;//Indice de escritura del buffer TX
char bufferTX[TX_BUFFER_SIZE]; // Buffer para transmision

//Buffer para recepcion y sus indices
unsigned short indice_lectura_RX = 0; //Indice de lectura del buffer RX
unsigned short indice_escritura_RX = 0;//Indice de escritura del buffer RX
char bufferRX[RX_BUFFER_SIZE]; // Buffer para recepcion


//volatile uint8 Flag_Transmisor = FALSE; // si esta en TRUE indica que el buffer esta ocupado*/

volatile char RX_flag = 0;

extern volatile char comando; //Comando recibido por la terminal

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

//Recepcion de datos

void escribir_en_bufferRX(void) {
	char car;
	if (SCIS1_RDRF) { //Si esta disponible para leer
		car = SCID;//Leo el primer caracter
	}
	if(car != '\n'){
		bufferRX[indice_escritura_RX] = car;
		indice_escritura_RX++;
	}
	else{
		RX_flag = 1;//Se prende cuando lee todo el string
	}
}

char* leer_comando(void){
	char lectura[RX_BUFFER_SIZE];
	short indiceAux = 0;
	
	while(indice_lectura_RX < indice_escritura_RX){
		lectura[indiceAux] = bufferRX[indice_lectura_RX];
		indice_lectura_RX++;
		indiceAux++;//Se podria dejar solo indice_lectura_RX, fijate que queda mejor
	}
	lectura[indiceAux] = '\0';//Para que al leer el comando haya un corte de control
	
	indice_lectura_RX = 0;//Se reinician ambos punteros
	indice_escritura_RX = 0;
	
	return lectura;//Devuelvo lo que lei
}


void SCI_escribir_char_al_buffer(char dato){
	if (indice_escritura_TX < TX_BUFFER_SIZE) { // si hay lugar en el buffer guarda un dato
		bufferTX[indice_escritura_TX] = dato; 
		indice_escritura_TX++;
	}
}


//Transmision de datos

void SCI_enviar_cadena(char *cadena){
	while (*cadena != '\0') {
		SCI_escribir_char_al_buffer(*cadena);//Por lo visto toma este llamado como si fuera un prototipo, y genera el error abajo, lo vemos desp
		cadena++;
	}
	SCIC2_TIE = 1; //Habilita las interrupciones de transmision
	delay(400);  //Delay de 400ms
}

void SCI_update(void) {
	if (indice_escritura_TX > indice_lectura_TX) {//Si el indice de escritura es mayor, hay caracteres a transmitir
		if (SCIS1_TDRE) { //Si esta disponible el trasmisor
			SCID = bufferTX[indice_lectura_TX];
			indice_lectura_TX++;
		}
	} else { //Reinicio los indices y deshabilito la interrupcion
		indice_lectura_TX = 0;
		indice_escritura_TX = 0;
		SCIC2_TIE = 0;
	}
}


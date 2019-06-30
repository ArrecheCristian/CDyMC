
#include "definicion.h"
#include "derivative.h"

uint8 car = 0; // variable correspondiente al caracter de entrada del dispositivo
uint8 TXindice_lec = 0;
uint8 TXindice_esc = 0; // indices de control del buffer
uint8 TX_Buffer[TX_BUFFER_LENGTH]; // buffer interno donde se almacenan los strings antes de transmitir
volatile uint8 flag_ent = FALSE; // flag que advierte que está disponible la nueva entrada
//volatile uint8 Flag_Transmisor = FALSE; // si esta en TRUE indica que el buffer esta ocupado

void delay(void) {
	/**
	 * funcion delay utilizada en las transmisiones
	 * aproximadamente 400 ms
	 */
	short i;
	for (i = 0; i < 0xFFFF; i++)
		;
	for (i = 0; i < 0xFFFF; i++)
		;
}

void SCI_RX_Handler(void) {
	/**
	 * Funcion que se ejecuta cuando hay 
	 * interrupcion de recepción
	 */
	if (SCIS1_RDRF == 1) { // se pone nuevamente en 0 al leer
		car = SCID;
//		if (entrada == '\n') {
//			entrada = 0; 
//			// si se obtiene un mensaje de respuesta del modulo bluetooth se descarta la entrada
//		}
		flag_ent = TRUE; // flag que indica que el string ya esta disponible
	}
}

void SCI_write_char_to_buffer(uint8 dato) {
	if (TXindice_esc < TX_BUFFER_LENGTH) { // si hay lugar en el buffer guarda un dato
		TX_Buffer[TXindice_esc] = dato; 
		TXindice_esc++;
	}
}

void SCI_write_string(uint8 * STR) {
//	while (Flag_Transmisor)
//		; //espera que este ready el buffer
	while (*STR != '\0') {
		SCI_write_char_to_buffer(*STR);
		STR++;
	}
//	Flag_Transmisor = TRUE;
	SCIC2_TIE = 1; //habilita las interrupciones de transmision
	delay();
}

void SCI_update(void) {
	if (TXindice_lec < TXindice_esc) {
		/**
		 * si los indices no son iguales, hay caracteres en el buffer para transmitir
		 */
		if (SCIS1_TDRE) { // si esta disponible el transmisor procede a transmitir
			SCID = TX_Buffer[TXindice_lec];
			TXindice_lec++;
		}
	} else { // si se termino la transmision se reinicializan las variables
		TXindice_lec = 0;
		TXindice_esc = 0;
//		Flag_Transmisor = FALSE;
		SCIC2_TIE = 0; //deshabilita las interrupciones de transmision
	}
}


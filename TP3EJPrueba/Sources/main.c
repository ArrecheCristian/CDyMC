#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */


void MCU_init(void); /* Device initialization function declaration */

void SCI_enviar_cadena(char *cadena){
	while(*cadena!='\0'){
		while(SCIS1_TDRE==0);//Si esta en 0, es que esta ocupado asi que tengo que esperar, en 1 el transmisor me avisa que esta listo para transmitir
		SCID=*cadena;
		cadena++;
	}
}


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

//char comando[]="AT+PIN\r\n";//Este modulo como es chino necesita el \r \n, es para ver en que estado esta, deberia responder "OK\r\n" porque esta en modo AT
void main(void) {
	char respuesta[5];
	char bienvenida[]="Bienvenido";
	char aux;

	short int i=0;
	MCU_init();
  
	while(PTBD_PTBD2==0);
	for(;;) {
			if(SCIS1_RDRF!=0){
				respuesta[i]=SCID;
				i++;
			}
			else{
				respuesta[i] = '\0';
				SCI_enviar_cadena(respuesta);
				i=0;
			}
	}
}

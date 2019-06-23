#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include <string.h>
#define N 50


void MCU_init(void); /* Device initialization function declaration */


extern volatile short int RX_flag; //Flag de recepción de datos
extern volatile short int TX_flag; //Flag de transmision de datos

unsigned short int lleno = 0;
unsigned short int vacio = 0;
unsigned short sync_flag = 0;
char buffer[N];


// --------------------------------Funciones y programa principal---------------------------------------

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

void menu_inicio(){
	
	//Cadenas para mensaje de bienvenida
	char linea1[] = "Bienvenido, elija su comando:\n";
	char linea2[] = "- Ejemplo de comandos para configuración de frecuencia\n";
	char linea3[] = "1) 100 --> 100Hz\n";
	char linea4[] = "1) 300 --> 300Hz\n";
	char linea5[] = "2) 1k --> 1000Hz\n";
	char linea6[] = "2) 2k --> 2000Hz\n";
	char linea7[] = "- Comandos de control\n";
	char linea8[] = "1) ON --> Encender parlante\n";
	char linea9[] = "2) OFF --> Apagar parlante";
	char linea10[] = "3) RESET --> Volver a inicializar el MCU";
	
	SCI_enviar_cadena(linea1);
	SCI_enviar_cadena(linea2);
	SCI_enviar_cadena(linea3);
	SCI_enviar_cadena(linea4);
	SCI_enviar_cadena(linea5);
	SCI_enviar_cadena(linea6);
	SCI_enviar_cadena(linea7);
	SCI_enviar_cadena(linea8);
	SCI_enviar_cadena(linea9);
	SCI_enviar_cadena(linea10);
}


void guardar_buffer(){
	buffer[vacio] = SCID;
	vacio = (vacio+1) % N;
}



//char comando[]="AT+PIN\r\n";  //Necesita el \r \n, es para ver en que estado esta, deberia responder "OK\r\n" porque esta en modo AT
void main(void) {
	
	MCU_init();
	
	//Espero a que se haga la vinculacion con el dispositivo
	while(PTBD_PTBD2==0);

	menu_inicio();
	
	for(;;) {
			if(RX_flag){
				guardar_buffer();
				sync_flag = 1;
			}
			
			if(TX_flag){
				if(sync_flag){
					
				}
			}	
	}
}

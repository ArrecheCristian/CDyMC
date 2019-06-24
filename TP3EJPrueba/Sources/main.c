#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include <string.h>

#define N 50
#define FALSE 0
#define TRUE 1


void MCU_init(void); /* Device initialization function declaration */

enum comandos{ON, OFF, RESET,FREC};

extern volatile short int RX_flag; //Flag de recepción de datos
extern volatile short int TX_flag; //Flag de transmision de datos

unsigned short int lleno = 0;
unsigned short int vacio = 0;
unsigned char sync_flag = 0;
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
	char menu[] = "Bienvenido, elija su comando:\n"
					" - Comandos para configuracion de frecuencia:\n"
					"   1) 100 --> 100Hz\n";
					//"   2) 300 --> 300Hz\n";
					//"   3) 1k --> 1000Hz\n"
					//"   4) 2k --> 2000Hz\n"
					//" - Comandos de control\n"
					//"   1) ON --> Encender parlante\n"
					//"   2) OFF --> Apagar parlante\n"
					//"   3) RESET --> Volver a inicializar el MCU\n";
	//char linea2[] = "Comandos para configuracion de frecuencia\n";
	//char linea3[] = "1) 100 --> 100Hz\n";
	//char linea4[] = "2) 300 --> 300Hz\n";
	//char linea5[] = "3) 1k --> 1000Hz\n";
	//char linea6[] = "4) 2k --> 2000Hz\n";
	//char linea7[] = "- Comandos de control\n";
	//char linea8[] = "1) ON --> Encender parlante\n";
	//char linea9[] = "2) OFF --> Apagar parlante";
	//char linea10[] = "3) RESET --> Volver a inicializar el MCU";
	
	SCI_enviar_cadena(menu);
	//SCI_enviar_cadena(linea2);
	//SCI_enviar_cadena(linea3);
	//SCI_enviar_cadena(linea4);
	//SCI_enviar_cadena(linea5);
	//SCI_enviar_cadena(linea6);
	//SCI_enviar_cadena(linea7);
	//SCI_enviar_cadena(linea8);
	//SCI_enviar_cadena(linea9);
	//SCI_enviar_cadena(linea10);
}


void escribir_buffer(){
	buffer[vacio] = SCID;
	vacio = (vacio+1) % N;
}


unsigned short int leer_buffer(char* comando, unsigned short int i){
	
	if(vacio == lleno){
		return FALSE;
	}
	else{
		comando[i] = buffer[lleno];
		lleno = (lleno+1) % N;	
		return TRUE;
	}
}


void leer_comando(char *comando){
	unsigned short int i = 0;
	unsigned short int corte;
	comando="     ";
	
	corte = leer_buffer(comando,i);
	
	while (!corte && i<5){
		corte = leer_buffer(comando,i);
		i++;
	}
}

void ejecutar_comando(char *comando){
	
	/*switch(comando){
	
		case "ON   ":
		break;
		{
			
		}
		case "OFF":
		case "off":
		{
					
		}
		case "RESET":
		case "reset":
		{
					
		}
		case "100":
		{
			
		}
	
	}*/
	
}

/*enum convertir_a_enumerativo(char* comando){
	
	return ;
}*/


//char comando[]="AT+PIN\r\n";  //Necesita el \r \n, es para ver en que estado esta, deberia responder "OK\r\n" porque esta en modo AT
void main(void) {
	char mensaje[] = "Recepcion\n";
	char mensaje2[] = "Transmision\n";
	char comando[5];
	//char nombre_default[]="AT+NAMEGrupo8Dos\r\n";

	MCU_init();
	
	//SCI_enviar_cadena(nombre_default);
	
	//Espero a que se haga la vinculacion con el dispositivo
	while(PTBD_PTBD2==0);

	menu_inicio();
	
	sync_flag = 0;

	for(;;) {
			if(RX_flag){
				SCI_enviar_cadena(mensaje);
				RX_flag = 0;
				//escribir_buffer();
				//sync_flag = 1;
			}
			
			if(TX_flag){
				if(sync_flag){
					//leer_comando(comando);
					SCI_enviar_cadena(mensaje2);
					TX_flag=0;
					//enum_comando = convertir_a_enumerativo(comando);
					//ejecutar_comando(enum_comando);
				}
			}	
	}
}

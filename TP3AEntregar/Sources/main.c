#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include <string.h>
#include <buffer.h>

#define N 50
#define FALSE 0
#define TRUE 1

#define F1 40000 //100Hz
#define F2 13333
#define F3 8000
#define F4 4000
#define F5 2000
#define F6 800
#define F7 400
#define F8 333


void MCU_init(void); /* Device initialization function declaration */


extern volatile char RX_flag; //Flag de recepción de comando
volatile short NC; //Frecuencia actual del parlante



// --------------------------------Funciones y programa principal---------------------------------------

void menu_inicio(){
	
	SCI_enviar_cadena("\n\n\nBienvenido, elija su comando:\n");
	SCI_enviar_cadena(" - Comandos para configuracion de frecuencia:\n");
	SCI_enviar_cadena("      1) 100 --> 100Hz\n");
	SCI_enviar_cadena("      2) 300 --> 300Hz\n");
	SCI_enviar_cadena("      3) 500 --> 500Hz\n");
	SCI_enviar_cadena("      4) 1k --> 1000Hz\n");
	SCI_enviar_cadena("      5) 2k --> 2000Hz\n");
	SCI_enviar_cadena("      6) 5k --> 5000Hz\n");
	SCI_enviar_cadena("      7) 10k --> 10000Hz\n");
	SCI_enviar_cadena("      8) 12k --> 12000Hz\n");
	SCI_enviar_cadena(" - Comandos de control\n");
	SCI_enviar_cadena("      A) ON --> Encender parlante\n");
	SCI_enviar_cadena("      B) OFF --> Apagar parlante\n");
	SCI_enviar_cadena("      C) RESET --> Volver a inicializar el MCU");
}

int comparar_comando(char str1[], char str2[])
{
    int ctr=0;

    while(str1[ctr]==str2[ctr])
    {
        if(str1[ctr]=='\0'||str2[ctr]=='\0')
            break;
        ctr++;
    }
    if(str1[ctr]=='\0' && str2[ctr]=='\0')
        return 1;
    else
        return 0;
}

void ejecutar_comando(char comando){
	
	switch(comando){
	
		case '1':
			SCI_enviar_cadena("Frecuencia de 100Hz");
			NC=F1;
		break;
		case '2':
			SCI_enviar_cadena("Frecuencia de 300Hz");
			NC=F2;						
						
		break;
		case '3':
			SCI_enviar_cadena("Frecuencia de 500Hz");
			NC=F3;						
						
		break;
		case '4':
			SCI_enviar_cadena("Frecuencia de 1KHz");
			NC=F4;					
						
		break;
		case '5':
			SCI_enviar_cadena("Frecuencia de 2KHz");
			NC=F5;
									
						
		break;
		case '6':
			SCI_enviar_cadena("Frecuencia de 5KHz");
			NC=F6;					
						
		break;
		case '7':
			SCI_enviar_cadena("Frecuencia de 10KHz");
			NC=F7;					
						
		break;
		case '8':
			SCI_enviar_cadena("Frecuencia de 12KHz");
			NC=F8;						
						
		break;
		case 'A':
			SCI_enviar_cadena("Sonido activado");
			TPM1C1SC=0x54U;
		break;
		case 'B':
			SCI_enviar_cadena("Sonido desactivado");
			TPM1C1SC = 0;								
		break;
		case 'C':
			SCI_enviar_cadena("Dispositivo reseteado");
			NC = F1;
			TPM1C1SC = 0;
			menu_inicio();
		break;
		default:
			SCI_enviar_cadena("Comando invalido");
		break;
	}
	
}

char determinar_comando(char command[]){
	if(comparar_comando(command,"ON\r")){
		return 'A';
	}else{
	
	if(comparar_comando(command,"OFF\r")){
		return 'B';
	}else{
	
	if(comparar_comando(command,"RESET\r")){
		return 'C';
	}else{
	
	if(comparar_comando(command,"100\r")){
		return '1';
	}else{
		
	if(comparar_comando(command,"300\r")){
			return '2';
	}else{
		
	if(comparar_comando(command,"500\r")){
			return '3';
	}else{
		
	if(comparar_comando(command,"1k\r")){
			return '4';
	}else{
	
	if(comparar_comando(command,"2k\r")){
			return '5';
	}else{
	
	if(comparar_comando(command,"5k\r")){
			return '6';
	}else{
		
	if(comparar_comando(command,"10k\r")){
			return '7';
	}else{
		
	if(comparar_comando(command,"12k\r")){
			return '8';
	}}}}}}}}}}}
}

//char comando[]="AT+PIN\r\n";  //Necesita el \r \n, es para ver en que estado esta, deberia responder "OK\r\n" porque esta en modo AT
void main(void) {
	char nombre_default[]="AT+NAMEG8\r\n"; //Nombre por defecto de nuestro modulo bluetooth
	char aux;
	char comando_comparable;
	char *comando;
	MCU_init();
	
	SCI_enviar_cadena(nombre_default); //Se envía el nombre por defecto al módulo
	
	NC = F1;
	TPM1C1SC = 0;//Desactivo las interrupciones por TPM1 CH1
	
	//Espero a que se haga la vinculacion con el dispositivo
	while(PTBD_PTBD2==0);
	
	menu_inicio();
	
	for(;;) {
		if(RX_flag){
			comando = leer_comando();
			comando_comparable = determinar_comando(comando);
			ejecutar_comando(comando_comparable);
			RX_flag = 0;
		}
	}
}

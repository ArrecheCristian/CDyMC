#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#include "bt_mod.h"
#include "SCI.h"

void MCU_init(void); /* Device initialization function declaration */
void SCI_write_string(const char *);
//void delay(const short);
extern volatile uint8 car;
volatile char flag_imp;
extern volatile char flag_ent;
volatile short NC;
volatile short ultimafrec;
void main(void) {
	char temp = 0;
	MCU_init(); /* call Device Initialization */

	delay();
	SCI_write_string("AT+NAMEPPP\r\n");
	while (!PTBD_PTBD2)
		;
	delay();
	PTBDD_PTBDD2 = 0;
	flag_imp = 1;
	TPM1C1SC = 0;
	ultimafrec = frec1; //frecuencia por defecto
	for (;;) {
		while(PTBD_PTBD2==1) {
			if(flag_imp==1) {
				delay();
				SCI_write_string("COMANDOS: \n");
				SCI_write_string("1 PARA 100 HZ\n");
				SCI_write_string("2 PARA 300 HZ\n");
				SCI_write_string("3 PARA 500 HZ\n");
				SCI_write_string("4 PARA 1K HZ\n");
				SCI_write_string("5 PARA 2K HZ\n");
				SCI_write_string("6 PARA 5K HZ\n");
				SCI_write_string("7 PARA 10K HZ\n");
				SCI_write_string("8 PARA 12K HZ\n");
				SCI_write_string("p PARA PRENDER\n");
				SCI_write_string("a PARA APAGAR\n");
				SCI_write_string("r PARA RESETEAR\n");
				flag_imp=0;
			}
			if(flag_ent==1) {
				flag_ent=0;
				switch (car) {
					case '1': SCI_write_string("se eligio la frecuencia 100Hz a\n");
					NC=frec1;
					TPM1C1SC;
					TPM1C1SC=0x54U;
					ultimafrec=NC;
					break;
					case '2': SCI_write_string("se eligio la frecuencia 300Hz b\n");
					NC=frec2;
					TPM1C1SC;
					TPM1C1SC=0x54U;
					ultimafrec=NC;
					break;
					case '3': SCI_write_string("se eligio la frecuencia 500Hz b\n");
					NC=frec3;
					TPM1C1SC;
					TPM1C1SC=0x54U;
					ultimafrec=NC;
					break;
					case '4': SCI_write_string("se eligio la frecuencia 1kHz b\n");
					NC=frec4;
					TPM1C1SC;
					TPM1C1SC=0x54U;
					ultimafrec=NC;
					break;
					case '5': SCI_write_string("se eligio la frecuencia 2kHz b\n");
					NC=frec5;
					TPM1C1SC;
					TPM1C1SC=0x54U;
					ultimafrec=NC;
					break;
					case '6': SCI_write_string("se eligio la frecuencia 5kHz b\n");
					NC=frec6;
					TPM1C1SC;
					TPM1C1SC=0x54U;
					ultimafrec=NC;
					break;
					case '7': SCI_write_string("se eligio la frecuencia 10kHz b\n");
					NC=frec7;
					TPM1C1SC;
					TPM1C1SC=0x54U;
					ultimafrec=NC;
					break;
					case '8': SCI_write_string("se eligio la frecuencia 12kHz b\n");
					NC=frec8;
					TPM1C1SC;
					TPM1C1SC=0x54U;
					ultimafrec=NC;
					break;
					case 'p': SCI_write_string("se eligio prender \n");
					NC=ultimafrec;
					TPM1C1SC;
					TPM1C1SC=0x54U;
					break;
					case 'a': SCI_write_string("se eligio apagar \n");
					TPM1C1SC = 0;
					break;
					case 'r': SCI_write_string("se eligio resetear \n");
					NC=frec1; //frecuencia por defecto
					flag_imp=1;
					break;
					case '\n': delay();
					break;
					default : SCI_write_string("incorrcto \n");
					break;
				}
			}
		}
		while(PTBD_PTBD2==0) {
			flag_imp=1;
			delay();
			delay();
		}
	}

}

//void SCI_write_string(const char * str) {
//
//	while (*str != 0) {
//		while( SCIS1_TDRE == 0);
//		SCID = (*str);
//		str++;
//	}
//
//}
//
//void delay(const short d) {
//	short i;
//	for (i = 0; i != d; i++)
//		;
//}


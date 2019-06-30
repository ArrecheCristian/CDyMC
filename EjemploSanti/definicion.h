
#ifndef DEFINICION_H_
#define DEFINICION_H_

#ifndef uint8
typedef unsigned char uint8;
typedef enum {defecto, barrer, continuo} states;
#endif



#define TRUE 1
#define FALSE 0

/**
 * A continuacion los valores de NC correspondientes a las notas musicales
 */
#define frec1 40000 //100Hz
#define frec2 13333
#define frec3 8000
#define frec4 4000
#define frec5 2000
#define frec6 800
#define frec7 400
#define frec8 333
#define SOL_S 9638
#define LA 9091
#define LA_S 8584
#define SI 8097

#define TX_BUFFER_LENGTH 100
// tamañano del buffer interno que guarda los strings antes de trasmitirlos

#endif /* DEFINICION_H_ */

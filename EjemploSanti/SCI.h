#include "definicion.h"

#ifndef SCI_H_
#define SCI_H_
void delay(void);
void SCI_Handler(void);
void SCI_Update(void);
void SCI_write_char_to_buffer(uint8);
void SCI_write_string(uint8 *);
#endif /* SCI_H_ */


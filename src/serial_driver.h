#ifndef SERIAL_DRIVER_H
#define SERIAL_DRIVER_H

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

void USART_Init(void);
void USART_SendByte(uint8_t data, FILE* stream);

#endif

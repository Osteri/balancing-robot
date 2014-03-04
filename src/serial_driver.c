#include "serial_driver.h"

#include "avr/io.h"
#include "avr/interrupt.h"

#ifndef F_CPU
 #define F_CPU 16000000
#endif

/* Define baud rate. */
#define USART_BAUDRATE 38400
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

volatile unsigned char UART_RX_buf;

void USART_Init(void) {
    UBRR1L = BAUD_PRESCALE; // load lower 8-bits into the low byte of the UBRR register
    UBRR1H = (BAUD_PRESCALE >> 8);
    UCSR1B = 1<<TXEN1 | 1<<RXEN1 | 1<<RXCIE;
    UCSR1C = 1<<UCSZ11 | 1<<UCSZ10;
}

void USART_SendByte(uint8_t data, FILE* stream) {
    while((UCSR1A &(1<<UDRE)) == 0); // wait for last byte
    UDR1 = data; // transmit
}

ISR(USART1_RX_vect) { // receive byte
    UART_RX_buf = UDR1;
}

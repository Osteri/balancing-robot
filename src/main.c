#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdlib.h>

#include "lcd_lib.h"
#include "utilities.h"
#include "L3G4200D.h"
#include "servo_controller.h"

/* Define baud rate */
#define USART_BAUDRATE 38400
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define LCD_VALUE_SLOT_1 0,0    // x and y, usage: LCDGotoXY(LCD_VALUE_SLOT_1)
#define LCD_VALUE_SLOT_2 6,0
#define LCD_VALUE_SLOT_3 12,0
#define LCD_VALUE_SLOT_4 0,1
#define LCD_VALUE_SLOT_5 6,1
#define LCD_VALUE_SLOT_6 12,1

volatile unsigned char UARTbuf;

void USART_Init(void) {
    UBRR1L = BAUD_PRESCALE; // load lower 8-bits into the low byte of the UBRR register
    UBRR1H = (BAUD_PRESCALE >> 8);
    UCSR1B = 1<<TXEN1 | 1<<RXEN1 | 1<<RXCIE;
    UCSR1C = 1<<UCSZ11 | 1<<UCSZ10;
}

ISR(USART1_RX_vect) { // receive byte
    UARTbuf = UDR1;
}

void USART_SendByte(uint8_t data, FILE* stream) {
    while((UCSR1A &(1<<UDRE)) == 0); // wait until last byte has been transmitted
    UDR1 = data; // transmit
}


int main(void) {

    /* Initialize: */
    LCDinit();

    TWIInit();
    L3G4200D_Init();
    USART_Init();
    //Servo_Init();


    /* Prepare: */
    LCDclr();
    sei();

    /* Use printf() to send data with USART. */
    FILE usart_stream = FDEV_SETUP_STREAM(USART_SendByte, NULL, _FDEV_SETUP_WRITE);
    stdout = &usart_stream;

    while (1) {
        uint8_t size_of_buf = sizeof(buf) / sizeof(char);

        _delay_ms(500);

        LCDGotoXY(LCD_VALUE_SLOT_1);
        LCDstring((uint8_t*)"X:", 2);
        LCDstring( (uint8_t*)Double2Chars(L3G4200D_GetX()), size_of_buf - 1 );

        LCDGotoXY(LCD_VALUE_SLOT_2);
        LCDstring((uint8_t*)" Y:", 3);
        LCDstring( (uint8_t*)Double2Chars(L3G4200D_GetY()), size_of_buf - 1 );

        LCDGotoXY(LCD_VALUE_SLOT_4);
        LCDstring((uint8_t*)"Z:", 2);
        LCDstring((uint8_t*)Double2Chars(L3G4200D_GetZ()), size_of_buf - 1 );

        printf("test");

    }
}

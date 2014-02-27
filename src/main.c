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

/* Timer0 prescale. */
#define T0_PS 128

/* Define baud rate. */
#define USART_BAUDRATE 38400
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define LCD_VALUE_SLOT_1 0,0    // x and y, usage: LCDGotoXY(LCD_VALUE_SLOT_1)
#define LCD_VALUE_SLOT_2 6,0
#define LCD_VALUE_SLOT_3 12,0
#define LCD_VALUE_SLOT_4 0,1
#define LCD_VALUE_SLOT_5 6,1
#define LCD_VALUE_SLOT_6 12,1

volatile unsigned char UART_RX_buf;

volatile unsigned int cnt = 0;

void USART_Init(void) {
    UBRR1L = BAUD_PRESCALE; // load lower 8-bits into the low byte of the UBRR register
    UBRR1H = (BAUD_PRESCALE >> 8);
    UCSR1B = 1<<TXEN1 | 1<<RXEN1 | 1<<RXCIE;
    UCSR1C = 1<<UCSZ11 | 1<<UCSZ10;
}

ISR(USART1_RX_vect) { // receive byte
    UART_RX_buf = UDR1;
}

ISR(TIMER0_COMP_vect) {
    cnt++; // tick every 1 ms
}

void USART_SendByte(uint8_t data, FILE* stream) {
    while((UCSR1A &(1<<UDRE)) == 0); // wait for last byte
    UDR1 = data; // transmit
}

int main(void) {

    /* Use timer0 to create "delta time" for integration.
     */
    TCCR0 |= (1<<CS02) | (1<<CS00) | (1<<WGM01);    // CTC
    TIMSK |= (1<<OCIE0);                            // enable OC interrupt
    OCR0 = 0.001 / ( (1.0f / F_CPU) * T0_PS );      // CTC TOP
    OCR0 -= 1;      // it takes one cycle to go TOP -> BOTTOM
    TCNT0 = 0;

    /* Initialize: */
    LCDinit();
    TWIInit();
    L3G4200D_Init();
    USART_Init();
    //Servo_Init();

    /* Prepare: */
    LCDclr();

    /* Use printf() to send data by USART. */
    FILE usart_stream = FDEV_SETUP_STREAM(USART_SendByte, NULL, _FDEV_SETUP_WRITE);
    stdout = &usart_stream;

    sei();

    register float dt = 0.01;
    register float xAngle = 0;

    while (1) {

        if (cnt % 10 == 0) {
            float xDelta = L3G4200D_GetX() * 0.00875f;
            xAngle += xDelta * dt;
            printf("x:%f ", xAngle);
            printf("\r");
        }
    }
}


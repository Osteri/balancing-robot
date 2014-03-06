#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>
#include <stdlib.h>

#include "lcd_lib.h"
#include "utilities.h"
#include "L3G4200D.h"
#include "LSM303DLHC.h"
#include "servo_controller.h"
#include "serial_driver.h"
#include "math.h"

/* Timer0 prescale. */
#define T0_PS 128

#define LCD_VALUE_SLOT_1 0,0    // x and y, usage: LCDGotoXY(LCD_VALUE_SLOT_1)
#define LCD_VALUE_SLOT_2 6,0
#define LCD_VALUE_SLOT_3 12,0
#define LCD_VALUE_SLOT_4 0,1
#define LCD_VALUE_SLOT_5 6,1
#define LCD_VALUE_SLOT_6 12,1

volatile unsigned int cnt = 0;

ISR(TIMER0_COMP_vect) {
    cnt++; // tick every 1 ms
}

int main(void) {

    /* Use timer0 to create "delta time" for integration. */
    TCCR0 |= (1<<CS02) | (1<<CS00) | (1<<WGM01);    // CTC
    TIMSK |= (1<<OCIE0);                            // enable OC interrupt
    OCR0 = 0.001 / ( (1.0f / F_CPU) * T0_PS );      // CTC TOP
    OCR0 -= 1;      // it takes one cycle to go TOP -> BOTTOM
    TCNT0 = 0;

    /* Initialize: */
    LCDinit();
    TWIInit();
    L3G4200D_Init();
    LSM303DLHC_Init();
    USART_Init();
    //Servo_Init();

    /* Prepare: */
    LCDclr();

    /* Use printf() to send data with USART. */
    FILE usart_stream = FDEV_SETUP_STREAM(USART_SendByte, NULL, _FDEV_SETUP_WRITE);
    stdout = &usart_stream;

    sei();

    //register float dt = 0.01;
    //register float xAngle = 0;

    int j = 0, sum = 0;

    int accel_center_x = LSM303DLHC_GetX();
    int accel_center_y = LSM303DLHC_GetY();
    int accel_center_z = LSM303DLHC_GetZ();

    float a_angle_x, a_angle_y;

    while (1) {

//        if (cnt % 10 == 0) {
//            j++;
//            sum += abs(L3G4200D_GetX());
        float x_val, y_val, z_val, result;
        unsigned int x2, y2, z2; //24 bit

        // Lets get the deviations from our baseline
        x_val = LSM303DLHC_GetX() - accel_center_x;
        y_val = LSM303DLHC_GetY() - accel_center_y;
        z_val = LSM303DLHC_GetZ() - accel_center_z;

        // Work out the squares
        x2 = (unsigned int)(x_val*x_val);
        y2 = (unsigned int)(y_val*y_val);
        z2 = (unsigned int)(z_val*z_val);

        //X Axis
        result=sqrt(y2+z2);
        result=x_val/result;
        //a_angle_x = atan(result) * 0.001f;

        //Y Axis
        result=sqrt(x2+z2);
        result=y_val/result;
        //a_angle_y = atan(result) * 0.001f;


            //float xDelta = L3G4200D_GetX() * 0.00875f;
            //xAngle += xDelta * dt;
            printf("x:%f \r",1.0 );


//            if (j>1000) {
//                double avg = (double)sum / (double)j;
//                printf("\n avg: %f", avg );
//                while(1);
//            }
//        }
    }
}



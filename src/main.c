#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include <stdio.h>

#include "lcd_lib.h"

#define T1_PS 8

#define SHOW_1_DEC 4    // how many decimals we're showing
#define SHOW_2_DEC 5
#define SHOW_3_DEC 6
#define SHOW_4_DEC 7
#define SHOW_5_DEC 8
#define SHOW_6_DEC 9

#define LCD_VALUE_SLOT_1 0,0    // x and y, usage: LCDGotoXY(LCD_VALUE_SLOT_1)
#define LCD_VALUE_SLOT_2 6,0
#define LCD_VALUE_SLOT_3 12,0
#define LCD_VALUE_SLOT_4 0,1
#define LCD_VALUE_SLOT_5 6,1
#define LCD_VALUE_SLOT_6 12,1

char* Double2Chars(double num);

static char buf[SHOW_6_DEC] = ""; // for double2chars conversion

int main(void) {
    DDRB = 0xFF; // PWM
    PORTB = 0x00;

    LCDinit();
    LCDclr();
    _delay_ms(100); // LCD start time

    TCCR1A |= 1<<COM1A1 | 1<<COM1A0 | 1<<WGM11; // inverted fast PWM: (1<<COM1A0)
    TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS11; // prescaler: 8
    ICR1 = 43399;

    /* Pause pulse width 20 ms + control pulse width 1.7 ms (max) = 21.7 ms.
     * 43 400 in OCR1 = 21.7 ms.
     *
     * Possible OCR1A values: 399999 - 40799.
     * .---------------.-------.---------.-------.
     * | Rotation:     | CW    | STEADY  | CCW   |
     * |---------------.--------.--------.-------.
     * | OCR1A - x:    |x: 2600 |x: 3000 |x: 3400|
     * |---------------.-------.---------.-------.
     * | ms:           | 1.3   | 1.5     | 1.7   |
     */

    int a = 2600;

    while (1) {
        LCDGotoXY(LCD_VALUE_SLOT_1);
        LCDstring( (uint8_t*)Double2Chars(OCR1A), (uint8_t)sizeof(buf) - 1);

       // a++;
       // _delay_ms(10);
       // OCR1A = ICR1 - a;
       // _delay_ms(200);
       // OCR1A = ICR1 - (3400+a);
       // _delay_ms(200);
        OCR1A = ICR1 - 3000;

    }
}

/**
 * @brief Convert double value to corresponding char array.
 *
 * Size of the buf defines how many digits we are converting from double
 * to char array (buf). If the buf size is 6, then M_PI becomes "3.141".
 * If the buf size is 4, then M_PI becomes "3.1" and so on.
 *
 * @param num Double value being converted to char array.
 *
 * @returns Pointer to converted char array.
 *
 * @example char* buf[6] = Double2Chars(M_PI); // buf is now "3.141"
 *
 * @author Oskari Teeri
 * @date 26.1.2014
 **/
char* Double2Chars(double num) {
    static char buf[SHOW_3_DEC] = "";
    snprintf(buf, sizeof(double) * 8, "%f", num);
    return buf;
}



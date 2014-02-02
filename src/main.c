#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include "lcd_lib.h"
#include "utilities.h"
#include "L3G4200D.h"

#define LCD_VALUE_SLOT_1 0,0    // x and y, usage: LCDGotoXY(LCD_VALUE_SLOT_1)
#define LCD_VALUE_SLOT_2 6,0
#define LCD_VALUE_SLOT_3 12,0
#define LCD_VALUE_SLOT_4 0,1
#define LCD_VALUE_SLOT_5 6,1
#define LCD_VALUE_SLOT_6 12,1

int main(void) {
    //DDRB = 0xFF; // PWM
    //PORTB = 0x00;

    LCDinit();
    LCDclr();
    _delay_ms(100); // LCD start time


    /* Pause pulse width 20 ms + control pulse width 1.7 ms (max) = 21.7 ms.
     * 43 400 in OCR1 = 21.7 ms period.
     *
     * Possible OCR1A values: 399999 - 40799.
     * .---------------.-------.---------.-------.
     * | Rotation:     | CW    | STEADY  | CCW   |
     * |---------------.--------.--------.-------.
     * | OCR1A - x:    |x: 2600 |x: 3000 |x: 3400|
     * |---------------.-------.---------.-------.
     * | ms:           | 1.3   | 1.5     | 1.7   | */
    TCCR1A |= 1<<COM1A1 | 1<<WGM11;          // fast PWM
    TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS11; // prescaler: 8

    OCR1A = 3000;           // steady by default
    ICR1 = 39999 + OCR1A;

    L3G4200D_Init();

    sei();

    while (1) {
        //LCDGotoXY(LCD_VALUE_SLOT_1);
        //LCDstring( (uint8_t*)Double2Chars(a), (uint8_t)sizeof(buf) - 1);

        _delay_ms(100);
        uint8_t data = L3G4200D_ReadAddress();

        LCDGotoXY(LCD_VALUE_SLOT_1);
        LCDstring( (uint8_t*)Double2Chars(data), (uint8_t)sizeof(buf) - 1);

    }
}

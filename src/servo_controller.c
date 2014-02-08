#include "servo_controller.h"

#include <avr/interrupt.h>

void Servo_Init(void) {

    /* Pause pulse width 20 ms + control pulse width 1.7 ms (max) = 21.7 ms.
    * 43 400 in OCR1 = 21.7 ms period.
    *
    *  Possible OCR1A values: 399999 - 40799.
    * .---------------.-------.---------.-------.
    * | Rotation:     | CW    | STEADY  | CCW   |
    * |---------------.--------.--------.-------.
    * | OCR1A - x:    |x: 2600 |x: 3000 |x: 3400|
    * |---------------.-------.---------.-------.
    * | ms:           | 1.3   | 1.5     | 1.7   |
    */
    TCCR1A |= 1<<COM1A1 | 1<<WGM11;          // fast PWM
    TCCR1B |= 1<<WGM13 | 1<<WGM12 | 1<<CS11; // prescaler: 8

    OCR1A = 3000;           // steady by default
    ICR1 = 39999 + OCR1A;
}


#define F_CPU 16000000UL

#include <avr/io.h>

#include <util/delay.h>

#include "lcd_lib.h"
#include "utilities.h"
#include "L3G4200D.h"
#include "servo_controller.h"

#define LCD_VALUE_SLOT_1 0,0    // x and y, usage: LCDGotoXY(LCD_VALUE_SLOT_1)
#define LCD_VALUE_SLOT_2 6,0
#define LCD_VALUE_SLOT_3 12,0
#define LCD_VALUE_SLOT_4 0,1
#define LCD_VALUE_SLOT_5 6,1
#define LCD_VALUE_SLOT_6 12,1

int main(void) {

    _delay_ms(100);
    LCDinit();
    LCDclr();

    L3G4200D_Init();
    Servo_Init();

    while (1) {
        _delay_ms(100);
        int data = L3G4200D_ReadAddress();
        LCDGotoXY(LCD_VALUE_SLOT_1);
        uint8_t size_of_buf = sizeof(buf) / sizeof(char);
        LCDstring( (uint8_t*)Double2Chars(data), size_of_buf - 1 );
    }
}

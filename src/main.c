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

    /* Initialize: */
    LCDinit();

    TWIInit();
    L3G4200D_Init();
    //Servo_Init();

    /* Prepare: */
    LCDclr();


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
    }
}

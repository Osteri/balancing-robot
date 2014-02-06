#include "L3G4200D.h"


/* SDO pin connected to Vcc -> SDO_PIN = 1
 * SDO pin connected to GND -> SDO_PIN = 0
 */

//#define SDO_PIN

#ifdef SDO_PIN
    #define L3G4200D_R_ADDR 0xD1
    #define L3G4200D_W_ADDR 0xD0
#else
    #define L3G4200D_R_ADDR 0xD3
    #define L3G4200D_W_ADDR 0xD2
#endif

void L3G4200D_Init(void) {
    TWIInit();
}

uint8_t L3G4200D_ReadAddress(void) {
    uint8_t u8data;
    TWIStart();
    TWIWrite((uint8_t)(L3G4200D_W_ADDR));
    TWIWrite((uint8_t)(0x0F));
    TWIStart();
    TWIWrite((uint8_t)(L3G4200D_R_ADDR));
    u8data = TWIReadNACK();
    TWIStop();
    return u8data;

//    uint8_t u8data;
//    TWIStart();
//    TWIWrite((uint8_t)(DS1307_ADDR));
//    TWIWrite((uint8_t)(mem));
//    TWIStart();
//    TWIWrite((uint8_t)(DS1307_ADDR + 1));
//    u8data = TWIReadNACK();
//    TWIStop();
//    return u8data;
}

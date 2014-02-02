#include "L3G4200D.h"


void L3G4200D_Init(void) {
    TWIInit();
}

uint8_t L3G4200D_ReadAddress(void) {
    TWIStart();
    TWIWrite((uint8_t)(L3G4200D_W_ADDR));
    TWIWrite((uint8_t)(0x0F));
    TWIStart();
    TWIWrite((uint8_t)(L3G4200D_R_ADDR));
    uint8_t data = TWIReadNACK();
    TWIStop();
    return data;

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

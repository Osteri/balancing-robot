#include "L3G4200D.h"

/*
 * L3G4200D I²C address will change 0xD0 or 0xD2, depending
 * if the SDO pin is connected to Vcc or GND.
 *
 * SDO pin address configuration gives us ability to connect two
 * identical gyros.
 *
 * SDO pin connected to Vcc -> #define SDO_PIN
 * SDO pin connected to GND -> // nothing
 */
#ifdef SDO_PIN
    #define L3G4200D_R_ADDR 0xD1
    #define L3G4200D_W_ADDR 0xD0
#else
    #define L3G4200D_R_ADDR 0xD3
    #define L3G4200D_W_ADDR 0xD2
#endif

#define CTRL_REG1 0x20

void L3G4200D_Init(void) {
    TWIInit();

    TWIStart();
    TWIWrite((uint8_t)(L3G4200D_W_ADDR));
    TWIWrite((uint8_t)(CTRL_REG1));
    TWIWrite((uint8_t)(0x0F));
    //TWIWrite((uint8_t)(L3G4200D_W_ADDR));
    //u8data = TWIReadNACK();
    TWIStop();
}

uint8_t L3G4200D_ReadAddress(void) {

    uint8_t u8data;
    TWIStart();
    TWIWrite((uint8_t)(L3G4200D_W_ADDR));
    TWIWrite((uint8_t)(0x26));
    TWIStart();
    TWIWrite((uint8_t)(L3G4200D_R_ADDR));
    u8data = TWIReadNACK();
    TWIStop();
    return u8data;
}

#ifndef L3G4200D_H
#define L3G4200D_H

#include "TWIPrimitives.h"

/* SDO pin connected to Vcc -> SDO_PIN = 1
 * SDO pin connected to GND -> SDO_PIN = 0 */
//#define SDO_PIN 0

//#ifdef SDO_PIN
//#define L3G4200D_R_ADDR 0xD1
//#define L3G4200D_W_ADDR 0xD0
//#else
        #define L3G4200D_R_ADDR 0xD3
        #define L3G4200D_W_ADDR 0xD2
//#endif

void L3G4200D_Init(void);

uint8_t L3G4200D_ReadAddress(void);

#endif

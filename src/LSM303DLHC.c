#include "LSM303DLHC.h"

void LSM303DLHC_Init(void) {

    TWISetData(L3G4200D_ADDR, L3G4200D_CTRL_REG1, 0x0F); // start gyro
}

uint8_t L3G4200D_GetTemp(void) {
    return TWIGetData(L3G4200D_ADDR, L3G4200D_OUT_TEMP);
}

int L3G4200D_GetX(void) {
    uint16_t data;
    data = TWIGetData(L3G4200D_ADDR, L3G4200D_OUT_X_H); // MSB
    data <<= 8;
    data |= TWIGetData(L3G4200D_ADDR, L3G4200D_OUT_X_L); // LSB
    return data;
}

int L3G4200D_GetY(void) {
    uint16_t data;
    data = TWIGetData(L3G4200D_ADDR, L3G4200D_OUT_Y_H); // MSB
    data <<= 8;
    data |= TWIGetData(L3G4200D_ADDR, L3G4200D_OUT_Y_L); // LSB
    return data;
}

int L3G4200D_GetZ(void) {
    uint16_t data;
    data = TWIGetData(L3G4200D_ADDR, L3G4200D_OUT_Z_H); // MSB
    data <<= 8;
    data |= TWIGetData(L3G4200D_ADDR, L3G4200D_OUT_Z_L); // LSB
    return data;
}

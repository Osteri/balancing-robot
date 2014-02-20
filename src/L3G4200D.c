#include "L3G4200D.h"

/*
 * L3G4200D I²C address will change 0xD0 or 0xD2, depending
 * if the SDO pin is connected to Vcc or GND.
 *
 * SDO pin address configuration gives the ability to connect two
 * identical gyroscopes.
 *
 * SDO pin connected to Vcc -> #define SDO_PIN
 * SDO pin connected to GND -> // nothing
 */
#ifdef SDO_PIN
  #define L3G4200D_ADDR 0xD0
#else
  #define L3G4200D_ADDR 0xD2
#endif

/* Control registers */
#define L3G4200D_CTRL_REG1 0x20
#define L3G4200D_CTRL_REG2 0x21
#define L3G4200D_CTRL_REG3 0x22
#define L3G4200D_CTRL_REG4 0x23
#define L3G4200D_CTRL_REG5 0x24

/* Output registers*/
#define L3G4200D_REFERENCE 0x25
#define L3G4200D_OUT_TEMP 0x26
#define L3G4200D_STATUS_REG 0x27
#define L3G4200D_OUT_X_L 0x28
#define L3G4200D_OUT_X_H 0x29
#define L3G4200D_OUT_Y_L 0x2A
#define L3G4200D_OUT_Y_H 0x2B
#define L3G4200D_OUT_Z_L 0x2C
#define L3G4200D_OUT_Z_H 0x2D
#define L3G4200D_FIFO_CTRL_REG 0x2E
#define L3G4200D_FIFO_SRC_REG 0x2F
#define L3G4200D_INT1_CFG 0x30
#define L3G4200D_INT1_SRC 0x31
#define L3G4200D_INT1_TSH_XH 0x32
#define L3G4200D_INT1_TSH_XL 0x33
#define L3G4200D_INT1_TSH_YH 0x34
#define L3G4200D_INT1_TSH_YL 0x35
#define L3G4200D_INT1_TSH_ZH 0x36
#define L3G4200D_INT1_TSH_ZL 0x37
#define L3G4200D_INT1_DURATION 0x38

void L3G4200D_Init(void) {
    /* Write (0x0F) to CTRL_REG1 for switching to Normal mode.
     * Default mode (0x0E) is power saving mode. */
    TWISetData(L3G4200D_ADDR, L3G4200D_CTRL_REG1, 0x0F);
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


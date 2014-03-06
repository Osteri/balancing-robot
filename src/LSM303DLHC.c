#include "LSM303DLHC.h"

#define LSM303DLHC_ADDR 0x32

#define CTRL_REG1_A 0x20
#define CTRL_REG2_A 0x21
#define CTRL_REG3_A 0x22
#define CTRL_REG4_A 0x23
#define CTRL_REG5_A 0x24
#define CTRL_REG6_A 0x25
#define REFERENCE_A 0x26
#define STATUS_REG_A 0x27
#define OUT_X_L_A 0x28
#define OUT_X_H_A 0x29
#define OUT_Y_L_A 0x2A
#define OUT_Y_H_A 0x2B
#define OUT_Z_L_A 0x2C
#define OUT_Z_H_A 0x2D
#define FIFO_CTRL_REG_A 0x2E
#define FIFO_SRC_REG_A 0x2F
#define INT1_CFG_A 0x30
#define INT1_SRC_A 0x31
#define INT1_THS_A 0x32
#define INT1_DURATION_A 0x33
#define INT2_CFG_A 0x34
#define INT2_SRC_A 0x35
#define INT2_THS_A 0x36
#define INT2_DURATION_A 0x37
#define CLICK_CFG_A 0x38
#define CLICK_SRC_A 0x39
#define CLICK_THS_A 0x3A
#define TIME_LIMIT_A 0x3B
#define TIME_LATENCY_A 0x3C
#define TIME_WINDOW_A 0x3D

void LSM303DLHC_Init(void) {

    /* Set accelerometer to normal mode and 100 Hz data rate. */
    TWISetData(LSM303DLHC_ADDR, CTRL_REG1_A, 0x5F);
}

int LSM303DLHC_GetX(void) {
    uint16_t data;
    data = TWIGetData(LSM303DLHC_ADDR, OUT_X_H_A); // MSB
    data <<= 8;
    data |= TWIGetData(LSM303DLHC_ADDR, OUT_X_L_A); // LSB
    return data;
}

int LSM303DLHC_GetY(void) {
    uint16_t data;
    data = TWIGetData(LSM303DLHC_ADDR, OUT_Y_H_A); // MSB
    data <<= 8;
    data |= TWIGetData(LSM303DLHC_ADDR, OUT_Y_L_A); // LSB
    return data;
}

int LSM303DLHC_GetZ(void) {
    uint16_t data;
    data = TWIGetData(LSM303DLHC_ADDR, OUT_Z_H_A); // MSB
    data <<= 8;
    data |= TWIGetData(LSM303DLHC_ADDR, OUT_Z_L_A); // LSB
    return data;
}

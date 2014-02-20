#ifndef L3G4200D_H
#define L3G4200D_H

#include "TWIPrimitives.h"

/*
 * Degree per second value (DPS) depends on full scale (FS) value.
 * One digit is one mDPS.
 * Datasheet announces DPS as mDPS, convert to regular degrees.
 */
#define FS 250

#ifndef FS
  #error FS not defined.
#elif FS == 250
  #define DPS 1.0f/8.75f // milli DPS -> DPS
#elif FS == 500
  #define DPS 1.0f/17.5f // milli DPS -> DPS
#elif FS == 2000
  #define DPS 1.0f/70.0f // milli DPS -> DPS
#endif

void L3G4200D_Init(void);

uint8_t L3G4200D_GetTemp(void);
int L3G4200D_GetX(void);
int L3G4200D_GetY(void);
int L3G4200D_GetZ(void);

#endif

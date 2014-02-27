#ifndef L3G4200D_H
#define L3G4200D_H

#include "TWIPrimitives.h"

void L3G4200D_Init(void);

uint8_t L3G4200D_GetTemp(void);
int L3G4200D_GetX(void);
int L3G4200D_GetY(void);
int L3G4200D_GetZ(void);

#endif

#ifndef LSM303DLHC_H
#define LSM303DLHC_H

#include "TWIPrimitives.h"

void LSM303DLHC_Init(void);
int LSM303DLHC_GetX(void);
int LSM303DLHC_GetY(void);
int LSM303DLHC_GetZ(void);

#endif

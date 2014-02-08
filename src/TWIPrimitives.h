#ifndef TWIPRIMITIVES_H
#define TWIPRIMITIVES_H

#include <util/twi.h>

/* Primitive TWI communication functions, not part of the API. */
void TWIInit(void);
void TWIStart(void);
void TWIWrite(uint8_t data);
void TWIStop(void);
void TWIError(int errorCode);
uint8_t TWIReadACK(void);
uint8_t TWIReadNACK(void);

/* API functions. */
uint8_t TWIGetData(uint8_t addr, uint8_t mem);
void TWISetData(uint8_t addr, uint8_t mem, uint8_t value);

#endif

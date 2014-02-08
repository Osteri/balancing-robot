#include "TWIPrimitives.h"

/*
 * SCL frequency = CPU Clock frequency / (16 + 2 * TWBR * 4^(TWSR))
 *               = 16 000 000 / (16 + 2 * 18 * 4^1)
 *               = 100 kHz
 */
void TWIInit(void) {
    TWSR &= ~(1<<TWPS1 | 1<<TWPS0); // TWSR = 1
    TWBR = 18;
    TWCR |= (1<<TWEN); // Enable TWI
}

void TWIStart(void) {
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}

void TWIStop(void) {
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void TWIWrite(uint8_t data) { 
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
}

uint8_t TWIReadACK(void) {
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while (!(TWCR & (1<<TWINT)));
    return TWDR;
}

uint8_t TWIReadNACK(void) {
    TWCR = (1<<TWINT)|(1<<TWEN);
    while (!(TWCR & (1<<TWINT)));
    return TWDR;
}

void TWISetData(uint8_t addr, uint8_t mem, uint8_t value) {

    TWIStart();
    if (TW_STATUS != TW_START)
        TWIError(TW_STATUS);

    TWIWrite((uint8_t)(addr + TW_WRITE));
    if (TW_STATUS != TW_MT_SLA_ACK)
        TWIError(TW_STATUS);

    TWIWrite((uint8_t)(mem));
    if (TW_STATUS != TW_MT_DATA_ACK)
        TWIError(TW_STATUS);

    TWIWrite((uint8_t)(value));
    if (TW_STATUS != TW_MT_DATA_ACK)
        TWIError(TW_STATUS);

    TWIStop();
}

uint8_t TWIGetData(uint8_t addr, uint8_t mem) {

    uint8_t data;

    TWIStart();
    if (TW_STATUS != TW_START)
        TWIError(TW_STATUS);

    TWIWrite((uint8_t)(addr + TW_WRITE));
    if (TW_STATUS != TW_MT_SLA_ACK)
        TWIError(TW_STATUS);

    TWIWrite((uint8_t)(mem));
    if (TW_STATUS != TW_MT_DATA_ACK)
        TWIError(TW_STATUS);

    TWIStart();
    if (TW_STATUS != TW_REP_START)
        TWIError(TW_STATUS);

    TWIWrite((uint8_t)(addr + TW_READ));
    if (TW_STATUS != TW_MT_DATA_ACK)
        TWIError(TW_STATUS);

    data = TWIReadNACK();
    if (TW_STATUS != TW_MT_DATA_NACK)
        TWIError(TW_STATUS);

    TWIStop();

    return data;
}


void TWIError(int errorCode) {
    // Add your error routine here
}

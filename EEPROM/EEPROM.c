#include <STC12C5A60S2.H>
extern void I2CStart();
extern void I2CStop();
extern bit I2CWrite(unsigned char dat);
extern unsigned char I2CReadACK();
extern unsigned char I2CReadNACK();

void EEPROMWrite(unsigned char addr,unsigned char dat);
unsigned char EEPROMRead(unsigned char addr);

void EEPROMWrite(unsigned char addr,unsigned char dat)
{
    I2CStart();
    I2CWrite(0x50<<1);
    I2CWrite(addr);
    I2CWrite(dat);
    I2CStop();
}

unsigned char EEPROMRead(unsigned char addr)
{
    unsigned char dat;
    I2CStart();
    I2CWrite(0x50<<1);
    I2CWrite(addr);
    I2CStart();
    I2CWrite((0x50<<1)|0x01);
    dat = I2CReadNACK();
    I2CStop();
    return dat;
}
#include <STC12C5A60S2.H>
#include <intrins.h>
sbit I2C_SCL = P1^0;
sbit I2C_SDA = P1^1;

void I2CStart();
void I2CStop();
void I2CDelay();
bit I2CWrite(unsigned char dat);
unsigned char I2CReadACK();
unsigned char I2CReadNACK();

void I2CDelay()
{
    _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
}
void I2CStart()         //Send starting timing
{
    I2C_SCL = 1;
    I2C_SDA = 1;
    I2CDelay();
    I2C_SDA = 0;
    I2CDelay();
    I2C_SCL = 0;
}   
void I2CStop()          //Send stop timing
{
    I2C_SCL = 0;
    I2C_SDA = 0;
    I2CDelay();
    I2C_SCL = 1;
    I2CDelay();
    I2C_SDA = 1;
}
bit I2CWrite(unsigned char dat)     //Send data timing
{
    bit ack;
    unsigned char mask;
    for(mask=0x80;mask!=0x00;mask>>=1)      //Bitwise value
    {
        I2C_SDA = (mask&dat);
        I2CDelay();
        I2C_SCL = 1;
        I2CDelay();
        I2C_SCL = 0;
    }
    I2C_SDA = 1;
    I2CDelay();
    I2C_SCL = 1;
    ack = I2C_SDA;                  //Read return signal
    I2CDelay();
    I2C_SCL = 0;
    
    return ~ack;
}
unsigned char I2CReadNACK()         //Sent read data timing with stop signal
{
    unsigned char dat;
    unsigned char mask;
    I2C_SDA = 1;
    for(mask=0x80;mask!=0x00;mask>>=1)      //Bitwise value
    {
        I2CDelay();
        I2C_SCL = 1;
        if(I2C_SDA == 0)
            dat &= ~mask;
        else
            dat |= mask;
        I2CDelay();
        I2C_SCL = 0;
    }
    I2C_SDA = 1;                    //Sent stop signal
    I2CDelay();
    I2C_SCL = 1;
    I2CDelay();
    I2C_SCL = 0;
    
    return dat;
}
unsigned char I2CReadACK()      //Sent read data timing with continue signal
{
    unsigned char dat;
    unsigned char mask;
    I2C_SDA = 1;
    for(mask=0x80;mask!=0x00;mask>>=1)  //Bitwise value
    {
        I2CDelay();
        I2C_SCL = 1;
        if(I2C_SDA == 0)    
            dat &= ~mask;
        else
            dat |= mask;
        I2CDelay();
        I2C_SCL = 0;                
    }
    I2C_SDA = 0;                 //Sent continue signal
    I2CDelay();
    I2C_SCL = 1;
    I2CDelay();
    I2C_SCL = 0;
    
    return dat;
}
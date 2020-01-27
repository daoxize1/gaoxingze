#include <STC12C5A60S2.H>
#include <intrins.h>
sbit I2C_SCL = P1^0;
sbit I2C_SDA = P1^1;

void I2Cdelay();
void I2CStart();
void I2CStop();
bit I2CWrite(unsigned char dat);
bit I2CAddressing(unsigned char addr);

void I2Cdelay()
{
	int i;
    i = 37;
    while(--i);
    
}
void I2CStart()
{
	I2C_SDA = 1;
	I2C_SCL = 1;
	I2Cdelay();
	I2C_SDA = 0;
	I2Cdelay();
	I2C_SCL = 0;
}
void I2CStop()
{
	I2C_SDA = 0;
	I2C_SCL = 0;
	I2Cdelay();
	I2C_SCL = 1;
	I2Cdelay();
	I2C_SDA = 1;
}
bit I2CWrite(unsigned char dat)
{
	bit ack;
	unsigned char mask;
	for(mask = 0x80;mask!=0x00;mask>>=1)
	{
		if((mask&dat)==0)
			I2C_SDA = 0;
		else
			I2C_SDA = 1;
		I2Cdelay();
		I2C_SCL = 1;
		I2Cdelay();
		I2C_SCL = 0;
	}
	I2C_SDA = 1;
	I2Cdelay();
	I2C_SCL = 1;
	ack = I2C_SDA;
	I2Cdelay();
	I2C_SCL = 0;
	
	return ack;
}
bit I2CAddressing(unsigned char addr)
{
	bit ack;
	I2CStart();
	ack = I2CWrite(addr<<1);
	I2CStop();
	return ack;
}
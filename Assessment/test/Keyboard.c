#include <STC12C5A60S2.H>
sbit B1 = P3^4;
sbit B2 = P3^5;
sbit B3 = P3^6;
sbit B4 = P3^7;
extern char Interface;
extern unsigned char Alarm[3];
unsigned char times = 0;
void Setting()
{
	
}

void EXTInterrupt0() interrupt 0
{
	if(B1 == 0)
	{
		Interface = 'B';
	}
	if(B2 == 0)
	{
		times++;
		//if(times == 6)
	}
}
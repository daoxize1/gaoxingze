#include <STC12C5A60S2.H>
sbit IR_INPUT = P3^2;
bit irflag=0;
unsigned char ircode[4];
	
unsigned int GetHighTime();
unsigned int GetLowTime();
void IrInit();

void IrInit()
{
	IR_INPUT = 1;
	TMOD &= 0XF0;
	TMOD |= 0X01;
	TR0 = 0;
	ET0 = 0;
	EX0 = 1;
	IT0 = 1;
}
unsigned int GetHighTime()
{
	unsigned int time;
	TH0 = 0;
	TL0 = 0;
	TR0 = 1;
	while(IR_INPUT == 1)
	{
		if(TH0 > 0XC2)
			break;
	}
	TR0 = 0;
	time = TH0 * 256 + TL0;
	
	return time;
}
unsigned int GetLowTime()
{
	unsigned int time;
	TH0 = 0;
	TL0 = 0;
	TR0 = 1;
	while(IR_INPUT == 0)
	{
		if(TH0 > 0XC2)
			break;
	}
	TR0 = 0;
	time = TH0 * 256 + TL0;
	
	return time;
}

void EXTInterrupt0() interrupt 0
{
	unsigned char i,j;
	unsigned char byt;
	unsigned int time;
	
	time = GetLowTime();
	if((time<22666) || (time>25333))
	{
		IE0 = 0;
		return;
	}
	time = GetHighTime();
	if((time<10666) || (time>13333))
	{
		IE0 = 0;
		return;
	}
	
	for(i=0;i<4;i++)
	{
		for(j=0;j<8;j++)
		{
			time = GetLowTime();
			if((time<906) || (time>2080))
			{
				IE0 = 0;
				return;
			}
			time = GetHighTime();
			if((time>906)&&(time<2080))
			{
				byt >>= 1;
			}
			else if((time>3893)&&(time<5066))
			{
				byt >>= 1;
				byt |= 0x80;
			}
			else
			{
				IE0 = 0;
				return;
			}
		}
		ircode[i] = byt;
	}
	irflag = 1;
	IE0 = 0;
}
#include <STC12C5A60S2.H>
sbit AddrA = P1^0;
sbit AddrB = P1^1;
sbit AddrC = P1^2;
extern unsigned char ircode[4];
unsigned char ledchar[]={	
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0X76};
int i = 0;
void Timer1Init() 			//1ms + Open Timer1 Interrupt
{
	AUXR |= 0x40;			
	TMOD &= 0x0F;		
	TMOD |= 0x10;		
	TL1 = 0x00;		
	TH1 = 0x83;		
	TF1 = 0;		
	TR1 = 1;		
	ET1 = 1;
}

void LEDScan()				//Digital tube refresh
{
	P0 = 0X00;
	switch(i)
	{
		case 0:AddrC=0;AddrB=0;AddrA=0;P0=ledchar[ircode[0]>>4];break;
		case 1:AddrC=0;AddrB=0;AddrA=1;P0=ledchar[ircode[0]&0X0F];break;
		case 2:AddrC=1;AddrB=1;AddrA=0;P0=ledchar[ircode[2]>>4];break;
		case 3:AddrC=1;AddrB=1;AddrA=1;P0=ledchar[ircode[2]&0X0F];break;
		default:break;
	}
}

void Timer1Interrupt() interrupt 3 //Digital tube refresh
{
	TL1 = 0x00;
	TH1 = 0x83;		
	TF1 = 0;
	LEDScan();
	i++;
	if(i == 4)
	{
		i = 0;
	}
	
}
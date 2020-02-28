#include <STC12C5A60S2.H>

extern void IrInit();
extern void Timer1Init();
extern unsigned char ircode[4];
extern bit irflag;
void main()
{
	EA = 1;			
	IrInit();			
	Timer1Init();		
	while(1);
	
}
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
	ircode[0]=0;
	ircode[1]=2;
	ircode[2]=3;
	ircode[3]=4;
	while(1)
	{
		if(irflag == 1)
		{
			irflag = 0;
			
		}
	}
}
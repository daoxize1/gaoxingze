#include <STC12C5A60S2.H>
sbit buzz = P1^7;
bit BuzzerOn = 0;
extern void delay(int i);
void RingOn()
{
	BuzzerOn = 1;
	while(1)
	{
		buzz = ~buzz;
		delay(500);			//¿ØÖÆÉùµ÷
		if(BuzzerOn = 0)
			break;
	}
}
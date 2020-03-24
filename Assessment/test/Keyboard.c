#include <STC12C5A60S2.H>
/*times = 1 --> hour
  times = 2 --> minute
  times = 3 --> second
  times = 4 --> Vmax
  times = 5 --> Vmin */

sbit B1 = P3^4;
sbit B2 = P3^5;
sbit B3 = P3^6;
sbit B4 = P3^7;
extern char Interface;
extern char Alarm[3];
extern bit BuzzerOn;
unsigned char times = 0;
void delay(int i)
{
	while(--i);
}
void KeyScan()
{
	if(B1 == 0 && Interface == 'A')
	{
		Interface = 'B';
		while(B1 == 0);
		delay(100000);
	}
	
	if(B1 == 0 && Interface == 'B')
	{
		Interface = 'A';
		while(B1 == 0);
		delay(100000);
	}
	
	if(B2 == 0 && Interface == 'B')
	{
		times++;
		if(times == 4)
			times = 0;
		while(B2 == 0);
		delay(100000);
	}
	
	if(B3 == 0 && Interface == 'B')
	{
		switch(times)
		{
			case 1:Alarm[0]++;if(Alarm[0] == 25) Alarm[0] = 0;break;
			case 2:Alarm[1]++;if(Alarm[1] == 60) Alarm[1] = 0;break;
			case 3:Alarm[2]++;if(Alarm[2] == 60) Alarm[2] = 0;break;
			default:break;
		}
		while(B3 == 0);
		delay(100000);
	}
	
	if(B4 == 0 && BuzzerOn == 1)
	{
		BuzzerOn = 0;
	}
}


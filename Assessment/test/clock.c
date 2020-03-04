#include <STC12C5A60S2.H>

unsigned char Time[3]={23,59,29};
unsigned int i = 0;
void ClockInit()//10ms@32MHz
{		
	TMOD &= 0xF0;		
	TMOD |= 0x01;		
	TL0 = 0xD5;		
	TH0 = 0x97;		
	TF0 = 0;		
	TR0 = 1;		
	ET0 = 1;
}

void Timer0Interrupt() interrupt 1
{
	i++;
	if(i == 100)
	{
		Time[2]++;
		i = 0;
		if(Time[2] == 60)
		{
			Time[1]++;
			Time[2] = 0;
			if(Time[1] = 60)
			{
				Time[0]++;
				Time[1] = 0;
				if(Time[0] == 24)
				{
					Time[0] = 0;
				}
			}
		}
	}
}
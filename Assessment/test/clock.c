#include <STC12C5A60S2.H>
extern char Interface;
unsigned char Time[3]={23,59,29};
unsigned char Alarm[3]={00,01,00};
char TimeDisplay[8];
unsigned int i = 0;
extern void LCDShowStr(unsigned char x,unsigned char y,char *str);

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

void CharToString(unsigned char Array);
{
	TimeDisplay[0] = Array[0]/10+'0';
	TimeDisplay[1] = Array[0]%10+'0';
	TimeDisplay[2] = '-';
	TimeDisplay[3] = Array[0]/10+'0';
	TimeDisplay[4] = Array[0]%10+'0';
	TimeDisplay[5] = '-';
	TimeDisplay[6] = Array[0]/10+'0';
	TimeDisplay[7] = Array[0]%10+'0';
}

void DisplayInterfaceA()
{
	LCDShowStr(0,0,"A");
	CharToString(Time);
	LCDShowStr(0,2,TimeDisplay);
}


void DisplayInterfaceB()
{
	LCDShowStr(0,0,"B");
	CharToString(Alarm);
	LCDShowStr(0,2,TimeDisplay);
}


void Timer0Interrupt() interrupt 1
{
	i++;
	TL0 = 0xD5;
	TH0 = 0x97;	
	TR0 = 1;
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
	if(i == 10&&Interface == 'A')
	{
		DisplayInterfaceA();
	}
	if(i == 10&&Interface == 'B')
	{
		DisplayInterfaceB();
	}
}
#include <STC12C5A60S2.H>
extern char Interface;
char Time[3]={23,59,29};
char Alarm[3]={23,59,40};
char TimeDisplay[9]={0};
unsigned int i = 0;
extern bit BuzzerOn;
extern void LCDShowStr(unsigned char x,unsigned char y,char *str);
extern void LCDWriteCmd(unsigned char cmd);
extern void RingOn();
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

void CharToString(char Arra[])
{
	TimeDisplay[0] = Arra[0]/10+'0';
	TimeDisplay[1] = Arra[0]%10+'0';
	TimeDisplay[2] = '-';
	TimeDisplay[3] = Arra[1]/10+'0';
	TimeDisplay[4] = Arra[1]%10+'0';
	TimeDisplay[5] = '-';
	TimeDisplay[6] = Arra[2]/10+'0';
	TimeDisplay[7] = Arra[2]%10+'0';
	TimeDisplay[8] = '\0';
}

void DisplayInterfaceA()
{
	LCDWriteCmd(0x01); 
	LCDShowStr(0,0,"A");
	CharToString(Time);
	LCDShowStr(0,1,TimeDisplay);
}


void DisplayInterfaceB()
{
	LCDWriteCmd(0x01); 
	LCDShowStr(0,0,"B");
	CharToString(Alarm);
	LCDShowStr(0,1,TimeDisplay);
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
	if(Time[0]==Alarm[0] && Time[1]==Alarm[1]&&Time[2]==Alarm[2])
	{
		BuzzerOn = 1;
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
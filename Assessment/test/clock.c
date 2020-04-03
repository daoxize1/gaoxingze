#include <STC12C5A60S2.H>
char Time[3]={23,59,29};
char Alarm[3]={00,01,00};
char TimeDisplay[9]={0};
char xdata UartString[17]={0};
unsigned int i = 0;

extern char Interface;
extern bit BuzzerOn;
extern bit overlimit;
extern bit flag;
extern unsigned int Volt;
extern unsigned char VH;
extern unsigned char VL;
extern char xdata VoltString[6];

extern void LCDShowStr(unsigned char x,unsigned char y,char *str);
extern void LCDShowChar(unsigned char x,unsigned char y,char ch);
extern void LCDWriteCmd(unsigned char cmd);
extern void RingOn();
extern void VoltToString(unsigned int Volt);
extern void UartSentString(char *str);

void ClockInit();
void CharToString(char Arra[]);
void DisplayInterfaceA();
void DisplayInterfaceB();
void DataToUartString();


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

void CharToString(char Arra[])			//将时间变为字符串来显示
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

void DisplayInterfaceA()				//显示界面A
{
	LCDWriteCmd(0x01); 
	LCDShowStr(0,0,"A");
	CharToString(Time);
	LCDShowStr(4,0,TimeDisplay);
	
	VoltToString(Volt);
	LCDShowStr(0,1,"V1:");
	LCDShowStr(3,1,VoltString);
}


void DisplayInterfaceB()				//显示界面B
{
	LCDWriteCmd(0x01); 
	LCDShowStr(0,0,"B");
	CharToString(Alarm);
	LCDShowStr(4,0,TimeDisplay);
	
	LCDShowStr(0,1,"VH:");
	LCDShowChar(3,1,VH+'0');
	LCDShowStr(8,1,"VL:");
	LCDShowChar(11,1,VL+'0');
}

void DataToUartString()					//将上报电压的数据转换为字符串来上报
{
	unsigned char i;
	for(i=0; i<4; i++)
	{
		UartString[i] = VoltString[i];
	}
	
	UartString[4] = '+';
	UartString[5] = Time[0]/10 + '0';
	UartString[6] = Time[0]%10 + '0';	
	UartString[7] = Time[1]/10 + '0';
	UartString[8] = Time[1]%10 + '0';
	UartString[9] = Time[2]/10 + '0';
	UartString[10] = Time[2]%10 + '0';
	UartString[11] = '\r';
	UartString[12] = '\n';
	UartString[13] = '\0';
}

void Timer0Interrupt() interrupt 1
{
	i++;
	TL0 = 0xD5;
	TH0 = 0x97;	
	TR0 = 1;
	if(i == 100)							//时钟 进位
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
	if(Time[0]==Alarm[0] && Time[1]==Alarm[1]&&Time[2]==Alarm[2]) //闹铃时间到
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
	if(i == 95 && overlimit == 1 && flag == 1)		//超限上报
	{
		DataToUartString();
		TI = 0;
		UartSentString(UartString);
	}
	
}
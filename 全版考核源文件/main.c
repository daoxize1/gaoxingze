#include <STC12C5A60S2.H>
sbit buzz = P1^7;
sbit OverLimitLED = P3^0;
extern bit flag;				//密码正确的标志
bit BuzzerOn;
extern void UartInit();
extern void LCDInit();
extern void ClockInit();
extern void UartSentString(char *str);
extern void LCDShowStr(unsigned char x,unsigned char y,char *str);
extern void KeyScan();
extern void delay(int i);
extern void Timer1Init();
extern unsigned int Volt;
extern unsigned char VH;
extern unsigned char VL;
extern bit overlimit;
char Interface;


void main()
{
	UartInit();
	LCDInit();
	ClockInit();
	Timer1Init();
	EA = 1;						//打开总中断
	TI = 0;						//串口发送
	IT0 = 1;
	EX0 = 1;
	LCDShowStr(0,0,"Waiting...");
	UartSentString("Please input password!\r\n");
	while(1)					//等待正确输入密码
	{
		if(flag == 1)
			break;
	}
	Interface = 'A';			//进入A界面
	while(1)					//扫描按键
	{
		KeyScan();
		if(BuzzerOn == 1)
		{
			buzz = ~buzz;		//我的蜂鸣器必须以这种方式发声
		}
		delay(300);
		if((Volt/1000)>VH || (Volt/1000)<VL)
		{
			overlimit = 1;
			OverLimitLED = 0;
		}
		else
		{
			overlimit = 0;
			OverLimitLED = 1;
		}
	}
	while(1);
}


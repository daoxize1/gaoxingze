#include <STC12C5A60S2.H>
char Output[40]={"Please input password!"};
char Input[30];
char Password[6]={1,2,3,4,5,6};
unsigned char step = 0;
void UartInit(void)		//9600bps@32MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//独立波特率发生器时钟为Fosc,即1T
	BRT = 0x30;		//设定独立波特率发生器重装值
	AUXR |= 0x01;		//串口1选择独立波特率发生器为波特率发生器
	AUXR |= 0x10;		//启动独立波特率发生器
	ES = 1;
}

void UartInterrupt() interrupt 4
{
	unsigned char i = 0;
	unsigned char RecDat;
	if(step == 0)
	{
		do
		{
			SBUF = Output[i];
			while(!TI);
			TI = 0;
			i++;
		}while(Output[i]!='\0');
		SBUF = '\n';
		while(!TI);
		TI = 0;
		
		i = 0;
		step++;
	}
	if(step == 1)
	{
		do
		{
			Input[i] = SBUF;
			RI = 0;
			i++;
		}while(SBUF!='\0');
		Input[i] = '\0';
		i = 0;
		step++;
	}
	if(step == 2)
	{
		do
		{
			SBUF = Input[i];
			while(!TI);
			TI = 0;
			i++;
		}while(Input[i]!='\0');
		i = 0;
	}
}
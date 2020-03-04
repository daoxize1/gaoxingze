#include <STC12C5A60S2.H>
char Output[40]={"Please input password!"};
char Input[30];
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
	TI = 0;
	do
	{
		SBUF = Output[i];
		while(!TI);
		TI = 0;
		i++;
	}while(Output[i]!='\0');
	Input[0] = SBUF;
	RI = 0;

}
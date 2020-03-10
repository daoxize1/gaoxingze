#include <STC12C5A60S2.H>
#include <string.h>
char Output[40]={"Please input password!"};
char Input[30];
char Password[6]={1,2,3,4,5,6};
unsigned char step = 0;
bit flag = 0;
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

void UartRecString(char Input[])
{
	unsigned char length = 0;
	unsigned int TimeOut = 1000;
	while(TimeOut--)
	{
		if(RI != 0)
		{
			RI = 0;
			Input[length] = SBUF;
			length++;
		}
	}
	Input[length] = '\0';
}
void UartSentString(char *str)
{
	while(*str!='\0')
	{
		SBUF = *str++;
		while(!TI);
		TI = 0;
	}
}
void UartInterrupt() interrupt 4
{
	unsigned char i = 0;
	UartRecString(Input);
	if(strcmp("123456\r\n",Input)==1)
	{
		UartSentString("Welcome to you!\r\n");
		flag = 1;
	}
	else 
	{
		UartSentString("The password is error! Please input again!\r\n");
	}
}
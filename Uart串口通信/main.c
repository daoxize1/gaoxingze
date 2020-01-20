//波特率9600 16进制发送 发什么数字LCD上显示什么数字 （目前还不会接收字符串）
#include <STC12C5A60S2.H>
#include <string.h>
int i = 0;
extern void LCDInit();
extern void ShowStr(unsigned char x,unsigned char y,char *str);
void UartInit();
void main()
{
    UartInit();
    LCDInit();
    while(1);
}

//这里用了STC-ISP的破特率计算器，没自己算
void UartInit(void)		//9600bps@12.000MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//独立波特率发生器时钟为Fosc,即1T
	BRT = 0xB2;		//设定独立波特率发生器重装值
	AUXR |= 0x01;		//串口1选择独立波特率发生器为波特率发生器
	AUXR |= 0x10;		//启动独立波特率发生器
    ES = 1;
    EA = 1;
}


void UartInterrupt() interrupt 4
{
    char str[20];
    /*do
    {
        str[i] = SBUF;
        i++;
    }while(SBUF!="\0");
    RI = 0;
    i = 0;*/
    str[0] = SBUF + '0';
    RI = 0;
    str[1] = '\0';
    ShowStr(0,0,str);
    SBUF = 1;
    while(!TI);
    TI = 0;
}
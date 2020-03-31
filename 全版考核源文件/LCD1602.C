#include <STC12C5A60S2.H>
#include <intrins.h>
#define LCD_DB P0
sbit LCD_EN = P2^7;
sbit LCD_RS = P2^6;
sbit LCD_WR = P2^5;
extern unsigned int Volt;

char xdata VoltString[6]={0};

void LCDInit();
void LCDWaitReady();
void LCDWriteDat(unsigned char dat);
void LCDWriteCmd(unsigned char cmd);
void LCDSetCursor(unsigned char x,unsigned char y);
void LCDShowStr(unsigned char x,unsigned char y,char *str);
void LCDShowChar(unsigned char x,unsigned char y,char ch);

void LCDDelay();
void VoltToString(unsigned int Volt);


void LCDDelay()
{
	_nop_();_nop_();_nop_();_nop_(); _nop_();_nop_();_nop_();_nop_();
}

void LCDInit()
{
	LCDWriteCmd(0x38);
	LCDWriteCmd(0x0c);
	LCDWriteCmd(0x06);
	LCDWriteCmd(0x01);
}

void LCDWaitReady()
{
	unsigned char sta;
	LCD_DB = 0xff;
	LCD_RS = 0;
	LCD_WR = 1;
	do
	{
		LCD_EN = 1;
		sta = LCD_DB;
		LCDDelay();
		LCD_EN = 0;
	}while(sta & 0x80);
}

void LCDWriteCmd(unsigned char cmd)
{
	LCDWaitReady();
	LCD_RS = 0;
	LCD_WR = 0;
	LCD_DB = cmd;
	LCDDelay();
	LCD_EN = 1;
	LCD_EN = 0;
}

void LCDWriteDat(unsigned char dat)
{
	LCDWaitReady();
	LCD_RS = 1;
	LCD_WR = 0;
	LCD_DB = dat;
	LCDDelay();
	LCD_EN = 1;
	LCD_EN = 0;
}

void LCDSetCursor(unsigned char x,unsigned char y)
{
	unsigned char addr;
	if(y == 0)
		addr = 0x00 + x;
	else
		addr = 0x40 + x;
	LCDWriteCmd(addr | 0x80);
}

void LCDShowStr(unsigned char x,unsigned char y,char *str)
{
	LCDSetCursor(x,y);
	while(*str!='\0')
	{
		LCDWriteDat(*str++);
	}
}

void LCDShowChar(unsigned char x,unsigned char y,char ch)
{
	LCDSetCursor(x,y);
	LCDWriteDat(ch);
}

void VoltToString(unsigned int Volt)
{
	unsigned char i = 0;
	VoltString[0] = Volt/1000 + '0';
	VoltString[1] = '.';
	VoltString[2] = Volt%1000/100 + '0';
	VoltString[3] = Volt%100/10 + '0';
	VoltString[4] = '\0';
}
#include <STC12C5A60S2.H>
#include <intrins.h>
#define LCD_DB P0
sbit LCD_EN = P2^7;
sbit LCD_RS = P2^6;
sbit LCD_WR = P2^5;
void LCDInit();
void LCDWriteCmd(unsigned char cmd);
void LCDWriteDat(unsigned char dat);
void LCDWaitReady();
void LCDSetCursor(unsigned char x,unsigned char y);
void LCDShowStr(unsigned char x,unsigned char y,char *str);
void LCDShowChar(unsigned char x,unsigned char y,char a);
void LCDDelay();        //Too fast will cause LCD to fail to display,so it needs delay

void LCDDelay()
{
    unsigned char i;
    i = 38;
    while(i--);
}
void LCDInit()          //LCD1602 initialization
{
    LCDWriteCmd(0x38);
    LCDWriteCmd(0x0c);
    LCDWriteCmd(0x06);
    LCDWriteCmd(0x01);
}
void LCDWaitReady()
{
    unsigned char sta;      //Indicates the current status of the LCD(busy or free)
    LCD_DB = 0xff;
    LCD_RS = 0;
    LCD_WR = 1;
    do
    {
        LCD_EN = 1;
        sta = LCD_DB;
        LCD_EN = 0;
    }while(sta & 0x80);     //if (sta & 0x80) = 0,lcd is free,so continue

}
void LCDWriteCmd(unsigned char cmd)
{
    LCDWaitReady();     //Waiting for the LCD to be free
    LCD_RS = 0;
    LCD_WR = 0;
    LCD_DB = cmd;
    LCDDelay();
    LCD_EN = 1;
    LCD_EN = 0;
}
void LCDWriteDat(unsigned char dat)
{
    LCDWaitReady();     //Waiting for the LCD to be free
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
        addr = x + 0x00;    //0x00 is first row
    else
        addr = x + 0x40;    //0x40 is second row
    LCDWriteCmd(addr | 0x80);
}
void LCDShowStr(unsigned char x,unsigned char y,char *str)      //Display string
{
    LCDSetCursor(x,y);
    while(*str!='\0')   //Show each char of the string
	{
		LCDWriteDat(*str++);
	}
}
void LCDShowChar(unsigned char x,unsigned char y,char a)        //Display char
{
    LCDSetCursor(x,y);
    LCDWriteDat(a);
}
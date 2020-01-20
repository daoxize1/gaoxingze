//滚动显示“Hello world!”
#include <STC12C5A60S2.H>
#define LCD_DB P0
sbit LCD_EN = P2^7;
sbit LCD_RS = P2^6;
sbit LCD_WR = P2^5;

void LCDInit();
void LCDWaitReady();
void LCDWriteCmd(unsigned char cmd);
void LCDWriteDat(unsigned char dat);
void SetCursor(unsigned char x,unsigned char y);
void ShowStr(unsigned char x,unsigned char y,char *str);
void delay(int i);
void main()
{
    int i;
    LCDInit();
    while(1)
    {
        for(i = 1;i <= 16;i++)
        {
            LCDWriteCmd(0x01);
            ShowStr(16-i,0,"Hello World!");
            delay(20000);
        }
    }
    while(1);
}
void delay(int i)
{
    int a;
    for(a = 0;a < 5;a++)
    {
        while(i--);
    }
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
    LCD_RS = 0;
    LCD_WR = 1;
    LCD_DB = 0xff;
    do
    {
        LCD_EN = 1;
        sta = LCD_DB;
        LCD_EN = 0;
    }while(sta & 0x80);
}

void LCDWriteCmd(unsigned char cmd)
{
    LCDWaitReady();
    LCD_RS = 0;
    LCD_WR = 0;
    LCD_DB = cmd;
    LCD_EN = 1;
    LCD_EN = 0;
}
void LCDWriteDat(unsigned char dat)
{
    LCDWaitReady();
    LCD_RS = 1;
    LCD_WR = 0;
    LCD_DB = dat;
    LCD_EN = 1;
    LCD_EN = 0;
}

void SetCursor(unsigned char x,unsigned char y)
{
    unsigned char addr;
    if(y == 0)
        addr = 0x00 + x;
    else
        addr = 0x40 + x;
    LCDWriteCmd(addr | 0x80);
}
  
void ShowStr(unsigned char x,unsigned char y,char *str)
{
    SetCursor(x,y);
    while(*str!='\0')
    {
        LCDWriteDat(*str++);
    }
}

//LCD1602的刷新率太低，滚动显示效果不理想，还是静态显示好
#include <STC12C5A60S2.H>
#define LCD_DB P0           //Set up LCD1602 slot
sbit LCD_EN = P2^7;
sbit LCD_RS = P2^6;
sbit LCD_WR = P2^5;

void LCDInit();
void LCDWaitReady();
void LCDWriteCmd(unsigned char cmd);
void LCDWriteDat(unsigned char dat);
void SetCursor(unsigned char x,unsigned char y);
void ShowStr(unsigned char x,unsigned char y,char *str);
void delay(int i);      //Too fast will cause LCD to fail to display,so it needs delay

void LCDInit()          //LCD1602 initialization
{
    LCDWriteCmd(0x38);
    LCDWriteCmd(0x0c);
    LCDWriteCmd(0x06);
    LCDWriteCmd(0x01);
}

void LCDWaitReady()     
{
    unsigned char sta;  //Indicates the current status of the LCD(busy or free)
    LCD_RS = 0;
    LCD_WR = 1;
    LCD_DB = 0xff;
    do
    {
        LCD_EN = 1;
        sta = LCD_DB;
        LCD_EN = 0;
    }while(sta & 0x80);//if (sta & 0x80) = 0,lcd is free,so continue
}

void LCDWriteCmd(unsigned char cmd)
{
    LCDWaitReady();     //Waiting for the LCD to be free
    LCD_RS = 0;
    LCD_WR = 0;
    LCD_DB = cmd;
    LCD_EN = 1;
    LCD_EN = 0;
}
void LCDWriteDat(unsigned char dat)
{
    LCDWaitReady();     //Waiting for the LCD to be free
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
        addr = 0x00 + x;    //0x00 is first row
    else
        addr = 0x40 + x;    //0x40 is second row
    LCDWriteCmd(addr | 0x80);
}
  
void ShowStr(unsigned char x,unsigned char y,char *str)
{
    SetCursor(x,y);
    while(*str!='\0')       //Show each char of the string
    {
        LCDWriteDat(*str++);
    }
}

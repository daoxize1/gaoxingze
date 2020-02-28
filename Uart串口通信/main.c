//Baud rate 9600 and hex send
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


void UartInit(void)		//9600bps@32MHz
{
	PCON &= 0x7F;		
	SCON = 0x50;		
	AUXR |= 0x04;		
	BRT = 0x98;		   
	AUXR |= 0x01;		
	AUXR |= 0x10;		
    ES = 1;             //Open Usart Interrupt and master Interrupt
    EA = 1;
}


void UartInterrupt() interrupt 4
{
    char str[20];
    str[0] = SBUF + '0';
    RI = 0;
    str[1] = '\0';
    ShowStr(0,0,str);   //Show received char
    SBUF = 1;
    while(!TI);         //Wait sending
    TI = 0;
}
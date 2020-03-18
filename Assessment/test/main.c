#include <STC12C5A60S2.H>
extern bit flag;
extern void UartInit();
extern void LCDInit();
extern void ClockInit();
extern void UartSentString(char *str);
extern void LCDShowStr(unsigned char x,unsigned char y,char *str);
char Interface;
void main()
{
	UartInit();
	LCDInit();
	ClockInit();
	EA = 1;
	TI = 0;
	EX0 = 0;
	IT0 = 1;
	LCDShowStr(0,0,"Waiting...");
	UartSentString("Please input password!\r\n");
	while(1)
	{
		if(flag == 1)
			break;
	}
	Interface = 'A';
	while(1);
}


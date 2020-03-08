#include <STC12C5A60S2.H>
extern void UartInit();
void main()
{
	UartInit();
	EA = 1;
	TI = 0;
	while(1);
}
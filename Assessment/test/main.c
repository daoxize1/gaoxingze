#include <STC12C5A60S2.H>
extern void UartInit();
void main()
{
	UartInit();
	EA = 1;
	while(1);
}
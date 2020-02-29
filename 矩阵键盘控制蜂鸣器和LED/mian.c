#include <STC12C5A60S2.H>
#define Keyboard P0
#define LED P1
sbit Buzzer = P2^0;
unsigned char KeyValue[16]={
	0x88,0x84,0x82,0x81,
	0x48,0x44,0x42,0x41,
	0x28,0x24,0x22,0x21,
	0x18,0x14,0x12,0x11}; 	//Keyborad Value
void main()
{
	unsigned char i;
	while(1)
	{
		//The first two rows of buttons turn on the buzzer and LED
		for(i=0;i<8;i++)	
		{
			if(Keyboard = KeyValue[i])
			{
				Buzzer = 0;
				LED = 0;
			}
		}
		//The last two rows of buttons turn off the buzzer and LED
		for(i=8;i<16;i++)
		{
			if(Keyboard = KeyValue[i])
			{
				Buzzer = 1;
				LED = 1;
			}
		}
	}
}
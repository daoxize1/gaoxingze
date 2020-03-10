#include <STC12C5A60S2.H>
sbit AddrA = P2^2;
sbit AddrB = P2^3;
sbit AddrC = P2^4;
unsigned char j = 0;
unsigned char code LedChar[]={
	0x3f,0x06,0x5b,0x4f,
    0x66,0x6d,0x7d,0x07,
    0x7f,0x6f,0x77,0x7c,
    0x39,0x5e,0x79,0x71
	};

void Timer1Init(void)		//2����@32MHz
{
	AUXR &= 0xBF;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x10;		//���ö�ʱ��ģʽ
	TL1 = 0x2B;		//���ö�ʱ��ֵ
	TH1 = 0xEB;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
	ET1 = 1;
}
	
void interruptLED() interrupt 3
{
	TL1 = 0x2B;
	TH1 = 0xEB;
	TR1 = 1;
    P0 = 0x00;
    switch(j)
    {
        case 0:AddrA = 1;AddrB = 1;AddrC = 1;P0 = LedChar[0];j++;break;
        case 1:AddrA = 0;AddrB = 1;AddrC = 1;P0 = LedChar[0];j++;break;
        case 2:AddrA = 1;AddrB = 0;AddrC = 1;P0 = LedChar[0];j++;break;
        case 3:AddrA = 0;AddrB = 0;AddrC = 1;P0 = LedChar[0];j++;break;
        case 4:AddrA = 1;AddrB = 1;AddrC = 0;P0 = LedChar[0];j++;break;
        case 5:AddrA = 0;AddrB = 1;AddrC = 0;P0 = LedChar[0];j++;break;
        case 6:AddrA = 1;AddrB = 0;AddrC = 0;P0 = LedChar[0];j++;break;
        case 7:AddrA = 0;AddrB = 0;AddrC = 0;P0 = LedChar[0];j=0;break;
        default:break;
    }
}
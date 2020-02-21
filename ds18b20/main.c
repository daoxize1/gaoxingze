#include <STC12C5A60S2.H>
bit flag1s = 0;

void Timer0Init();
unsigned char IntToString(unsigned char *str,int dat);
extern bit StartDS18B20();
extern bit GetDS18B20Temp(int *temp);
extern void LCDInit();
extern void LCDShowStr(unsigned char x,unsigned char y,char *str);

int i = 0;

void main()
{
	bit res;
	int temp;
	int intT,decT;
	unsigned char len;
	unsigned char str[12];
	EA = 1;
	Timer0Init();
	StartDS18B20();
	LCDInit();
	while(1)
	{
		if(flag1s)
		{
			flag1s = 0;
			res = GetDS18B20Temp(&temp);
			if(res)
			{
				intT = temp >> 4;
				decT = temp & 0xf;
				len = IntToString(str,intT);
				str[len++] = '.';
				decT = (decT*10) / 16;
				str[len++] = decT + '0';
				while(len < 6)
				{
					str[len++] = ' ';
				}
				str[len] = '\0';
				LCDShowStr(0,0,str);
			}
			else
			{
				LCDShowStr(0,0,"error!");
			}
			StartDS18B20();
		}
	}
}
unsigned char IntToString(unsigned char *str,int dat)
{
	signed char i = 0;
	unsigned char len = 0;
	unsigned char buf[6];
	
	if(dat < 0)
	{
		dat = -dat;
		*str++ = '-';
		len++;
	}
	do
	{
		buf[i++] = dat % 10;
		dat = dat / 10;
		
	}while(dat > 0);
	len = len + i;
	while(i-- > 0)
	{
		*str++ = buf[i] + '0';
	}
	*str = '\0';
	
	return len;
		
}
void Timer0Init()
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xD5;		//设置定时初值
	TH0 = 0x97;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;
}

void InterruptTimer0() interrupt 1
{
	TF0 = 0;
	TL0 = 0xD5;
	TH0 = 0x97;

	i++;
	if(i >= 100)
	{
		i = 0;
		flag1s = 1;
	}
}
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
	bit res;				//The signal of successfully get the temperature
	int temp;
	int intT,decT;			//First and last eight bits of temperature
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
			res = GetDS18B20Temp(&temp);		//Get the temperature
			if(res)								//If success,Converting temp to strings
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
				LCDShowStr(0,0,str);			//Display temperature
			}
			else								//If failed,display "error"
			{
				LCDShowStr(0,0,"error!");		
			}
			StartDS18B20();
		}
	}
}
unsigned char IntToString(unsigned char *str,int dat)	//Turn integer into string
{
	signed char i = 0;
	unsigned char len = 0;
	unsigned char buf[6];
	
	if(dat < 0)				//Determine the + and - of temperature
	{
		dat = -dat;
		*str++ = '-';
		len++;
	}
	do						//Put every bit of temperature into buffer
	{
		buf[i++] = dat % 10;
		dat = dat / 10;
		
	}while(dat > 0);
	len = len + i;
	while(i-- > 0)			//Trun char to int
	{
		*str++ = buf[i] + '0';
	}
	*str = '\0';
	
	return len;
		
}
void Timer0Init()		//10ms@32M 12T with openning Timer0 interrupt
{
	AUXR &= 0x7F;		
	TMOD &= 0xF0;		
	TMOD |= 0x01;		
	TL0 = 0xD5;		
	TH0 = 0x97;		
	TF0 = 0;		
	TR0 = 1;		
	ET0 = 1;
}

void InterruptTimer0() interrupt 1	//Refresh temperature every 100 interruptions(1s)
{
	TF0 = 0;
	TL0 = 0xD5;
	TH0 = 0x97;

	i++;
	if(i >= 100)
	{
		i = 0;
		flag1s = 1;		//The flag of Refreshing
	}
}
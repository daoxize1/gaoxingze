#include <STC12C5A60S2.H>
/*times = 1 --> hour
  times = 2 --> minute
  times = 3 --> second
  times = 4 --> Vmax
  times = 5 --> Vmin */

sbit B1 = P3^4;
sbit B2 = P3^5;
sbit B3 = P3^6;
sbit B4 = P3^7;
extern char Interface;				//表示现在是界面A还是界面B
extern char Alarm[3];				//闹钟时间	
extern bit BuzzerOn;				//表示蜂鸣器的状态

unsigned char times = 0;			//表示正在修改的数据
unsigned char VH = 6;				//电压上报上限
unsigned char VL = 4;				//电压上报下限

void delay(int i)					//类似于消抖
{
	while(--i);
}
void KeyScan()						//判断按下了哪个键
{
	if(B1 == 0 && Interface == 'A') //切换界面
	{
		Interface = 'B';
		while(B1 == 0);
		delay(100000);				//消抖
	}
	
	if(B1 == 0 && Interface == 'B')	//同上
	{
		Interface = 'A';
		while(B1 == 0);
		delay(100000);
	}
	
	if(B2 == 0 && Interface == 'B')	//判断修改哪个位置的数据
	{
		times++;
		if(times == 6)
			times = 0;
		while(B2 == 0);
		delay(100000);
	}
	
	if(B3 == 0 && Interface == 'B')	//修改数据
	{
		switch(times)
		{
			case 1:Alarm[0]++;if(Alarm[0] == 25) Alarm[0] = 0;break;
			case 2:Alarm[1]++;if(Alarm[1] == 60) Alarm[1] = 0;break;
			case 3:Alarm[2]++;if(Alarm[2] == 60) Alarm[2] = 0;break;
			case 4:VH++;if(VH == 10) VH = 0;break;
			case 5:VL++;if(VL == 10) VL = 0;break;
			default:break;
		}
		while(B3 == 0);
		delay(100000);
	}
	
	if(B4 == 0 && BuzzerOn == 1)	//B4关闭蜂鸣器
	{
		BuzzerOn = 0;
	}
}


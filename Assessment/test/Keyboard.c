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
extern char Interface;				//��ʾ�����ǽ���A���ǽ���B
extern char Alarm[3];				//����ʱ��	
extern bit BuzzerOn;				//��ʾ��������״̬

unsigned char times = 0;			//��ʾ�����޸ĵ�����
unsigned char VH = 6;				//��ѹ�ϱ�����
unsigned char VL = 4;				//��ѹ�ϱ�����

void delay(int i)					//����������
{
	while(--i);
}
void KeyScan()						//�жϰ������ĸ���
{
	if(B1 == 0 && Interface == 'A') //�л�����
	{
		Interface = 'B';
		while(B1 == 0);
		delay(100000);				//����
	}
	
	if(B1 == 0 && Interface == 'B')	//ͬ��
	{
		Interface = 'A';
		while(B1 == 0);
		delay(100000);
	}
	
	if(B2 == 0 && Interface == 'B')	//�ж��޸��ĸ�λ�õ�����
	{
		times++;
		if(times == 6)
			times = 0;
		while(B2 == 0);
		delay(100000);
	}
	
	if(B3 == 0 && Interface == 'B')	//�޸�����
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
	
	if(B4 == 0 && BuzzerOn == 1)	//B4�رշ�����
	{
		BuzzerOn = 0;
	}
}


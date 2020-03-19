#include <STC12C5A60S2.H>
sbit buzz = P1^7;
extern bit flag;				//������ȷ�ı�־
bit BuzzerOn;
extern void UartInit();
extern void LCDInit();
extern void ClockInit();
extern void UartSentString(char *str);
extern void LCDShowStr(unsigned char x,unsigned char y,char *str);
extern void KeyScan();
extern void delay(int i);
char Interface;
void main()
{
	UartInit();
	LCDInit();
	ClockInit();
	EA = 1;						//�����ж�
	TI = 0;						//���ڷ���
	IT0 = 1;
	EX0 = 1;
	LCDShowStr(0,0,"Waiting...");
	UartSentString("Please input password!\r\n");
	while(1)					//�ȴ���ȷ��������
	{
		if(flag == 1)
			break;
	}
	Interface = 'A';			//����A����
	while(1)					//ɨ�谴��
	{
		KeyScan();
		if(BuzzerOn == 1)
		{
			buzz = ~buzz;		//�ҵķ��������������ַ�ʽ����
		}
		delay(300);
	}
	while(1);
}


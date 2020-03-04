#include <STC12C5A60S2.H>
char Output[40]={"Please input password!"};
char Input[30];
void UartInit(void)		//9600bps@32MHz
{
	PCON |= 0x80;		//ʹ�ܲ����ʱ���λSMOD
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x04;		//���������ʷ�����ʱ��ΪFosc,��1T
	BRT = 0x30;		//�趨���������ʷ�������װֵ
	AUXR |= 0x01;		//����1ѡ����������ʷ�����Ϊ�����ʷ�����
	AUXR |= 0x10;		//�������������ʷ�����
	ES = 1;
}

void UartInterrupt() interrupt 4
{
	unsigned char i = 0;
	TI = 0;
	do
	{
		SBUF = Output[i];
		while(!TI);
		TI = 0;
		i++;
	}while(Output[i]!='\0');
	Input[0] = SBUF;
	RI = 0;

}
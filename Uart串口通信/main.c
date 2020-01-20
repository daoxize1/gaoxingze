//������9600 16���Ʒ��� ��ʲô����LCD����ʾʲô���� ��Ŀǰ����������ַ�����
#include <STC12C5A60S2.H>
#include <string.h>
int i = 0;
extern void LCDInit();
extern void ShowStr(unsigned char x,unsigned char y,char *str);
void UartInit();
void main()
{
    UartInit();
    LCDInit();
    while(1);
}

//��������STC-ISP�������ʼ�������û�Լ���
void UartInit(void)		//9600bps@12.000MHz
{
	PCON |= 0x80;		//ʹ�ܲ����ʱ���λSMOD
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x04;		//���������ʷ�����ʱ��ΪFosc,��1T
	BRT = 0xB2;		//�趨���������ʷ�������װֵ
	AUXR |= 0x01;		//����1ѡ����������ʷ�����Ϊ�����ʷ�����
	AUXR |= 0x10;		//�������������ʷ�����
    ES = 1;
    EA = 1;
}


void UartInterrupt() interrupt 4
{
    char str[20];
    /*do
    {
        str[i] = SBUF;
        i++;
    }while(SBUF!="\0");
    RI = 0;
    i = 0;*/
    str[0] = SBUF + '0';
    RI = 0;
    str[1] = '\0';
    ShowStr(0,0,str);
    SBUF = 1;
    while(!TI);
    TI = 0;
}
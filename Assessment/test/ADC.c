#include <STC12C5A60S2.H>
#include <intrins.h>
sbit DOUT = P1^3;		//�������
sbit DIN = P1^4;		//��������
sbit CS = P1^5;			//Ƭѡ
sbit CLK = P1^6;		//ʱ��

void SPIWrite(unsigned char dat)
{
	unsigned char i;
	CLK = 0;
	for(i=0; i<8; i++)
	{
		DIN = dat >> 7; //�������λ
		dat <<= 1;
		CLK = 0;
		CLK = 1;  //�����ط�������
	}
}

unsigned int SPIRead()
{
	unsigned char i;
	unsigned int dat = 0;
	for(i=0; i<12; i++)  //����12λ����
	{
		dat <<= 1;
		CLK = 1;
		CLK = 0;    	//�½��ؽ�������
		
		dat |= DOUT;
	}
	return dat;
	
}

unsigned int ReadADValue(unsigned char cmd)
{
	unsigned char i;
	unsigned int AD_Value;
	CLK = 0;		
	CS = 0;
	SPIWrite(cmd);
	for(i=6; i>0; i--); 	//��ʱ�ȴ�ת�����
	CLK = 1;   //����һ��ʱ�����ڣ����BUSY
	_nop_();
	_nop_();
	CLK = 0;
	_nop_();
	_nop_();
	AD_Value = SPIRead();
	CS = 1;
	return AD_Value;	
}
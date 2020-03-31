#include <STC12C5A60S2.H>
#include <intrins.h>
sbit DOUT = P1^3;		//数据输出
sbit DIN = P1^4;		//数据输入
sbit CS = P1^5;			//片选
sbit CLK = P1^6;		//时钟

void SPIWrite(unsigned char dat)
{
	unsigned char i;
	CLK = 0;
	for(i=0; i<8; i++)
	{
		DIN = dat >> 7; //放置最高位
		dat <<= 1;
		CLK = 0;
		CLK = 1;  //上升沿放置数据
	}
}

unsigned int SPIRead()
{
	unsigned char i;
	unsigned int dat = 0;
	for(i=0; i<12; i++)  //接收12位数据
	{
		dat <<= 1;
		CLK = 1;
		CLK = 0;    	//下降沿接收数据
		
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
	for(i=6; i>0; i--); 	//延时等待转换结果
	CLK = 1;   //发送一个时钟周期，清除BUSY
	_nop_();
	_nop_();
	CLK = 0;
	_nop_();
	_nop_();
	AD_Value = SPIRead();
	CS = 1;
	return AD_Value;	
}
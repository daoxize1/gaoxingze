#include <STC12C5A60S2.H>
#include<intrins.h>
sbit DOUT = P3^7;	  //Output
sbit CLK  = P3^6;	  //Clock
sbit DIN  = P3^4;	  //Input
sbit CS   = P3^5;	  //Chip Select

void SPI_Write(unsigned char dat)
{
	unsigned char i;
	CLK = 0;
	for(i=0; i<8; i++)
	{
		DIN = dat >> 7;  	//Put highest
		dat <<= 1;
		CLK = 0;			//Rising edge placing data

		CLK = 1;

	}
}
unsigned int SPI_Read()
{
	unsigned char i, dat=0;
	CLK = 0;
	for(i=0; i<12; i++)		//receive 12 bits data
	{
		dat <<= 1;

		CLK = 1;
		CLK = 0;

		dat |= DOUT;

	}
	return dat;	
}
unsigned int Read_AD_Data(unsigned char cmd)
{
	unsigned char i;
	unsigned int AD_Value;
	CLK = 0;
	CS  = 0;
	SPI_Write(cmd);
	for(i=6; i>0; i--); 	//Waiting
	CLK = 1;	  //Send one clock cycle,clear BUSY
	_nop_();
	_nop_();
	CLK = 0;
	_nop_();
	_nop_();
	AD_Value=SPI_Read();
	CS = 1;
	return AD_Value;	
}
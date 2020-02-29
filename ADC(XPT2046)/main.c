//Use ADC to read voltage value and display on the digital tube
#include <STC12C5A60S2.H>
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
extern unsigned int Read_AD_Data(unsigned char cmd);
unsigned char LEDBuffer[4];
unsigned char code LEDChar[10]={
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
int i;
void delay(int i)
{
	while(i--);	
}
void datapros()
{
	unsigned int temp;
	if(i==50)
	{
		i=0;
		temp = Read_AD_Data(0x94);		//   AIN0 Potentiometer
	}
	i++;
	LEDBuffer[0]=LEDChar[temp/1000];//Thousands
	LEDBuffer[1]=LEDChar[temp%1000/100];//Hundreds
	LEDBuffer[2]=LEDChar[temp%1000%100/10];//Ten
	LEDBuffer[3]=LEDChar[temp%1000%100%10];//Singles		
}
void DigDisplay()
{
	unsigned char i;
	for(i=0;i<4;i++)
	{
		switch(i)	 //Bit selection
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//Display 0th
			case(1):
				LSA=1;LSB=0;LSC=0; break;//Display 1th
			case(2):
				LSA=0;LSB=1;LSC=0; break;//Display 2th
			case(3):
				LSA=1;LSB=1;LSC=0; break;//Display 3th	
		}
		P0=LEDBuffer[i];//Send data
		delay(1000); 
		P0=0x00;//Remove shadow
	}		
}

void main()
{	
	while(1)
	{
		datapros();	 //Data processing
		DigDisplay();//Digital tube display		
	}		
}

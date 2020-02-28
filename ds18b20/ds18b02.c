#include <STC12C5A60S2.H>
sbit IO_DS18B20 = P3^2;

void DelayX10us(unsigned char t)
{
	unsigned char j;
	do
	{
		j = 77;
		while (--j);
	}while(--t);
}
void Delay2us()
{
	unsigned char i;

	i = 13;
	while (--i);
}
bit GetDS18B20ACK()	//Initialize according to the timing diagram
{
	bit ack;
	EA = 0;
	IO_DS18B20 = 0;
	DelayX10us(65);
	IO_DS18B20 = 1;
	DelayX10us(6);
	ack = IO_DS18B20;
	while(!IO_DS18B20);
	EA = 1;
	return ack;
}

void WriteDS18B20(unsigned char dat)
{
	unsigned char mask;
	EA = 0;									//Close interrupt to reduce interference
	for(mask=0x01;mask!=0x00;mask<<=1)		//Bitwise value according to the timing diagram
	{
		IO_DS18B20 = 0;
		Delay2us();
		IO_DS18B20 = (mask&dat);
		DelayX10us(6);
		IO_DS18B20 = 1;
	}
	EA = 1;									//Open interrupt
}

unsigned char ReadDS18B20()					//Read data
{
	unsigned char mask;
	unsigned char dat;
	EA = 0;									//Close interrupt to reduce interference
	for(mask=0x01;mask!=0x00;mask<<=1)		//Bitwise value according to the timing diagram
	{
		IO_DS18B20 = 0;
		Delay2us();
		IO_DS18B20 = 1;
		Delay2us();
		if(IO_DS18B20 == 1)
			dat |= mask;
		else
			dat &= ~mask;
		DelayX10us(6);
	}
	
	EA = 1;									//Open interrupt
	
	return dat;
	
}

bit StartDS18B20()						//Determine whether to accept data successfully	
{
	bit ack;
	
	ack = GetDS18B20ACK();
	if(ack == 0)
	{
		WriteDS18B20(0xCC); 
		WriteDS18B20(0x44); 
	}
	
	return ~ack;
}

bit GetDS18B20Temp(int *temp)			//Get temp
{
	bit ack;
	unsigned char LSB,MSB;				//High 8 bits,low 8 bits
	
	ack = GetDS18B20ACK();
	if(ack == 0)
	{
		WriteDS18B20(0xCC); 
		WriteDS18B20(0xBE);
		LSB = ReadDS18B20();
		MSB = ReadDS18B20();
		*temp = ((int)MSB<<8)+LSB;		//Turn double 8bits to 16bits
	}
	return ~ack;
}


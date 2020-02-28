#include <STC12C5A60S2.H>
extern unsigned char EEPROMRead(unsigned char addr);
extern void EEPROMWrite(unsigned char addr,unsigned char dat);
extern void LCDInit();
extern void LCDShowStr(unsigned char x,unsigned char y,char *str);
extern void LCDShowChar(unsigned char x,unsigned char y,char a);
void main()
{
    unsigned char dat;
    LCDInit();
    dat = EEPROMRead(0x02);         //Read data 0f 0x02
    LCDShowChar(0,0,dat+'0');
    dat++;
    EEPROMWrite(0x02,dat);          //Write data to 0x02
    while(1);
}
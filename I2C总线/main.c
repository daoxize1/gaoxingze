//I2C寻址EEPROM，EEPROM的地址是0x50，0x60为空地址，将寻址结果显示在LCD1602上
#include <STC12C5A60S2.H>
#include <string.h>
extern bit I2CAddressing(unsigned char addr);
extern void ShowStr(unsigned char x,unsigned char y,char *str);
extern void LCDInit();
void main()
{
    bit ack;
    char str[10];
    LCDInit();
    
    ack = I2CAddressing(0x50);
    strcpy(str,"0x50:");
    str[5] = (unsigned char)ack+'0';
    str[6] = '\0';
    ShowStr(0,0,str);
    
    strcpy(str,"0x60:");
    ack = I2CAddressing(0x60);
    str[5] = (unsigned char)ack+'0';
    str[6] = '\0';
    ShowStr(0,1,str);
    
    while(1);
}

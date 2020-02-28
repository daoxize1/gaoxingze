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
    
    ack = I2CAddressing(0x50);              //I2C Addressing 0x50
    strcpy(str,"0x50:");
    str[5] = (unsigned char)ack+'0';        
    str[6] = '\0';                          //Turn addressing results into strings
    ShowStr(0,0,str);                       //Display addressing results
    
    strcpy(str,"0x60:");                    //I2C Addressing 0x50
    ack = I2CAddressing(0x60);
    str[5] = (unsigned char)ack+'0';
    str[6] = '\0';                          //Turn addressing results into strings
    ShowStr(0,1,str);                       //Display addressing results
    
    while(1);
}

#ifndef _EEPROM_
#define _EEPROM_

//typedef unsigned char BYTE;
//typedef unsigned int WORD;

/*Declare SFR associated with the IAP */
sfr IAP_DATA    =   0xE2;           //Flash data register
sfr IAP_ADDRH   =   0xE3;           //Flash address HIGH
sfr IAP_ADDRL   =   0xE4;           //Flash address LOW
sfr IAP_CMD     =   0xE5;           //Flash command register
sfr IAP_TRIG    =   0xE6;           //Flash command trigger
sfr IAP_CONTR   =   0xE7;           //Flash control register

/*Define ISP/IAP/EEPROM command*/
#define CMD_IDLE    0               //Stand-By
#define CMD_READ    1               //Byte-Read
#define CMD_PROGRAM 2               //Byte-Program
#define CMD_ERASE   3               //Sector-Erase

/*Define ISP/IAP/EEPROM operation const for IAP_CONTR*/
//#define ENABLE_IAP 0x80           //if SYSCLK<30MHz
//#define ENABLE_IAP 0x81           //if SYSCLK<24MHz
#define ENABLE_IAP  0x82            //if SYSCLK<20MHz
//#define ENABLE_IAP 0x83           //if SYSCLK<12MHz
//#define ENABLE_IAP 0x84           //if SYSCLK<6MHz
//#define ENABLE_IAP 0x85           //if SYSCLK<3MHz
//#define ENABLE_IAP 0x86           //if SYSCLK<2MHz
//#define ENABLE_IAP 0x87           //if SYSCLK<1MHz

void IapProgramByte( unsigned char dat,unsigned int addr);//储存数据到EEPEOM
void IapEraseSector(unsigned int addr);//擦除EEPROM数据
unsigned char IapReadByte(unsigned int addr);//读取EEPROM数据

#endif
#ifndef _SPD6000_
#define _SPD6000_
#include <reg52.h>
#include "global_var.h"
sbit SDA = P1^1;
sbit SCL = P1^0;
sbit SS  = P1^6;

extern Ms4515;
void SomeNOP();
unsigned char SPI_ReadByte();
unsigned char MS4515DO_read(unsigned char * p,unsigned char* temperature);
void data_read(Ms4515* date)  ;
 float date_Smooth();
float Wid_Speed();
#endif

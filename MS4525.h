#ifndef _MS4525_
#define _MS4525_
#include <reg52.h>
#include "global_var.h"

sbit SS2  = P1^7; // 1.7

extern Ms4515;
//unsigned char MS4525DO_read(unsigned char * p,unsigned char* temperature);
//void data_read_4525(Ms4515* date)  ;
float date_Smooth_4525(float *tem);
unsigned int tmp_read();
#endif

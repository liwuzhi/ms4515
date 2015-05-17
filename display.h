#ifndef _DISPLAY_
#define _DISPLAY_
#include "global_var.h"
#include "lcd12864.h"

//void disylay_mun(unsigned int num,char point,char start_x,char start_y);
void display_stringChar(unsigned char start_x,unsigned char start_y,char* s);
void disylay_mun(unsigned int num,char point,char start_x,char start_y)	;
unsigned char display_Preassure();
unsigned char display_Area();
unsigned char display_Main();
unsigned char display_Range();
unsigned char display_uint();
unsigned char display_ZKSet();
unsigned char display_Rate();
unsigned char display_Renew();
unsigned char display_WindSpeedRate();
unsigned char display_WindSpeedZero();
unsigned char display_WindSpeed();
unsigned char display_Protect1(unsigned char ** cp,char num);

unsigned char display_workchang();
unsigned char display_MaxOut();

#endif
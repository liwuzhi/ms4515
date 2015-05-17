#ifndef _GLOBAL_VAR_
#define _GLOBAL_VAR_

//#define _DEBUG_
typedef struct Ms4515_
{
  float pressure ;
  float temperature;
}Ms4515;

extern unsigned int temper1;

extern xdata float dat1_zero;

extern xdata char g_cFunc;

extern unsigned int g_cOut2;

extern xdata unsigned int g_iProtect;

extern xdata unsigned char g_cSecrit ;

extern xdata unsigned char g_cStart ;

extern xdata unsigned char g_cPassword1;

extern xdata float g_fK2;			

extern xdata unsigned char g_cIntegral;

extern xdata unsigned int g_iArea;

extern xdata char g_cUint;

extern xdata float g_fZero ;

extern xdata float g_fZero_rev ;

extern xdata float g_fK1 ;

extern xdata unsigned int g_iRange;

extern unsigned char g_cOut1[2];

extern unsigned int g_iOut2;

extern xdata unsigned int g_iRangeMin;

extern Ms4515 date;

extern xdata unsigned int g_iTimebase;

extern xdata unsigned char g_cSecrit_Num ;

extern xdata unsigned char g_cCh4Flag;

extern xdata char g_cReadCh4;

extern xdata unsigned int g_iCh4Num ;

extern xdata char g_cWorkChange ;

extern char g_cMaxOut;

extern xdata float g_fSum ;

extern unsigned int g_iTime;

extern unsigned int g_iCh4Num_test;

extern unsigned int g_iLed_light ;

extern float g_fSum_biao;

extern float g_fSum_biao_ch4 ;

#endif
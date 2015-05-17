
#include <reg52.h>

//#include "SPD6000.h"
#include "display.h"
#include "lcd12864.h"
#include "global_var.h"
#include "storage.h"
#include "pwm.h"
#include "ziku.h"
#include "CH4.h"

sfr WDT_CONTR = 0xe1;
sbit  OUT1  = P3^5;
sbit  OUT2  = P3^7;
sbit  LED = P3^1;


 Ms4515 date ;
void Timeinit();
void main()
{
   
   code unsigned char* chinese1[] ={font_22,font_23,yi,font_00,font_00};
   code unsigned char* chinese3[] ={font_22,font_23,font_00,font_00,font_00};
   code char arr[] = {'e','r','r','\0'};
   P3M0 = 0x00;//P3M0 & 0XFE;
   P3M1 = 0x01;//P3M1 | 0x01;
   lcd_on();
   dat_Init();
   Lcm_Init();
   pca_Init();
   Timeinit();
   date.pressure = 0; 
  // data_read(&date);
    if(g_cSecrit == 0)
	{
	  g_cStart++;
	  if(g_cStart>6)
	    {
		  g_cStart =6;
		}
	 // Dateeprom();
	 StrotPrect();
	}
	else
	{
	  g_cStart = 0; 
	}

	 if(g_cStart == 6 )
	  {
	    Clean_Display(0,0,128,48,0);
	    display_stringChar(6,1,arr);
		while(1)
		{
		}
	  }
	 
  while(1)
  {
       Clean_Display(0,0,128,64,0);//在进入新界面前清空前一界面的值
     
	   switch (g_cFunc)
		{
		  case 0:  display_Main();
		              break;
		  case 1:  display_WindSpeed();
		              break;
		  case 2:  display_WindSpeedZero();
		              break;
		  case 3:  display_WindSpeedRate();
		              break;
		  case 4:  display_Renew();
		              break;
		  case 5:  display_Rate();
		              break;
		  case 6:  display_ZKSet();
		              break;
		  case 7:  display_Area();
		              break;
		  case 8:  display_uint();
		              break;
		  case 9:  display_Range();
		              break;
		  case 10: display_Preassure();
		              break;
		  case 11: display_workchang();
		              break;
		  case 12 : display_MaxOut();
		              break;
		  case 13: if(display_Protect1(chinese3,240) == 1)
		                {
						   g_cSecrit = 1;
						   StrotPrect();
						 //  Dateeprom();
						}
					g_cFunc = 0; 
		            break;
		  case 15: display_Protect1(chinese1,5);
		              break;
		  default : break;
		}  
		if(g_cSecrit == 1)
		{
			if(g_cFunc == 13)
			    g_cFunc =0;
		}
		else
		{
		   if(g_cFunc == 14)
			    g_cFunc =0;
		}
	}
}

void Timeinit()
{
  TMOD|= 0x11;
  IP = 0X02;
  TH1=(65535-5000)/256; 
  TL1=(65535-5000)%256; 

  TH0=100; 
  TL0=100;
  EA=1;
  ET0=1;
  TR0=1;
  ET1=1;
  TR1=1;
}

void T1_time()interrupt 3
{  
	//TH1=(65535-50000)/256;
	//TL1=(65535-50000)%256;

	TH1=60;
	TL1=175;	 //175
     
	 g_iLed_light++;
	 if(g_iLed_light >= 1150)
	   {
	     g_iLed_light =1150;
		 lcd_off(); 
	   }
	   else
	   {
	     lcd_on();
	   }

	g_iProtect++;
	if(g_iProtect > 1000)
	  {
	      g_iProtect = 900;
	  }

	g_iTimebase++;
	 if(g_iTimebase > 21)
	 {
	   g_iTimebase = 1;
	   g_iTime++;
	   if(g_iTime ==3427 )
	    {
		  g_iTime = 0;
		}
	 }

	 g_cReadCh4++;
	 if(g_cReadCh4 == 60)
	  {
	    g_cReadCh4 = 1;
		startCH4();
	  }
     if(g_cReadCh4 == 21)
	   {
	     stopCH4(); 
	   }

	WDT_CONTR=0x3c;
	if(g_iTimebase%10 == 0)
	  {
	     LED = ~LED;
	  }	 
}

void T0_time()interrupt 1
{  
	TH0=g_cOut1[0];
	TL0=g_cOut1[1];
	OUT1 = ~OUT1 ;
}

void PCA_isr() interrupt 6
{
    CCF0 = 0;                       //Clear interrupt flag
    CCAP0L = out2;
    CCAP0H = out2 >> 8;            //Update compare value
    out2 += g_iOut2;
    OUT2 = ~OUT2; 
}



void exint() interrupt 0
{
  g_iCh4Num++;
}  
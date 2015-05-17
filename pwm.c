#include "reg51.h"
#include "intrins.h"
#include "pwm.h"
#include "global_var.h"
unsigned int out2;

void pca_Init()
{
      CCON = 0;                       //Initial PCA control register
                                    //PCA timer stop running
                                    //Clear CF flag
                                    //Clear all module interrupt flag
    CL = 0;                         //Reset PCA base timer
    CH = 0;
    CMOD = 0x00;                    //Set PCA timer clock source as Fosc/12
                                    //Disable PCA timer overflow interrupt
//    value = T100Hz;
    CCAP0L = out2;
    CCAP0H = out2 >> 8;            //Initial PCA module-0
     out2+= g_iOut2;
    CCAPM0 = 0x49;                  //PCA module-0 work in 16-bit timer mode and enable PCA interrupt

    CR = 1;                         //PCA timer start run
    EPCAI = 1;
//    EA = 1;
}

void pca_set2(float x)
{/*
  if(g_cUint == 0)
   {
    g_iOut2 = 500000L/(200+800*x/g_iRange);//100*(200+800*x/g_iRange);
   }
   else
   {
    g_iOut2 = 500000L/(200+800*x/g_iRangeMin);//100*(200+800*x/g_iRangeMin);  
   } */
  g_iOut2 = 500000L/(200+800*x/100);
}
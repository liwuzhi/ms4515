#ifndef _PWM_
#define _PWM_

#define FOSC    12000000L
#define T200Hz  (FOSC / 12 / 50)
#define T1000Hz (FOSC / 12 /10)

/*Declare SFR associated with the PCA */
sbit EPCAI      =   IE^6;

sfr CCON        =   0xD8;           //PCA control register
sbit CCF0       =   CCON^0;         //PCA module-0 interrupt flag
sbit CCF1       =   CCON^1;         //PCA module-1 interrupt flag
sbit CR         =   CCON^6;         //PCA timer run control bit
sbit CF         =   CCON^7;         //PCA timer overflow flag
sfr CMOD        =   0xD9;           //PCA mode register
sfr CL          =   0xE9;           //PCA base timer LOW
sfr CH          =   0xF9;           //PCA base timer HIGH
sfr CCAPM0      =   0xDA;           //PCA module-0 mode register
sfr CCAP0L      =   0xEA;           //PCA module-0 capture register LOW
sfr CCAP0H      =   0xFA;           //PCA module-0 capture register HIGH
sfr CCAPM1      =   0xDB;           //PCA module-1 mode register
sfr CCAP1L      =   0xEB;           //PCA module-1 capture register LOW
sfr CCAP1H      =   0xFB;           //PCA module-1 capture register HIGH
sfr CCAPM2      =   0xDC;           //PCA module-2 mode register
sfr CCAP2L      =   0xEC;           //PCA module-2 capture register LOW
sfr CCAP2H      =   0xFC;           //PCA module-2 capture register HIGH
sfr CCAPM3      =   0xDD;           //PCA module-3 mode register
sfr CCAP3L      =   0xED;           //PCA module-3 capture register LOW
sfr CCAP3H      =   0xFD;           //PCA module-3 capture register HIGH

extern unsigned int out2;
void pca_Init();

void pca_set2(float x);

#endif
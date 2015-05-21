#include <reg52.h>
#include "eeprom.h"
#include "global_var.h"

#define SECRIT     0x6a00
#define START      0x6a01

#define ZERO_ADD_1 0x6fF0
#define ZERO_ADD_2 0x6fF1

#define K2_ADD_1    0x6fF2
#define K2_ADD_2    0x6fF3

#define K1_ADD_1    0x6fFB
#define K1_ADD_2    0x6fFC

#define INTEGRAL   0x6ff4

#define AREA_1     0x6ff9
#define AREA_2     0x6ffa

#define UNIT       0x6ff7

#define RANGE      0x6ff8

#define RANGEMIN1  0x6ff5
#define RANGEMIN2  0x6ff6

#define SECRIT_NUM 0x6fff

#define ISCH4      0x6fef

#define MAXOUT     0x6fea

#define SUM1       0x6fee
#define SUM2       0x6fed
#define SUM3       0x6fec
#define SUM4       0x6feb

#define SUM1_BIAO_1       0x6fe5
#define SUM1_BIAO_2       0x6fe6
#define SUM1_BIAO_3       0x6fe7
#define SUM1_BIAO_4       0x6fe8

#define SUM1_BIAO_CUN_1       0x6fd1
#define SUM1_BIAO_CUN_2       0x6fd2
#define SUM1_BIAO_CUN_3       0x6fd3
#define SUM1_BIAO_CUN_4       0x6fd4

#define ZERO_ADD_REV_1 0x6fe1
#define ZERO_ADD_REV_2 0x6fe2


#define START1     0x6cf0
#define START2     0x6cf1

/**********二级eeprom保护数据******************/
#define ZERO_ADD_1_2 0x68F0
#define ZERO_ADD_2_2 0x68F1

#define K2_ADD_1_2    0x68F2
#define K2_ADD_2_2    0x68F3

#define K1_ADD_1_2    0x68FB
#define K1_ADD_2_2    0x68FC

#define INTEGRAL_2   0x68f4

#define AREA_1_2     0x68f9
#define AREA_2_2     0x68fa

#define UNIT_2       0x68f7

#define RANGE_2      0x68f8

#define RANGEMIN1_2  0x68f5
#define RANGEMIN2_2  0x68f6

#define SECRIT_NUM_2 0x68ff

#define ISCH4_2      0x68ef

#define MAXOUT_2     0x68ea

#define SUM1_2       0x68ee
#define SUM2_2       0x68ed
#define SUM3_2       0x68ec
#define SUM4_2       0x68eb

#define SUM2_BIAO_1       0x68e6
#define SUM2_BIAO_2       0x68e7
#define SUM2_BIAO_3       0x68e8
#define SUM2_BIAO_4       0x68e9


#define SUM2_BIAO_CUN_1       0x68e5
#define SUM2_BIAO_CUN_2       0x68e4
#define SUM2_BIAO_CUN_3       0x68e3
#define SUM2_BIAO_CUN_4       0x68e0  
 
#define ZERO_ADD_REV_1_2 0x68e1
#define ZERO_ADD_REV_2_2 0x68e2


void dat_Init()
{

   //char temp1,temp2,temp3,temp4;
   char temp1,temp2;
   char *p;
   temp1 = IapReadByte(START1);
   temp2 = IapReadByte(START2);
   if(temp1 ==10 && temp2 == 10)
   {
        /*面积参数初始化*/
		temp1 =IapReadByte(AREA_1);
		temp2 =IapReadByte(AREA_2);
        g_iArea = temp1*100+temp2;

		/*积分系数初始化话*/
        g_cIntegral = IapReadByte(INTEGRAL);

		/*零点值出事化*/
        temp1 = IapReadByte(ZERO_ADD_1);
		temp2 = IapReadByte(ZERO_ADD_2);
		g_fZero = (temp1*100+temp2)/100;

		/*零点在回复时用的值*/
		temp1 = IapReadByte(ZERO_ADD_REV_1);
		temp2 = IapReadByte(ZERO_ADD_REV_2);
		g_fZero_rev = (temp1*100+temp2)/100;

		/*比例值初始化*/
        temp1 = IapReadByte(K1_ADD_1);
		temp2 = IapReadByte(K1_ADD_2);
		g_fK1 = (temp1*100+temp2)/1000;

		/*补偿系数初始化*/
        temp1 = IapReadByte(K2_ADD_1);
		temp2 = IapReadByte(K2_ADD_2);
		g_fK2 = (temp1*100+temp2)/100;

	    /*单位初始化*/
		g_cUint =  IapReadByte(UNIT);

		/*量程初始化 秒为单位*/
		g_iRange = IapReadByte(RANGE);
	    
		/*量程初始化 分钟为单位*/
		 temp1 = IapReadByte(RANGEMIN1);
		 temp2 = IapReadByte(RANGEMIN2);
		 g_iRangeMin = temp1*100+temp2;

		 g_cSecrit = IapReadByte(SECRIT);

		 g_cWorkChange  = IapReadByte(ISCH4);

		 g_cMaxOut = IapReadByte(MAXOUT);

		 g_cStart =  IapReadByte(START);

		  p = (char *)&g_fSum;
		 *p = IapReadByte(SUM1);
		 *(p+1) = IapReadByte(SUM2);
		 *(p+2) = IapReadByte(SUM3);
		 *(p+3) = IapReadByte(SUM4);
	/*	 temp1 = IapReadByte(SUM1);
		 temp2 = IapReadByte(SUM2);
		 temp3 = IapReadByte(SUM3);
		 temp4 = IapReadByte(SUM4);
		 g_fSum = temp1+temp2*100.0+temp3*10000.0+temp4*1000000.0;*/

         p = (char *)&g_fSum_biao;
		 *p = IapReadByte(SUM1_BIAO_1);
		 *(p+1) = IapReadByte(SUM1_BIAO_2);
		 *(p+2) = IapReadByte(SUM1_BIAO_3);
		 *(p+3) = IapReadByte(SUM1_BIAO_4);
		 /*
		 temp1 = IapReadByte(SUM1_BIAO_1);
		 temp2 = IapReadByte(SUM1_BIAO_2);
		 temp3 = IapReadByte(SUM1_BIAO_3);
		 temp4 = IapReadByte(SUM1_BIAO_4);
		 g_fSum_biao = temp1+temp2*100.0+temp3*10000.0+temp4*1000000.0;	*/

		 p = (char *)&g_fSum_biao_ch4;
		 *p = IapReadByte(SUM1_BIAO_CUN_1);
		 *(p+1) = IapReadByte(SUM1_BIAO_CUN_2);
		 *(p+2) = IapReadByte(SUM1_BIAO_CUN_3);
		 *(p+3) = IapReadByte(SUM1_BIAO_CUN_4);
		 /*
		 temp1 = IapReadByte(SUM1_BIAO_CUN_1);
		 temp2 = IapReadByte(SUM1_BIAO_CUN_2);
		 temp3 = IapReadByte(SUM1_BIAO_CUN_3);
		 temp4 = IapReadByte(SUM1_BIAO_CUN_4);
		 g_fSum_biao_ch4 = temp1+temp2*100.0+temp3*10000.0+temp4*1000000.0;	*/
   }
   else
   {

     g_iArea = 10000; //1.0平方米
	 g_cIntegral = 0; //0
	 g_fZero = 0.0;
	 g_fZero_rev = 9.0;
	 g_fK1 = 1.0;
	 g_fK2 = 1.0;
	 g_cUint = 1;
	 g_iRange = 1;
	 g_iRangeMin = 100;
	 g_cSecrit = 0;
	 g_cStart = 0;
	 g_cSecrit_Num = 0;
	 g_cWorkChange = 0;
	 g_fSum = 0;
	 g_fSum_biao = 0;
	 g_fSum_biao_ch4 = 0;
	 g_cMaxOut = 0;
	 EA = 0;
	 IapEraseSector(ZERO_ADD_1);
	 IapEraseSector(START);
     IapEraseSector(START);
	 IapProgramByte(0,SECRIT);
     IapProgramByte(0,START);

	 IapProgramByte(0,ZERO_ADD_1);
	 IapProgramByte(0,ZERO_ADD_2);

	 IapProgramByte(9,ZERO_ADD_REV_1);
	 IapProgramByte(0,ZERO_ADD_REV_2);

	 IapProgramByte(10,K1_ADD_1);
	 IapProgramByte(0,K1_ADD_2);

	 IapProgramByte(1,K2_ADD_1);
	 IapProgramByte(0,K2_ADD_2);

	 IapProgramByte(g_cIntegral,INTEGRAL);   //IapProgramByte(0,INTEGRAL);


	 IapProgramByte(100,AREA_1); //1.0平方米
	 IapProgramByte(0,AREA_2);


	 IapProgramByte(g_iRange,RANGE);

	  IapProgramByte(1,RANGEMIN1);
	  IapProgramByte(0,RANGEMIN2);


	 IapProgramByte(0,UNIT);
 
     IapProgramByte(0,ISCH4);

	 IapProgramByte(0,MAXOUT);

	 p = (char *)&g_fSum;
     IapProgramByte(*p,SUM1);
	 IapProgramByte(*(p+1),SUM2);
	 IapProgramByte(*(p+2),SUM3);
	 IapProgramByte(*(p+3),SUM4);

	  p = (char *)&g_fSum_biao;
     IapProgramByte(*p,SUM1_BIAO_1);
	 IapProgramByte(*(p+1),SUM1_BIAO_2);
	 IapProgramByte(*(p+2),SUM1_BIAO_3);
	 IapProgramByte(*(p+3),SUM1_BIAO_4);
     
	 p = (char *)&g_fSum_biao_ch4;
	 IapProgramByte(*p,SUM1_BIAO_CUN_1);
	 IapProgramByte(*(p+1),SUM1_BIAO_CUN_2);
	 IapProgramByte(*(p+2),SUM1_BIAO_CUN_3);
	 IapProgramByte(*(p+3),SUM1_BIAO_CUN_4);

	 IapEraseSector(START1);
	 IapEraseSector(START2);
	 IapProgramByte(10,START1);
	 IapProgramByte(10,START2);
   }
   
    if(g_iArea==0xffff && g_cIntegral==0xff && g_cUint==0xff && g_iRange==0xffff && g_iRangeMin==0xffff && g_cSecrit==0xff )
	  {
	     /*面积参数初始化*/
		temp1 =IapReadByte(AREA_1_2);
		temp2 =IapReadByte(AREA_2_2);
        g_iArea = temp1*100+temp2;

		/*积分系数初始化话*/
        g_cIntegral = IapReadByte(INTEGRAL_2);

		/*零点值出事化*/
        temp1 = IapReadByte(ZERO_ADD_1_2);
		temp2 = IapReadByte(ZERO_ADD_2_2);
		g_fZero = (temp1*100+temp2)/100;

		/*零点在回复时用的值*/
		temp1 = IapReadByte(ZERO_ADD_REV_1_2);
		temp2 = IapReadByte(ZERO_ADD_REV_2_2);
		g_fZero_rev = (temp1*100+temp2)/100;

		/*比例值初始化*/
        temp1 = IapReadByte(K1_ADD_1_2);
		temp2 = IapReadByte(K1_ADD_2_2);
		g_fK1 = (temp1*100+temp2)/1000;

		/*补偿系数初始化*/
        temp1 = IapReadByte(K2_ADD_1_2);
		temp2 = IapReadByte(K2_ADD_2_2);
		g_fK2 = (temp1*100+temp2)/100;

	    /*单位初始化*/
		g_cUint =  IapReadByte(UNIT_2);

		/*量程初始化 秒为单位*/
		g_iRange = IapReadByte(RANGE_2);
	    
		/*量程初始化 分钟为单位*/
		 temp1 = IapReadByte(RANGEMIN1_2);
		 temp2 = IapReadByte(RANGEMIN2_2);
		 g_iRangeMin = temp1*100+temp2;

//		 g_cSecrit = IapReadByte(SECRIT_2);

		 g_cWorkChange  = IapReadByte(ISCH4_2);

		 g_cMaxOut = IapReadByte(MAXOUT_2);

//		 g_cStart =  IapReadByte(START_2);
		 p = (char *)&g_fSum;
		 *p = IapReadByte(SUM1_2);
		 *(p+1) = IapReadByte(SUM2_2);
		 *(p+2) = IapReadByte(SUM3_2);
		 *(p+3) = IapReadByte(SUM4_2);
		 
//		 temp1 = IapReadByte(SUM1_2);
//		 temp2 = IapReadByte(SUM2_2);
//		 temp3 = IapReadByte(SUM3_2);
//		 temp4 = IapReadByte(SUM4_2);
//		 g_fSum = temp1+temp2*100.0+temp3*10000.0+temp4*1000000.0; 

		 p = (char *)&g_fSum_biao;
		 *p = IapReadByte(SUM2_BIAO_1);
		 *(p+1) = IapReadByte(SUM2_BIAO_2);
		 *(p+2) = IapReadByte(SUM2_BIAO_3);
		 *(p+3) = IapReadByte(SUM2_BIAO_4);
		 
//         temp1 = IapReadByte(SUM2_BIAO_1);
//		 temp2 = IapReadByte(SUM2_BIAO_2);
//		 temp3 = IapReadByte(SUM2_BIAO_3);
//		 temp4 = IapReadByte(SUM2_BIAO_4);
//		 g_fSum_biao = temp1+temp2*100.0+temp3*10000.0+temp4*1000000.0;

		 p = (char *)&g_fSum_biao_ch4;
		 *p = IapReadByte(SUM2_BIAO_CUN_1);
		 *(p+1) = IapReadByte(SUM2_BIAO_CUN_2);
		 *(p+2) = IapReadByte(SUM2_BIAO_CUN_3);
		 *(p+3) = IapReadByte(SUM2_BIAO_CUN_4);
//		 
//         temp1 = IapReadByte(SUM2_BIAO_CUN_1);
//		 temp2 = IapReadByte(SUM2_BIAO_CUN_2);
//		 temp3 = IapReadByte(SUM2_BIAO_CUN_3);
//		 temp4 = IapReadByte(SUM2_BIAO_CUN_4);
//		 g_fSum_biao_ch4 = temp1+temp2*100.0+temp3*10000.0+temp4*1000000.0;	

		 IapEraseSector(ZERO_ADD_1);
	     IapEraseSector(START);
		 IapProgramByte(0,SECRIT);
	     IapProgramByte(0,START);
	
		 IapProgramByte(0,ZERO_ADD_1);
		 IapProgramByte(0,ZERO_ADD_2);
	
		 IapProgramByte(9,ZERO_ADD_REV_1);
		 IapProgramByte(0,ZERO_ADD_REV_2);
	//
		 IapProgramByte(10,K1_ADD_1);
		 IapProgramByte(0,K1_ADD_2);
	
		 IapProgramByte(1,K2_ADD_1);
		 IapProgramByte(0,K2_ADD_2);
	
	//	 IapEraseSector(INTEGRAL);
		 IapProgramByte(g_cIntegral,INTEGRAL);   //IapProgramByte(0,INTEGRAL);
	
	//	 IapEraseSector(AREA_1);
		 IapProgramByte(100,AREA_1); //1.0平方米
		 IapProgramByte(0,AREA_2);
	
	//	 IapEraseSector(RANGE);
		 IapProgramByte(g_iRange,RANGE);
	
		  IapProgramByte(1,RANGEMIN1);
		  IapProgramByte(0,RANGEMIN2);
	
		 IapProgramByte(0,UNIT);
	 
	     IapProgramByte(0,ISCH4);
	
		 IapProgramByte(0,MAXOUT);
	
	      p = (char *)&g_fSum; 
	     IapProgramByte(*p,SUM1);
		 IapProgramByte(*(p+1),SUM2);
		 IapProgramByte(*(p+2),SUM3);
		 IapProgramByte(*(p+3),SUM4);
	
	      p = (char *)&g_fSum_biao;
	     IapProgramByte(*p,SUM1_BIAO_1);
		 IapProgramByte(*(p+1),SUM1_BIAO_2);
		 IapProgramByte(*(p+2),SUM1_BIAO_3);
		 IapProgramByte(*(p+3),SUM1_BIAO_4);

		  p = (char *)&g_fSum_biao_ch4;
		 IapProgramByte(*p,SUM1_BIAO_CUN_1);
		 IapProgramByte(*(p+1),SUM1_BIAO_CUN_2);
		 IapProgramByte(*(p+2),SUM1_BIAO_CUN_3);
		 IapProgramByte(*(p+3),SUM1_BIAO_CUN_4);

		 IapEraseSector(START1);
		 IapEraseSector(START2);
		 IapProgramByte(10,START1);
		 IapProgramByte(10,START2);
	  } 
   EA = 1;
}

void StrotPrect()
{
  IapEraseSector(SECRIT);
  IapProgramByte(g_cSecrit,SECRIT);
  IapProgramByte(g_cStart,START);
}

void Dateeprom()
{
   unsigned char temp1,temp2;//,temp3,temp4;
   char * p;
   IapEraseSector(ISCH4);

    temp1 = g_iArea/100;
	temp2 = g_iArea%100;
	
	IapProgramByte(temp1,AREA_1);
	IapProgramByte(temp2,AREA_2);

   g_fZero = g_fZero*100;
   temp1 = (int)g_fZero/100;
   temp2 = (int)g_fZero%100;
   IapProgramByte(temp1,ZERO_ADD_1);
   IapProgramByte(temp2,ZERO_ADD_2);
   g_fZero = g_fZero/100;

    g_fZero_rev = g_fZero_rev*100;
   temp1 = (int)g_fZero_rev/100;
   temp2 = (int)g_fZero_rev%100;
   IapProgramByte(temp1,ZERO_ADD_REV_1);
   IapProgramByte(temp2,ZERO_ADD_REV_2);
   g_fZero_rev = g_fZero_rev/100;
   
   g_fK1 = g_fK1*1000;
   temp1 = (int)g_fK1/100;
   temp2 = (int)g_fK1%100;
   IapProgramByte(temp1,K1_ADD_1);
   IapProgramByte(temp2,K1_ADD_2);
   g_fK1 = g_fK1/1000;

   g_fK2 = g_fK2*100;
   temp1 = (int)g_fK2/100;
   temp2 = (int)g_fK2%100;
   IapProgramByte(temp1,K2_ADD_1);
   IapProgramByte(temp2,K2_ADD_2);
   g_fK2 = g_fK2/100;

   IapProgramByte(g_cIntegral,INTEGRAL);

	IapProgramByte(g_iRange,RANGE);

	temp1 = g_iRangeMin/100;
	temp2 = g_iRangeMin%100;
 	IapProgramByte(temp1,RANGEMIN1);
	IapProgramByte(temp2,RANGEMIN2);

	IapProgramByte(g_cUint,UNIT);

    IapProgramByte(g_cWorkChange,ISCH4);

    IapProgramByte(g_cMaxOut,MAXOUT);


    p = (char *)&g_fSum;
	IapProgramByte(*p,SUM1);
	IapProgramByte(*(p+1),SUM2);
	IapProgramByte(*(p+2),SUM3);
	IapProgramByte(*(p+3),SUM4);
	/*
	temp1 = ((long)(g_fSum))%100L;
	temp2 = ((long)(g_fSum))%10000L/100L;
	temp3 = ((long)(g_fSum))%1000000L/10000L;
	temp4 = ((long)(g_fSum))%100000000L/1000000L;
	IapProgramByte(temp1,SUM1);
	IapProgramByte(temp2,SUM2);
	IapProgramByte(temp3,SUM3);
	IapProgramByte(temp4,SUM4);	 */
    
	p = (char *)&g_fSum_biao;
	IapProgramByte(*p,SUM1_BIAO_1);
	IapProgramByte(*(p+1),SUM1_BIAO_2);
	IapProgramByte(*(p+2),SUM1_BIAO_3);
	IapProgramByte(*(p+3),SUM1_BIAO_4) ;
	/*
	temp1 = ((long)(g_fSum_biao))%100L;
	temp2 = ((long)(g_fSum_biao))%10000L/100L;
	temp3 = ((long)(g_fSum_biao))%1000000L/10000L;
	temp4 = ((long)(g_fSum_biao))%100000000L/1000000L;
	IapProgramByte(temp1,SUM1_BIAO_1);
	IapProgramByte(temp2,SUM1_BIAO_2);
	IapProgramByte(temp3,SUM1_BIAO_3);
	IapProgramByte(temp4,SUM1_BIAO_4) ;	*/

	p = (char *)&g_fSum_biao_ch4;
	IapProgramByte(*p,SUM1_BIAO_CUN_1);
	IapProgramByte(*(p+1),SUM1_BIAO_CUN_2);
	IapProgramByte(*(p+2),SUM1_BIAO_CUN_3);
	IapProgramByte(*(p+3),SUM1_BIAO_CUN_4) ;
	/*
    temp1 = ((long)(g_fSum_biao_ch4))%100L;
	temp2 = ((long)(g_fSum_biao_ch4))%10000L/100L;
	temp3 = ((long)(g_fSum_biao_ch4))%1000000L/10000L;
	temp4 = ((long)(g_fSum_biao_ch4))%100000000L/1000000L;
	IapProgramByte(temp1,SUM1_BIAO_CUN_1);
	IapProgramByte(temp2,SUM1_BIAO_CUN_2);
	IapProgramByte(temp3,SUM1_BIAO_CUN_3);
	IapProgramByte(temp4,SUM1_BIAO_CUN_4) ;		 */

    if(g_cSecrit == 0) 
	  {
	    IapEraseSector(ISCH4_2);
		temp1 = g_iArea/100;
		temp2 = g_iArea%100;
		
		IapProgramByte(temp1,AREA_1_2);
		IapProgramByte(temp2,AREA_2_2);
	
	   g_fZero = g_fZero*100;
	   temp1 = (int)g_fZero/100;
	   temp2 = (int)g_fZero%100;
	   IapProgramByte(temp1,ZERO_ADD_1_2);
	   IapProgramByte(temp2,ZERO_ADD_2_2);
	   g_fZero = g_fZero/100;
	
	    g_fZero_rev = g_fZero_rev*100;
	   temp1 = (int)g_fZero_rev/100;
	   temp2 = (int)g_fZero_rev%100;
	   IapProgramByte(temp1,ZERO_ADD_REV_1_2);
	   IapProgramByte(temp2,ZERO_ADD_REV_2_2);
	   g_fZero_rev = g_fZero_rev/100;
	   
	   g_fK1 = g_fK1*1000;
	   temp1 = (int)g_fK1/100;
	   temp2 = (int)g_fK1%100;
	   IapProgramByte(temp1,K1_ADD_1_2);
	   IapProgramByte(temp2,K1_ADD_2_2);
	   g_fK1 = g_fK1/1000;
	
	   g_fK2 = g_fK2*100;
	   temp1 = (int)g_fK2/100;
	   temp2 = (int)g_fK2%100;
	   IapProgramByte(temp1,K2_ADD_1_2);
	   IapProgramByte(temp2,K2_ADD_2_2);
	   g_fK2 = g_fK2/100;
	
	   IapProgramByte(g_cIntegral,INTEGRAL_2);
	
		IapProgramByte(g_iRange,RANGE_2);
	
		temp1 = g_iRangeMin/100;
		temp2 = g_iRangeMin%100;
	 	IapProgramByte(temp1,RANGEMIN1_2);
		IapProgramByte(temp2,RANGEMIN2_2);
	
		IapProgramByte(g_cUint,UNIT_2);
	
	    IapProgramByte(g_cWorkChange,ISCH4_2);
	
	    IapProgramByte(g_cMaxOut,MAXOUT_2);

		p = (char *)&g_fSum;
		IapProgramByte(*p,SUM1_2);
		IapProgramByte(*(p+1),SUM2_2);
		IapProgramByte(*(p+2),SUM3_2);
		IapProgramByte(*(p+3),SUM4_2);
		/*
		temp1 = ((long)(g_fSum))%100L;
		temp2 = ((long)(g_fSum))%10000L/100L;
		temp3 = ((long)(g_fSum))%1000000L/10000L;
		temp4 = ((long)(g_fSum))%100000000L/1000000L;
		IapProgramByte(temp1,SUM1_2);
		IapProgramByte(temp2,SUM2_2);
		IapProgramByte(temp3,SUM3_2);
		IapProgramByte(temp4,SUM4_2);  */

		p = (char *)&g_fSum_biao;
		IapProgramByte(*p,SUM2_BIAO_1);
		IapProgramByte(*(p+1),SUM2_BIAO_2);
		IapProgramByte(*(p+2),SUM2_BIAO_3);
		IapProgramByte(*(p+3),SUM2_BIAO_4);
		/*
		temp1 = ((long)(g_fSum_biao))%100L;
		temp2 = ((long)(g_fSum_biao))%10000L/100L;
		temp3 = ((long)(g_fSum_biao))%1000000L/10000L;
		temp4 = ((long)(g_fSum_biao))%100000000L/1000000L;
		IapProgramByte(temp1,SUM2_BIAO_1);
		IapProgramByte(temp2,SUM2_BIAO_2);
		IapProgramByte(temp3,SUM2_BIAO_3);
		IapProgramByte(temp4,SUM2_BIAO_4); */

		p = (char *)&g_fSum_biao_ch4;
		IapProgramByte(*p,SUM2_BIAO_CUN_1);
		IapProgramByte(*(p+1),SUM2_BIAO_CUN_2);
		IapProgramByte(*(p+2),SUM2_BIAO_CUN_3);
		IapProgramByte(*(p+3),SUM2_BIAO_CUN_4);
		/*
		temp1 = ((long)(g_fSum_biao_ch4))%100L;
		temp2 = ((long)(g_fSum_biao_ch4))%10000L/100L;
		temp3 = ((long)(g_fSum_biao_ch4))%1000000L/10000L;
		temp4 = ((long)(g_fSum_biao_ch4))%100000000L/1000000L;
		IapProgramByte(temp1,SUM2_BIAO_CUN_1);
		IapProgramByte(temp2,SUM2_BIAO_CUN_2);
		IapProgramByte(temp3,SUM2_BIAO_CUN_3);
		IapProgramByte(temp4,SUM2_BIAO_CUN_4);	*/
	  }   
}

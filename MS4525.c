#include "SPD6000.h"
#include "intrins.h"
#include "math.h"
#include "global_var.h"
#include "MS4525.h"

#define SMOTH_NUMBER 5

#define ZER0_SIZE 3

#define INTEGRAL_MAX 19


/*向传感器读取压差值*/
unsigned char MS4525DO_read(unsigned char * p,unsigned char* temperature)
{
  unsigned char error = 0;
  SS2= 0;
  SCL = 1; //SDP600 系列传感器(从机) 可以拉低SCL线来强制主机进入等待状态。传感器通过释放SCL线指示内部处理已完成
  *p = SPI_ReadByte();       //读取传感器第一个字节数据
  *(p+1) = SPI_ReadByte();  //读取传感器数据第二个字节数据
  *temperature = SPI_ReadByte();
  *(temperature+1) = SPI_ReadByte();
  SS2 = 1;
    if((((*p)&0xc0) == 0xc0) || (((*p)&0x40) == 0x40))
	   {
	      error = 1;
	   }
	   *p = (*p)&0x3f;
   return error;
}

 void data_read_4525(Ms4515* date)
 {
    int dat1;
	unsigned int temper;
	if(MS4525DO_read((unsigned char*)&dat1,(unsigned char*)&temper) == 0)
	{
	      if(dat1<=1638)
		    {
			  dat1 = 1638;
	        }
	      if(dat1>=14746)
            {
		      dat1 = 14746;
	        }
	     date->pressure = (dat1)*0.00789-12.928;//  date->pressure = ((dat1)*0.07751938-635)-g_fZero;
		 if(date->pressure< 0.0)
		   {
		     date->pressure = -date->pressure;
		   }
		   temper = temper/32;
		date->temperature = temper*0.0977-50;
	}
 }
 

float date_Smooth_4525(float *tmp)
 {
   static float pressre[SMOTH_NUMBER] = {0.0,0.0,0.0};
   float sum = 0;
   char j=0;
   static char i = 0;

  Ms4515 date1;
     data_read_4525(&date1);
	 *tmp = date1.temperature;
	 pressre[i] = date1.pressure;
	 i++;
	 if(i == SMOTH_NUMBER)
	   {
	     i= 0;
	   }
	  for(j=0;j<SMOTH_NUMBER;j++)
	   {
	     sum = sum+pressre[j];
	   }
	   sum = sum/SMOTH_NUMBER;

	   return sum;
 }
	 
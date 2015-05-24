#include "SPD6000.h"
#include "intrins.h"
#include "math.h"
#include "global_var.h"
#include "ch4.h"
#include "ms4525.h"

#define SMOTH_NUMBER 3

//#define ZER0_SIZE 3

#define INTEGRAL_MAX 19

typedef enum{
ACK = 0,
NO_ACK = 1
}etI2cAck;


/*简单的延时函数*/
void SomeNOP()
{
  int i;
  for(i=0;i<12;i++)
  {
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  }
}



/*通过I2C总线向传感器读出一个字节数据函数*/
unsigned char SPI_ReadByte()
{
  unsigned char mask ,rxByte = 0;
  SCL = 1;
  SomeNOP();
  for(mask=0x80;mask>0;mask>>=1)  //读八次，每次只读一位
  {
    SCL = 0;
	SomeNOP();
	SomeNOP();
	if(SDA == 1)
	 rxByte = (rxByte|mask);
	 SCL = 1;
	 SomeNOP();
  }
  SomeNOP();
  return rxByte;
}

/*向传感器读取压差值*/
unsigned char MS4515DO_read(unsigned char * p,unsigned char* temperature)
{
  unsigned char error = 0;
 // EA = 0; 
  SS= 0;
  SCL = 1; //SDP600 系列传感器(从机) 可以拉低SCL线来强制主机进入等待状态。传感器通过释放SCL线指示内部处理已完成
  *p = SPI_ReadByte();       //读取传感器第一个字节数据
  *(p+1) = SPI_ReadByte();  //读取传感器数据第二个字节数据
  *temperature = SPI_ReadByte();
  *(temperature+1) = SPI_ReadByte();
  SS = 1;
 // EA = 1;
    if((((*p)&0xc0) == 0xc0) || (((*p)&0x40) == 0x40))
	   {
	      error = 1;
	   }
	   *p = (*p)&0x3f;
   return error;
}

 void data_read(Ms4515* date)
 {
    int dat1;
	int temp;
	unsigned int temper;
	if(MS4515DO_read((unsigned char*)&dat1,(unsigned char*)temper) == 0)
	{
	      if(dat1<=1638)
		    {
			  dat1 = 1638;
	        }
	      if(dat1>=14746)
            {
		      dat1 = 14746;
	        }
	    date->pressure = ((dat1)*0.07751938-635)-g_fZero;
		 temp = date->pressure*10;
		 date->pressure = temp/10;
		 if(date->pressure< 0.1)
		   {
		     date->pressure = 0.0;
		   }
		  if(date->pressure>508.0)
		    {
			  date->pressure = 508.0;
			}
			temper = temper/32;
		date->temperature = temper*0.0977-50;
	}
 }

 float date_Smooth()
 {
    
   static float pressre[SMOTH_NUMBER] = {0.0,0.0,0.0};
   static float sum_old = 0;
   float ret;
   float sum = 0;
   char j=0;
   static char i = 0;

  Ms4515 date1;
     data_read(&date1);
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
	   ret = ((INTEGRAL_MAX+1-g_cIntegral)*sum+g_cIntegral*sum_old)/(INTEGRAL_MAX+1);
	   sum_old = ret;
	   return ret;
 }

 /***风速值******/
float Wid_Speed(float *p_pase,float * tempter)
 {
        
     float windSpeed; //最后的流速
	 int pressure; // 风速的差压值
	 float ch4;  //甲烷值
//	 float tmpter;	  //温度值
//	 float p_pase;	  //绝压值
	 int temp = 0;
	 #ifndef _DEBUG_
	  pressure = date_Smooth();
	  ch4= read_ch4();
	  if(ch4<0.001)
	  {
	    ch4 = 0.0;
	  }
	  *p_pase = date_Smooth_4525(tempter);
	 //  *p_pase = 85.0;
	  // *tempter = 26.5;
	 #endif
	 
	 windSpeed = (sqrt(pressure*2/((3.458-0.01533*ch4)*(*p_pase)/(273.15+*tempter))))*g_fK1*g_fK2;

      temp = windSpeed*10;
	  windSpeed = (float)temp/10;
	  if(windSpeed < 0.01)
	    {
		  windSpeed = 0.0;
		}
	  return windSpeed ;      
 }





 

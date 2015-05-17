#include "key.h"
#include "display.h"
#include <reg52.h>

#define PRESSURE        10  //ѹ��ֵ	H  ��С����
#define WIND_SPEED      0x01  //����ֵ	B  ��С����
#define WIND_SPEED_ZERO 0x02  //��У�������  C	 ��С����
#define WIND_SPEED_RATE 0x03  //У׼���������� D ��С����
#define RENEW           0x04  //����ϵ��	 E	��С����
#define WIND_SPEED_RATE_A 0x05  //����ϵ��
#define SET_AREA        0x07  //������趨	 F	 ��С����
#define WIND_FLUX       0x00  //����ֵ	 A ��С����
#define WIND_FLUX_MIN   0x08  //��λѡ��  L
#define ZK_SET          0X06  //zero k�ָ���ʼ�궨ֵ  u
#define SET_RANGE       0X09  //���� ��5����ÿ��Ϊ10   n
#define PROTECT         13  //���뱣������2
#define PROTECT1        14  //���뱣������1
#define ENCRYPEION      11    //
#define RETURN          12

sbit  add1=P0^0; 
sbit  sub1=P0^1;
sbit  sure1 =P3^3;
sbit  func1 =P3^4 ;

unsigned char key()
{
   unsigned char ret =0;
   if( add1 == 1)
     {	
	    g_iLed_light = 0;
	    ret = KEY_ADD;
	 } 
  
    if(sub1 == 1)
	{
	   g_iLed_light = 0;
	   ret = KEY_SUB;
	}

	if(sure1 == 1)
	{
	  g_iLed_light = 0;
	  ret = KEY_SURE;
	}

	if(func1 == 1)
	{
	  g_iLed_light = 0;
	  ret = KEY_FUNC;
	}

	 return ret;
}

unsigned int key_AddSub(unsigned int number,unsigned char point,unsigned char start_x,unsigned char start_y,unsigned int max)
{
   	  if(key() == KEY_ADD)
	    {
		   g_iProtect = 0;
		   number++;
		   if(number>max)
		     {
			   number = 0;
			 }
		   disylay_mun(number,point,start_x,start_y);
		}
	   if(key() == KEY_SUB)
	    {
		  number--;
		  g_iProtect = 0;
		  if(g_cFunc != 5)
		  {
			  if(number ==65535)
			   {
			     number = max;
			   }
		   }
		   else
		   {
		      if(number ==0)
			   {
			     number = max;
			   }
		   }
		  disylay_mun(number,point,start_x,start_y);
		}
		
		return number;

} 

void key_release()
{
    while(add1 || func1 || sure1 || sub1)
	{
	  g_iProtect = 0; 
	}
}
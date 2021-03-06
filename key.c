#include "key.h"
#include "display.h"
#include <reg52.h>

#define PRESSURE        10  //压力值	H  有小数点
#define WIND_SPEED      0x01  //风速值	B  有小数点
#define WIND_SPEED_ZERO 0x02  //调校风速零点  C	 有小数点
#define WIND_SPEED_RATE 0x03  //校准风速灵敏度 D 有小数点
#define RENEW           0x04  //积分系数	 E	无小数点
#define WIND_SPEED_RATE_A 0x05  //补偿系数
#define SET_AREA        0x07  //截面积设定	 F	 无小数点
#define WIND_FLUX       0x00  //风量值	 A 有小数点
#define WIND_FLUX_MIN   0x08  //单位选择  L
#define ZK_SET          0X06  //zero k恢复初始标定值  u
#define SET_RANGE       0X09  //量程 有5档，每档为10   n
#define PROTECT         13  //密码保护界面2
#define PROTECT1        14  //密码保护界面1
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
		    g_iProtect = 0;
		    number--;
		    if(number == 65535)
			   {
			     number = max;
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

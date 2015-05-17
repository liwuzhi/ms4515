#include "display.h"
#include "ziku.h"
#include "key.h"
#include "storage.h"
#include "spd6000.h"
#include "MS4525.h"
#include "pwm.h"
#include "CH4.h"
#include "eeprom.h"

#define POINT_0 0
#define POINT_1 1
#define POINT_2 2
#define POINT_3 3

#define ZERO_ADD_REV_1 0x6fe1
#define ZERO_ADD_REV_2 0x6fe2

#define READ_TIME 10

sbit  OUT2  = P3^7;



void delay( int x)
{
    int y,z;
   for(y=x;y>0;y--)
    {
	   for(z=100;z>0;z--)
	    {
		}
	}
}

void key_delay()
{
   static char num;
   if(key() != 0)
     {
	    num++;
		if(num > 20)
		  {
		    num = 11;
		  }
	   if(num >10)
	     {
		   delay(1);
		 }
		 else
		 {
		   delay(300);
		 }
	 }
	 else
	 {
	   num =0;
	 }
   if(num >10)
     {
	   delay(10);
	 }
	 else
	 {
	   delay(1000);
	 }
}

unsigned char return_Main()
{
            if(g_iProtect > 900)
			   {
			      g_cFunc = 0;
			      return 1;
			   }
			   else
			   {
			      return 0;
			   }
}
void disylay_mun(unsigned int num,char point,char start_x,char start_y)
{
  unsigned char temp_num[5];
  unsigned char temp[6]={0,0,0,0,0,0};
  unsigned char i=0,j=0;
  temp_num[0] = num/10000+'0';
  temp_num[1] = num%10000/1000+'0';
  temp_num[2] = num%1000/100+'0';
  temp_num[3] = num%100/10+'0';
  temp_num[4] = num%10+'0';
   temp[5-point] = '.';
  for(i=0;i<6;i++)
  {
     if(0 == temp[i])
	 {
	    temp[i] = temp_num[j];
		j++;
	 }
  }
  for(i=0;i<4-point;i++)
	 {
	   if(temp[i] == '0')
	     {
		   temp[i] = ' ';
		 }
		 else
		 {
		   break;
		 }
	 }
    if(point>0)
	{
	   Display_Onechar(start_x*8,start_y*2,temp[0],0);
       Display_Onechar((start_x+1)*8,start_y*2,temp[1],0);
	   Display_Onechar((start_x+2)*8,start_y*2,temp[2],0);
	   Display_Onechar((start_x+3)*8,start_y*2,temp[3],0);
	   Display_Onechar((start_x+4)*8,start_y*2,temp[4],0);
	   Display_Onechar((start_x+5)*8,start_y*2,temp[5],0);
	}
	else
	{
	   Display_Onechar(start_x*8,start_y*2,temp[0],0);
	   Display_Onechar((start_x+1)*8,start_y*2,temp[1],0);
	   Display_Onechar((start_x+2)*8,start_y*2,temp[2],0);
	   Display_Onechar((start_x+3)*8,start_y*2,temp[3],0);
	   Display_Onechar((start_x+4)*8,start_y*2,temp[4],0);
	}
}

void display_stringChar(unsigned char start_x,unsigned char start_y,char* s)
{
      unsigned char i=0;
   	  while(*s != '\0')
	  {
	     Display_Onechar((start_x+i)*8,start_y*2,*s,0);
		 i++;
		 s++;
	  }	  
}

void display_stringChinese(unsigned char start_x,unsigned char start_y,unsigned char** s)
{
  unsigned char i=0;
  for(i=0;i<5;i++)
  {
   Display_Graphic(start_x*8+i*16,start_y*2,16,16,*s,0);
   s++;
   }
}

void display_sum(long sum,char start_x,char start_y)
{
   unsigned char temp[9] = {0,0,0,0,0,0,0,0};
   char i;
   if(sum>999999999)
   {
     sum = 999999999;
   }
   temp[0] = sum/100000000L+'0';
   temp[1] = sum%100000000L/10000000L+'0';
   temp[2] = sum%10000000L/1000000L+'0';
   temp[3] = sum%1000000L/100000L+'0';
   temp[4] = sum%100000L/10000L+'0';
   temp[5] = sum%10000L/1000L+'0';
   temp[6] = sum%1000L/100L+'0';
   temp[7] = sum%100L/10L+'0';
   temp[8] = sum%10L+'0';

   for(i=0;i<8;i++)
	 {
	   if(temp[i] == '0')
	     {
		   temp[i] = ' ';
		 }
		 else
		 {
		   break;
		 }
	 }
   for(i=0;i<9;i++)
   {
      Display_Onechar((start_x+i)*8,start_y*2,temp[i],0);
   }
}
 
void read_senser(float* p_flux,float* p_pase,float ch4,float* tmpter)
{
        float ch4_temp;
		   ch4_temp = ch4;
		   if(ch4_temp<0.001)
		      {
			     ch4_temp= 0.0;
			  }
           *p_pase = date_Smooth_4525(tmpter); //读取绝压值
	       if(g_cUint == 0)
		   {
		    if(g_cWorkChange == 1)	//工况
			{
		      *p_flux =  Wid_Speed()*g_iArea/10000;
			}
			else  //标况
			{
			 *p_flux =  Wid_Speed()*g_iArea/10000*(*p_pase/101.325)*(293/(273+*tmpter));
			}
			if(*p_flux>g_iRange)
			  {					   
			     *p_flux = g_iRange;
			  }
		  }
		  else
		  {
		    if(g_cWorkChange == 1)
			{
		      *p_flux =  Wid_Speed()*g_iArea/10000*60;
			}
			else
			{
			  *p_flux =  Wid_Speed()*g_iArea/10000*60*(*p_pase/101.325)*(293/(273+*tmpter));
			}
		    if(*p_flux>g_iRangeMin)
			  {
			     *p_flux = g_iRangeMin;
			  } 
		 }
}
   


void read_Maxout()
{
   float p_flux;
   float p_pase;
   float ch4;
   static char flag=0;
   static char flag1=0;
   float temper;

   if(g_iTime < 10 && flag1 ==0)	//每一小时保存一次
		{
		  if(g_cMaxOut == 0 || g_cMaxOut == 2)
		   {
		    Dateeprom();
		   }
		   flag1 = 1;
		}
		else if(g_iTime > 10)
		 {
		   flag1 = 0;
		 }

  // if(g_iTimebase <= 10 && flag == 0 )
   if(g_iTime%57 < 20 && flag ==0 )	//每一分钟计算一次
   {
        flag = 1;
        ch4 = read_ch4();
		if(ch4 < 0.001)
		  {
		     ch4 =0.0;
		  }
           p_pase = date_Smooth_4525(&temper); //读取绝压值
		  p_flux = Wid_Speed()*g_iArea/10000;
	       
		 if(g_cUint == 0)
		  {
			 g_fSum = g_fSum + p_flux;
			 g_fSum_biao = g_fSum_biao +  p_flux*(p_pase/101.325)*(293/(273+temper));
			 g_fSum_biao_ch4 = g_fSum_biao_ch4 + p_flux*(p_pase/101.325)*(293/(273+temper))*ch4/100;
		  }
		  else
		  {
		      g_fSum = g_fSum + p_flux*60 ;
			  g_fSum_biao = g_fSum_biao + p_flux*60*(p_pase/101.325)*(293/(273+temper));
			  g_fSum_biao_ch4 = g_fSum_biao_ch4 + p_flux*60*(p_pase/101.325)*(293/(273+temper))*ch4/100;
		  }
	}
	else if(g_iTime%57 > 20)
	{
	   flag = 0;
	}
} 	
/*
  显示压力界面
*/
unsigned char display_Preassure()
{
   	unsigned char key_num;
	unsigned int preassure;
    code unsigned char* chinese[] ={font_13,font_14,font_00,font_00,font_00};
    code char arr[] = {'p','a','\0'};

    preassure = date_Smooth();
	display_stringChinese(0,0,chinese);
	display_stringChar(6,1,arr);
	disylay_mun(preassure,0,0,1); 

	while(1)
	{
	    if(g_cMaxOut ==0 || g_cMaxOut ==2)
	    read_Maxout();
		key_num = key();
		if(key_num == KEY_FUNC)
		{
	    	g_cFunc++;
			key_release();
	    	return 0;
		}
		#ifdef _DEBUG_
		preassure = key_AddSub(preassure,1,0,1,10000);
		date.pressure = ((float)preassure)/10; 
		#else
		if((g_iTimebase%READ_TIME) == 0)
		  {
		   preassure = date_Smooth();
		   disylay_mun(preassure,0,0,1);
		  }
		#endif
		
		key_delay();
	    if(return_Main())
		{
			return 0;
		}
	}
      return 0;
}

unsigned char display_Area()
{
   	unsigned char key_num;
	unsigned int area;
	unsigned int temp_area;
   code unsigned char* chinese[] ={font_11,font_12,font_07,font_00,font_00,font_00};	//截面积
   code unsigned char* chinese2[] ={font_22,font_23,er,font_00,font_00};	  //密码2
   code char arr[] = {'c','m',60,'\0'};
       area = g_iArea;
	   temp_area = area;
	display_stringChinese(0,0,chinese);
	display_stringChar(5,1,arr);
	disylay_mun(area,0,0,1); 
	while(1)
	{
	    if(g_cMaxOut ==0 || g_cMaxOut ==2)
	    read_Maxout();
		key_num = key();
		if(key_num == KEY_FUNC)
		{
	    	g_cFunc++;
			key_release();
	    	return 0;
		}
        area = key_AddSub(area,0,0,1,10000);
		if(key_num == KEY_SURE)
		{
		   g_iProtect = 0;
		   g_iArea = area;
		   Clean_Display(0,0,128,64,0);
		   if(display_Protect1(chinese2,10) == 0)
		     {
			    g_iArea = temp_area;
				area = g_iArea;
			 }
			 else
			 {
			   Dateeprom();
			 }
		   Clean_Display(0,0,128,64,0);
		   display_stringChinese(0,0,chinese);
		   display_stringChar(5,1,arr);
		   disylay_mun(area,0,0,1);
		}
		key_delay();
	    if(return_Main())
		{
			return 0;
		}
	//	disylay_mun(100,2,0,2);
	}
}

void mian1_chinese()
{
  unsigned char* chineseWork[] ={gong,kuang,font_00,font_00,font_00};	  //工况
   unsigned char* chineseStandar[] ={biao,kuang,font_00,font_00,font_00}; //标况
  //code unsigned char* chineseFlux[] ={font_38,font_02,font_37,font_00,font_00};	 //流量	 此处应改成工况
  code unsigned char* chinesePase[] = {font_13,font_14,font_37,font_00,font_00}; //压力
  code unsigned char* chineseCH4[] = {jia,wan,font_37,font_00,font_00}; //甲烷
  //code unsigned char*  chineseMin[] = {font_32,font_33,font_34,font_35,font_36};//流量变送器
  //unsigned char * code chineseisch4[] = {chun,font_02,font_37,font_00,font_00};	 //纯量	 此处应改成标况
  unsigned char *code chineseTmp[] = {font_41,font_42,font_00,font_00,font_00};	 //温度

//   code char arrm3[] = {'m',59,'\0'};

   code char arr[] = {':','\0'};
   code char arrS[] = {'m',59,'/','s','\0'};	 //m3/s
   code char arrMin[] = {'m',59,'/','m','i','n','\0'}; //m3/min
   code char arrKPa[] = {'K','P','a','\0'};
 //  code char arrERR[] = {' ','-','-',' ',' ',' ',' ','\0'};
   code char arrch4[]	= {'%','\0'};
   code char arrTmper[] = {34,'C','\0'};
	 
    if(g_cWorkChange == 1)
	{ 
	  display_stringChinese(0,0,chineseWork);	 //显示中文流量
	}
	else
	{
	  display_stringChinese(0,0,chineseStandar);	
	}
	/*显示流量单位*/
	  if(g_cUint == 0)
	  {
	   	display_stringChar(12,0,arrS);
	  }
	  else
	  {
	    display_stringChar(10,0,arrMin);
	  }

	display_stringChinese(0,1,chinesePase);	 //显示中文压力
	display_stringChar(13,1,arrKPa);         //显示绝压单位 

   	display_stringChinese(0,2,chineseCH4);	//显示甲烷中文两个字
	display_stringChar(15,2,arrch4);	   //显示甲烷中的%
	//display_stringChar(5,2,arrERR);		   //显示甲烷中的--

	display_stringChinese(0,3,chineseTmp);//显示温度字样
	display_stringChar(4,3,arr);
	display_stringChar(14,3,arrTmper);
}

void mian1_num(char i)
{
   float pase;
   float flux;
   float ch4;
   float tmper;
   static float flux_sum =0.0;
   static float flux_sum_old =0.0;
   static char flux_num_1 = 0;
  // static char first_flag = 1;
   code char arrERR[] = {' ','-','-',' ',' ',' ',' ','\0'};
   code char arr[] = {':','\0'};

   	                ch4= read_ch4();
				    read_senser(&flux,&pase,ch4,&tmper);
			        disylay_mun(tmper*10,POINT_1,8,3);
						
					if(flux_sum_old<0.01 && flux_sum_old>-0.01)
					{
					  // flux_sum_old = flux;
					}
									 
				   if(pase<1.0)
				   {
				      display_stringChar(5,1,arrERR);	//显示--
					  CR = 0;                         //PCA timer start run
		              EPCAI = 0;
					  OUT2 = 1;
				   }
				   else
				   {
			          disylay_mun(pase*10,POINT_1,7,1);	 //显示绝压的数据
				      CR = 1;                         //PCA timer start run
		              EPCAI = 1;
				     pca_set2(pase);//设置绝压的输出脉冲
				   }
				   
				   /*设置甲烷的数据*/
				   if(ch4 >= 0.0 && ch4 < 100.001)
					{
					    disylay_mun(ch4*10,POINT_1,9,2);	//显示甲烷的百分比
					}
					else
					{
						display_stringChar(5,2,arrERR);	//显示--
					}
				  if(i == 0)
				   {
                    flux_num_1++;
				    flux_sum =flux_sum + flux;
				   }
				  if(40 == flux_num_1 || i == 1)
					{
					 if(i == 1)
					 {
					    flux = flux_sum_old ;
					 }
					 else
					 {
					  flux_num_1 = 0;
					  flux = flux_sum/40;
					  flux_sum_old = flux;
					  flux_sum = 0.0;
					 }
					 
					 if(g_cUint == 0)	  //在秒单位下的流量显示
					   {
					    disylay_mun(flux*100,POINT_2,6,0);
					    g_cOut1[0] = (65536-500000/(200+800.0/g_iRange*((float)flux))+3)/256; 
					    g_cOut1[1] = (65536-500000/(int)(200+800.0/g_iRange*(float)flux)+3)%256;
					   }
					   else
					   {
	  			         if(flux>g_iRangeMin)
						  {
						     flux = g_iRangeMin;
						  }
						   if(flux<100)
						    {
						     disylay_mun(flux*100,POINT_2,4,0);
							 display_stringChar(4,0,arr);
							}
							else
							{
							 if(flux>999.9)
							   {
							     flux = 999.9;
							   }
							  disylay_mun(flux*10,POINT_1,4,0);
							  display_stringChar(4,0,arr);
							}
							g_cOut1[0] = (65536-500000/(200+800.0/g_iRangeMin*flux)+3)/256;  
					        g_cOut1[1] = (unsigned int)(65536-500000/(200+800.0/g_iRangeMin*flux)+3)%256;
					   }	 
					}

}

void mian2_chinese()
{

   unsigned char* chinese[] ={zong,font_02,font_00,font_00,font_00};	  //总量
   unsigned char* chineseWork[] ={gong,kuang,font_00,font_00,font_00};	  //工况
   unsigned char* chineseStandar[] ={biao,kuang,font_00,font_00,font_00}; //标况
   unsigned char* chineseStandar_cun[] ={biao,chun,font_00,font_00,font_00}; //	 标纯
   unsigned char* chineseClear[] ={qing,font_03,font_00,font_00,font_00};	  //清零选择
   code char arrOFF[] = {'O','F','F',' ','\0'};
   code char arrON[] =  {'O','N',' ',' ','\0'};
   code char arrm3[] = {'m',59,'\0'};
   code char arr[] = {':','\0'};
      
        Clean_Display(0,0,128,64,0);  
		display_stringChinese(0,0,chinese);	//总量
		display_stringChar(4,0,arr); //总量后面的：			
		if(g_cMaxOut == 1)
		 {
		     display_stringChar(7,0,arrOFF);
		 }
		else if(g_cMaxOut == 0)
		 {
			 display_stringChar(7,0,arrON);
		 }
	    else
		 {
			 display_stringChinese(7,0,chineseClear);
		 }
		 /*显示工况和其单位*/
		display_stringChinese(0,1,chineseWork);
        display_stringChar(14,1,arrm3);
        display_stringChar(4,1,arr);

		/*显示标况和其单位*/
		display_stringChinese(0,2,chineseStandar);
        display_stringChar(14,2,arrm3);
        display_stringChar(4,2,arr);

		/*显示纯标和其单位*/
		display_stringChinese(0,3,chineseStandar_cun);
        display_stringChar(14,3,arrm3);
		display_stringChar(4,3,arr);
}


unsigned char display_Main()
{
   unsigned char key_num;
   char flag=0;
   char flag_ret1 = 1;
   char flag_ret2 = 1;
   mian1_chinese();
   mian1_num(1);
   
	while(1)
	{   
	    if(g_cMaxOut ==0 || g_cMaxOut ==2)
		{
			read_Maxout();
		}
		key_num = key();	//检查按键
				if(key_num == KEY_FUNC)
				{
				   if(g_iProtect>=900)	 //在第一次按下时跳转到密码一界面，不然跳转跳转到正常的下一个界面
				   {
					 g_cFunc = 15;
				   }
				   else
				   {
			    	 g_cFunc++;
				   }
					key_release();	//按键释放
			    	return 0;
				}
	    if(g_iTime%30 < 20 )	 //在前20s显示第一种界面
		{
		        if(flag_ret1 == 1)
				  {
				    Clean_Display(0,0,128,64,0);
					mian1_chinese();
					mian1_num(1);
				  }
				 flag_ret1 = 0;
				 flag_ret2 = 1;

			    
				
				   
				/*读取绝压和差压的传感器并显示*/
				// if(flag == 0 && (g_iTimebase <= 5 || (g_iTimebase >=10 && g_iTimebase<=15)) )
				if(0 == flag && g_iTimebase <= 5  )
				 {
				    flag = 1;
					mian1_num(0);
				 }
				 else if(g_iTimebase>5)
				  {
				     flag = 0 ;
				  }
		}
		else
		{
		  if(flag_ret2 == 1)
			{
			  Clean_Display(0,0,128,64,0);
	          mian2_chinese();			    			
			}
			flag_ret1 = 1;
			flag_ret2 = 0;
			if(0 == flag && g_iTimebase <= 5  )
			{
				    flag = 1;
					display_sum(g_fSum,5,1); //显示工况累积值
					display_sum(g_fSum_biao,5,2); //显示工况累积值
					display_sum(g_fSum_biao_ch4,5,3);
					//display_sum(12345678,6,3);

			}
			else if(g_iTimebase>5)
			{
				     flag = 0 ;
			}   		  
		}
	}
}

unsigned char display_WindSpeed()
{
   	unsigned char key_num;
	float windSpeed;
	unsigned int play;
    code unsigned char* chinese[] ={font_38,font_04,font_00,font_00,font_00};  //流速
    code char arr[] = {'m','/','s','\0'};

	display_stringChinese(0,0,chinese);
	display_stringChar(6,1,arr);
	windSpeed = Wid_Speed();
	play = windSpeed*10;
	disylay_mun(play,1,0,1); 

	while(1)
	{
	    if(g_cMaxOut ==0 || g_cMaxOut ==2)
	    read_Maxout();
		key_num = key();
		if(key_num == KEY_FUNC)
		{
	    	g_cFunc++;
			key_release();
	    	return 0;
		}

	    if((g_iTimebase%READ_TIME) == 0)
		 {
		    windSpeed = Wid_Speed();
			play =windSpeed*10;
			disylay_mun(play,POINT_1,0,1);
		 }
		key_delay();
	    if(return_Main())
		{
			return 0;
		}
	}
}

unsigned char display_WindSpeedZero()
{
    char i;
	char error;
   	unsigned char key_num;
	float windSpeed;
    int pressure = 0;
	unsigned int temper;
	float pressure_sum = 0;
    int play;
    code unsigned char* chinese[] ={font_03,font_24,font_05,font_06,font_00};	  //零点校准
	code unsigned char* chinese2[] ={font_22,font_23,er,font_00,font_00};	  //密码2
    code char arr[] = {'m','/','s','\0'};

	display_stringChinese(0,0,chinese);
	display_stringChar(6,1,arr);
	windSpeed = Wid_Speed();
	play = 	(int)(windSpeed*10);
	disylay_mun(play,1,0,1);  
	while(1)
	{
	    if(g_cMaxOut ==0 || g_cMaxOut ==2)
	    read_Maxout();
		key_num = key();
		if(key_num == KEY_FUNC)
		{
	    	g_cFunc++;
			key_release();
	    	return 0;
		}
		if(key_num == KEY_SURE)
		  {
		    g_iProtect = 0;
		    key_release();
		   Clean_Display(0,0,128,64,0);
		   if(display_Protect1(chinese2,10) == 1 )
		   {
		          i =0;
				while(i<5)
				   {
				       error = MS4515DO_read((unsigned char*)&pressure,(unsigned char*)&temper);
				//	   MS4515DO_read((unsigned char*)&dat1,(unsigned char*)temper) == 0
					    if( error == 0)
						{
						   i++;
						  	if(pressure<=1638)
						    {
							  pressure = 1638;
					        }
					      if(pressure>=14746)
				            {
						      pressure = 14746;
					        }
						 pressure_sum =pressure_sum+pressure;
						 
						}
			//			disylay_mun(i,0,7,2);
						delay(500);
				   }   
				   pressure_sum = pressure_sum/5;
				   g_fZero = pressure_sum*0.07751938-635;
				   g_fZero_rev = g_fZero;
				   Dateeprom(); 
		   }
		   Clean_Display(0,0,128,64,0);
		   display_stringChinese(0,0,chinese);
		   display_stringChar(6,1,arr);
		   	windSpeed = Wid_Speed();
        	play = 	(int)(windSpeed*10);
        	disylay_mun(play,1,0,1);
		
		  }
		if((g_iTimebase%READ_TIME) == 0)
		  {
		    windSpeed = Wid_Speed();
			play = 	(int)(windSpeed*10);
			disylay_mun(play,1,0,1);
//			disylay_mun(g_fZero*100,2,0,2);   //调试用，显示零点值为多少
		  }
		key_delay();
	    if(return_Main())
		{
			return 0;
		}
	}
}

unsigned char display_WindSpeedRate()
{
   	unsigned char key_num;
	float windSpeed;
	unsigned int play;
	float k1;
   code unsigned char* chinese[] ={font_26,font_27,font_05,font_06,font_00};	  //精度校准
   code unsigned char* chinese2[] ={font_22,font_23,er,font_00,font_00};	  //密码2
   code char arr[] = {'m','/','s','\0'};
     k1=g_fK1;
	display_stringChinese(0,0,chinese);
	display_stringChar(6,1,arr);
	windSpeed = Wid_Speed();
	play = 	(int)(windSpeed*10);
	disylay_mun(play,1,0,1); 
	while(1)
	{
	    if(g_cMaxOut ==0 || g_cMaxOut ==2)
	    read_Maxout();
		key_num = key();
		if(key_num == KEY_FUNC)
		{
	    	g_cFunc++;
			g_fK1 = k1;
			key_release();
	    	return 0;
		}

		if(key_num == KEY_ADD)
		  {
		   g_iProtect = 0;
		   windSpeed = Wid_Speed(); 
		   g_fK1 = (windSpeed+0.1)/windSpeed*g_fK1;
	       if(g_fK1 >= 20)
			{
			  g_fK1 = 20;
		    }
		   if(g_fK1 <= 0.1)
			{
			  g_fK1 = 0.1;
		    }
			windSpeed = Wid_Speed();
			play = 	(int)(windSpeed*10);
			disylay_mun(play,1,0,1);  
		  }
		  
		  if(key_num == KEY_SUB)
		  {
		   g_iProtect = 0;
		   windSpeed = Wid_Speed(); 
		   g_fK1 = (windSpeed-0.1)/windSpeed*g_fK1;
	       if(g_fK1 >= 20)
			{
			  g_fK1 = 20;
		    }
		   if(g_fK1 <= 0.1)
			{
			  g_fK1 = 0.1;
		    }
			windSpeed = Wid_Speed();
			play = 	(int)(windSpeed*10);
			disylay_mun(play,POINT_1,0,1);  
		  }

		  if(key_num == KEY_SURE)
		  {
		    g_iProtect = 0;
		   Clean_Display(0,0,128,64,0);
		   if(display_Protect1(chinese2,10) == 0)
		     {
			    
			    g_fK1 = k1;
			 }
			 else
			 {
			   Dateeprom();
			   k1 = g_fK1;
			 }
		   Clean_Display(0,0,128,64,0);
		   display_stringChinese(0,0,chinese);
		   	windSpeed = Wid_Speed();
        	play = 	(int)(windSpeed*10);
     	   disylay_mun(play,POINT_1,0,1);
		 //  disylay_mun(range,2,3,1);  
		  }
		 if(g_iTimebase == 1)
		 {
		   windSpeed = Wid_Speed();
			play = 	(int)(windSpeed*10);
			disylay_mun(play,POINT_1,0,1);
		 }
		key_delay();
	    if(return_Main())
		{
		   // g_fK1 = k1;
			return 0;
		}
	//	disylay_mun(100,2,0,2);
	}
}

unsigned char display_Rate()
{
   	unsigned char key_num;
   unsigned int range ;
    float temp_K2;   						
   code unsigned char* chinese[] = {font_39,font_40,font_09,font_10,font_00};	  //补偿系数
   code unsigned char* chinese2[] ={font_22,font_23,er,font_00,font_00};	  //密码2
    range = g_fK2*100;
	temp_K2 = g_fK2;
 //  char arr[] = {'m','/','s','\0'};
	display_stringChinese(0,0,chinese);
//	display_stringChar(6,1,arr);
    disylay_mun(range,2,0,1); 
	while(1)
	{
	    if(g_cMaxOut ==0 || g_cMaxOut ==2)
	    read_Maxout();
		key_num = key();
		if(key_num == KEY_FUNC)
		{
	    	g_cFunc++;
			key_release();
	    	return 0;
		}
		range = key_AddSub(range,2,0,1,200);
		if(key_num == KEY_SURE)
		{
		   g_iProtect = 0;
		   g_fK2 = (float)range/100;
		   Clean_Display(0,0,128,64,0);
		   if(display_Protect1(chinese2,10) == 0)
		     {
			  
			    g_fK2 = temp_K2;
				range = g_fK2*100;
			 }
			 else
			 {
			     Dateeprom();
			 }
		   Clean_Display(0,0,128,64,0);
		   display_stringChinese(0,0,chinese);
		   disylay_mun(range,2,0,1);
		}
		 key_delay();
	    if(return_Main())
		{
			return 0;
		}
	//	disylay_mun(100,2,0,2);
	}
}

unsigned char display_Renew()
{
   	unsigned char key_num;
	unsigned char integral;
	unsigned char temp_integral;
    code unsigned char* chinese[] ={font_07,font_08,font_09,font_10,font_00};	  //积分系数
    code unsigned char* chinese2[] ={font_22,font_23,er,font_00,font_00};	  //密码2
 //  char arr[] = {'m','/','s','\0'};
    integral = g_cIntegral;
	temp_integral = g_cIntegral;
	display_stringChinese(0,0,chinese);
	disylay_mun(g_cIntegral,0,0,1);
//	display_stringChar(6,1,arr); 
	while(1)
	{
	    if(g_cMaxOut ==0 || g_cMaxOut ==2)
	    read_Maxout();
		key_num = key();
		if(key_num == KEY_FUNC)
		{
	    	g_cFunc++;
			key_release();
	    	return 0;
		}
		integral = key_AddSub(integral,0,0,1,19);
        if(key_num == KEY_SURE)
		{
		   g_iProtect = 0;
		   g_cIntegral = integral;
		   Clean_Display(0,0,128,64,0);
		   if(display_Protect1(chinese2,10) == 0)
		   {
		     
		     g_cIntegral = temp_integral;
			 integral = g_cIntegral; 
		   }
		   else
		   {
		     Dateeprom();
		   }
		   Clean_Display(0,0,128,64,0);
		   display_stringChinese(0,0,chinese);
		   disylay_mun(integral,0,0,1);
		}

		key_delay();
	    if(return_Main())
		{
			return 0;
		}
		
	//	disylay_mun(100,2,0,2);
	}
}

unsigned char display_ZKSet()
{
   	unsigned char key_num;
	float k1,zero;
	unsigned char temp1,temp2;
   code unsigned char* chinese[] ={font_17,font_18,font_25,font_28,font_29};	  //恢复初始值
   code unsigned char* chinese1[] ={font_30,font_29,font_00,font_00,font_00};  //原值
   code unsigned char* chinese2[] ={font_31,font_29,font_00,font_00,font_00};   //新值
   code unsigned char* chinese3[] ={font_22,font_23,er,font_00,font_00};	  //密码2
 //  char arr[] = {'m','/','s','\0'};
       k1 = g_fK1;
	   zero = g_fZero;
	display_stringChinese(0,0,chinese);
//	display_stringChar(6,1,arr); 
     if((g_fZero>(g_fZero_rev-0.01)&&g_fZero<(g_fZero_rev+0.01)) && g_fK1>0.99 && g_fK1<1.01 )
	   {
	      display_stringChinese(0,1,chinese1);
	   }
	   else
	   {
	      display_stringChinese(0,1,chinese2);
	   }
	while(1)
	{
	    if(g_cMaxOut ==0 || g_cMaxOut ==2)
	    read_Maxout();
		key_num = key();
		if(key_num == KEY_FUNC)
		{
	    	g_cFunc++;
			key_release();
	    	return 0;
		}
		if(key_num == KEY_SURE)
		{
		   temp1 = IapReadByte(ZERO_ADD_REV_1);
		   temp2 = IapReadByte(ZERO_ADD_REV_2);
		   g_fZero_rev = (temp1*100+temp2)/100;
		   g_iProtect = 0;
		   g_fK1 = 1.0;
		   g_fZero =g_fZero_rev ;
		   Clean_Display(0,0,128,64,0);

 		   if(display_Protect1(chinese3,10)==0)
		     {
			   
			   g_fK1 = k1;
			   g_fZero = zero;
			 }
			 else
			 {
			  Dateeprom();
			 }
		   Clean_Display(0,0,128,64,0);
		   display_stringChinese(0,0,chinese);
		   if((g_fZero>(g_fZero_rev-0.01)&&g_fZero<(g_fZero_rev+0.01)) && g_fK1>0.99 && g_fK1<1.01 )
	       {
	         display_stringChinese(0,1,chinese1);
	       }
	       else
	       {
	         display_stringChinese(0,1,chinese2);
	       } 	
		}


		key_delay();
	    if(return_Main())
		{
			return 0;
		}
	//	disylay_mun(100,2,0,2);
	}
}


unsigned char display_uint()
{
   	unsigned char key_num;
	char uint1 ;
	char temp_uint1;
  code unsigned char* chinese[] ={font_15,font_16,font_00,font_00,font_00};	  //单位
  code unsigned char* chinese2[] ={font_22,font_23,er,font_00,font_00};	  //密码2
  code char arr0[] = {'m',59,'/','s',' ',' ','\0'};
  code char arr1[] = {'m',59,'/','m','i','n','\0'};
   uint1 = g_cUint;
   temp_uint1 = g_cUint;
	display_stringChinese(0,0,chinese);
	 if(uint1 == 1)
	  {
		  display_stringChar(3,1,arr1);
	  }
	   else
	  {
		  display_stringChar(3,1,arr0);
	  }
	while(1)
	{
	   if(g_cMaxOut ==0 || g_cMaxOut ==2)
	    read_Maxout();
		key_num = key();
		if(key_num == KEY_FUNC)
		{
	    	g_cFunc++;
			key_release();
	    	return 0;
		}
        if(key_num == KEY_ADD)
		 {
		    g_iProtect = 0;
		    uint1++;
			if(uint1 == 2)
			  uint1 = 0;
		   if(uint1 == 1)
		   {
		     display_stringChar(3,1,arr1);
		   }
		   else
		   {
		     display_stringChar(3,1,arr0);
		   }
		 }
		 if(key_num == KEY_SUB)
		 {
		   g_iProtect = 0;
		   uint1--;
		   if(uint1 < 0)
		    uint1 = 1;
			if(uint1 == 1)
		   {
		     display_stringChar(3,1,arr1);
		   }
		   else
		   {
		     display_stringChar(3,1,arr0);
		   }
		 }

		 if(key_num == KEY_SURE)
		   {
		       g_iProtect = 0;
		       g_cUint = uint1;
			   Clean_Display(0,0,128,64,0);
		       if(display_Protect1(chinese2,10)==0)
			     {
				    g_cUint = temp_uint1;
					uint1 = g_cUint;
				 }
				 else
				 {
				   Dateeprom();
				 }
		       Clean_Display(0,0,128,64,0);
		       display_stringChinese(0,0,chinese);
			   if(uint1 == 1)
			   {
			     display_stringChar(3,1,arr1);
			   }
			   else
			   {
			     display_stringChar(3,1,arr0);
			   }
		   }

		key_delay();
	    if(return_Main())
		{
			return 0;
		}
	//	disylay_mun(100,2,0,2);
	}

}

unsigned char display_workchang()
{
   	unsigned char key_num;
	char workChange ;
	char temp_workChange;
  code unsigned char* chinese[] ={font_38,font_02,lei,xin,font_00};	  //流量类型
  code unsigned char* chinese2[] ={font_22,font_23,er,font_00,font_00};	  //密码2
  code unsigned char* chinese_isCh4[] ={gong,kuang,font_38,font_02,font_00};	  //纯甲烷流量	此处改成工况
  code unsigned char* chinese_noCh4[] ={biao,kuang,font_38,font_02,font_00};	  //混合流量  此处改成标况
   workChange = g_cWorkChange;
   temp_workChange = g_cWorkChange;
	display_stringChinese(0,0,chinese);
	 if(workChange == 1)
	  {
	     display_stringChinese(0,1,chinese_isCh4);
	  }
	   else
	  {
		  display_stringChinese(0,1,chinese_noCh4);
	  }
	while(1)
	{
	    if(g_cMaxOut ==0 || g_cMaxOut ==2)
	    read_Maxout();
		key_num = key();
		if(key_num == KEY_FUNC)
		{
	    	g_cFunc++;
			key_release();
	    	return 0;
		}
        if(key_num == KEY_ADD)
		 {
		    g_iProtect = 0;
		    workChange++;
			if(workChange == 2)
			  workChange = 0;
		   if(workChange == 1)
		   {
		     display_stringChinese(0,1,chinese_isCh4);
		   }
		   else
		   {
		     display_stringChinese(0,1,chinese_noCh4);
		   }
		 }
		 if(key_num == KEY_SUB)
		 {
		   g_iProtect = 0;
		   workChange--;
		   if(workChange < 0)
		    {
		      workChange = 1;
			}
			if(workChange == 1)
		   {
		     display_stringChinese(0,1,chinese_isCh4);
		   }
		   else
		   {
		     display_stringChinese(0,1,chinese_noCh4);
		   }
		 }

		 if(key_num == KEY_SURE)
		   {
		       g_iProtect = 0;
		       g_cWorkChange = workChange;
			   Clean_Display(0,0,128,64,0);
		       if(display_Protect1(chinese2,10)==0)
			     {
				    g_cWorkChange = temp_workChange;
					workChange = g_cWorkChange;
				 }
				 else
				 {
				   Dateeprom();
				 }
		       Clean_Display(0,0,128,64,0);
		       display_stringChinese(0,0,chinese);
			   if(workChange == 1)
			   {
			     display_stringChinese(0,1,chinese_isCh4);
			   }
			   else
			   {
			     display_stringChinese(0,1,chinese_noCh4);
			   }
		   }

		key_delay();
	    if(return_Main())
		{
			return 0;
		}
	}

}


unsigned char display_MaxOut()
{
   	unsigned char key_num;
	char maxout ;
	char temp_maxout;
	char flag = 0;
    unsigned char* chineseClear[] ={qing,font_03,font_00,font_00,font_00};	  //清零选择
	code unsigned char* chinese2[] ={font_22,font_23,er,font_00,font_00};	  //密码2
   code char arrOFF[] = {'O','F','F',' ','\0'};
   code char arrON[] =  {'O','N',' ',' ','\0'};
  // code char arrm3[] = {'m',59,'\0'};
 //  code char arr[] = {':','\0'};

   maxout = g_cMaxOut;
   temp_maxout = g_cMaxOut;

   mian2_chinese();

	while(1)
	{
	    if(maxout == 0 || maxout == 2)
		{
	      read_Maxout();
		}
		if(0 == flag && g_iTimebase <= 5  )
			{
				    flag = 1;
					display_sum(g_fSum,5,1); //显示工况累积值
					display_sum(g_fSum_biao,5,2); //显示工况累积值
					display_sum(g_fSum_biao_ch4,5,3);
					//display_sum(12345678,6,3);

			}
			else if(g_iTimebase>5)
			{
				     flag = 0 ;
			}   		  
		
		key_num = key();
		if(key_num == KEY_FUNC)
		{
	    	g_cFunc++;
			key_release();
	    	return 0;
		}
        if(key_num == KEY_ADD)
		 {
		    g_iProtect = 0;
		    maxout++;
			if(maxout == 3)
			  maxout = 0;
		   if(maxout == 1)
		   {
		     display_stringChar(7,0,arrOFF);
		   }
		   else	if(maxout == 0)
		   {
		     display_stringChar(7,0,arrON);
		   }
		   else
		   {
		     display_stringChinese(7,0,chineseClear);
		   }
		 }
		 if(key_num == KEY_SUB)
		 {
		   g_iProtect = 0;
		   maxout--;
		   if(maxout < 0)
		    maxout = 2;
			if(maxout == 1)
		   {
		     display_stringChar(7,0,arrOFF);
		   }
		   else if(maxout == 0)
		   {
		     display_stringChar(7,0,arrON);
		   }
		   else
		   {
		     display_stringChinese(7,0,chineseClear);
		   }

		 }

		 if(key_num == KEY_SURE)
		   {
		       g_iProtect = 0;
		       g_cMaxOut = maxout;
			   Clean_Display(0,0,128,64,0);
		       if(display_Protect1(chinese2,10)==0)
			     {
				    g_cMaxOut = temp_maxout;
					maxout = g_cMaxOut;
				 }
				 else
				 {
				   if(maxout == 2)
				     {
					    g_fSum = 0.0;
						g_fSum_biao = 0.0;
						g_fSum_biao_ch4 = 0.0;
					 }
				   Dateeprom();
				 }
		       Clean_Display(0,0,128,64,0);
		      mian2_chinese();
			  display_sum(g_fSum,5,1); //显示工况累积值
			  display_sum(g_fSum_biao,5,2); //显示工况累积值
			  display_sum(g_fSum_biao_ch4,5,3); 
		   }

		key_delay();
	    if(return_Main())
		{
			return 0;
		}
	}

}  
unsigned char display_Range()
{
   	unsigned char key_num;
	unsigned int range,rangeMin,temp_range,temp_rangeMin;

  code unsigned char* chinese[] ={font_02,font_21,font_00,font_00,font_00};	  //量程
  code unsigned char* chinese2[] ={font_22,font_23,er,font_00,font_00};	  //密码2
  code char arr0[] = {'m',59,'/','s',' ',' ','\0'};
  code char arr1[] = {'m',59,'/','m','i','n','\0'};
     range = g_iRange;
	 temp_range = range;
	 rangeMin = g_iRangeMin;
	 temp_rangeMin = rangeMin;
	display_stringChinese(0,0,chinese);
	if(g_cUint == 0)
	{
	  display_stringChar(5,1,arr0);
	  disylay_mun(range,0,0,1);
	}
	else
	{
	  display_stringChar(5,1,arr1);
	  disylay_mun(rangeMin,0,0,1);
	} 
	while(1)
	{
	    if(g_cMaxOut ==0 || g_cMaxOut ==2)
	    read_Maxout();
		key_num = key();
		if(key_num == KEY_FUNC)
		{
	    	g_cFunc++;
			key_release();
	    	return 0;
		}

		if(key_num == KEY_ADD)
		{
		    g_iProtect = 0;
	        if(g_cUint == 0)
			  {
			    range++;
				if(range > 10)
				 {
				  range = 10;
				 }
				 disylay_mun(range,0,0,1);
			  }
			  else
			  {
			    rangeMin = rangeMin+5;
				if(rangeMin > 1000)
				   rangeMin = 1000;
				disylay_mun(rangeMin,0,0,1);
			  }
		}

		if(key_num == KEY_SUB)
		{
		    g_iProtect = 0;
	        if(g_cUint == 0)
			  {
			    range--;
				if(range == 0)
				 {
				  range = 1;
				 }
				 disylay_mun(range,0,0,1);
			  }
			  else
			  {
			    rangeMin = rangeMin-5;
				if(rangeMin == 0)
				   rangeMin = 5;
				disylay_mun(rangeMin,0,0,1);
			  }
		}

		if(key_num == KEY_SURE)
		  {
		       g_iProtect = 0;
		       g_iRange =range;
	           g_iRangeMin = rangeMin ;
			   Clean_Display(0,0,128,64,0);
		       if(display_Protect1(chinese2,10)==0)
			     {
				   g_iRange = temp_range;
				   g_iRangeMin = temp_rangeMin;
				   range = g_iRange;
				   rangeMin = g_iRangeMin;
				 }
				 else
				 {
				   Dateeprom();
				 }
		       Clean_Display(0,0,128,64,0);
		       display_stringChinese(0,0,chinese);
			   	if(g_cUint == 0)
				{
				  display_stringChar(5,1,arr0);
				  disylay_mun(range,0,0,1);
				}
				else
				{
				  display_stringChar(5,1,arr1);
				  disylay_mun(rangeMin,0,0,1);
				} 
		  }

		key_delay();
	    if(return_Main())
		{
			return 0;
		}
	//	disylay_mun(100,2,0,2);
	}
}

unsigned char display_Protect1(unsigned char ** chinese,char num)
{
   	unsigned char key_num;
//	unsigned char i;
    
   unsigned char password=0;
 //  unsigned char* chinese[] ={font_22,font_23,yi,font_00,font_00};	  //密码1
   code char arrOK[] = {'O','K',' ',' ',' ','\0'};
   code char arrNO[] = {'N','O',' ',' ',' ','\0'};
   code char arr[] = {'e','r','r','\0'};
	display_stringChinese(0,0,chinese);
	
  //	display_stringChar(6,1,arr); 
    disylay_mun(password,0,0,1);
	key_release();
	while(1)
	{
	    if(g_cMaxOut ==0 || g_cMaxOut ==2)
	    read_Maxout();
		key_num = key();
//		if(key_num == KEY_FUNC)
//		{
//			key_release();
//	    	return 0;
//		}																						`
		if(key_num == KEY_ADD)
		{
		   g_iProtect = 0;
		   password++;
		   disylay_mun(password,0,0,1);
		  
		}
		if(key_num == KEY_SUB)
		{
		   g_iProtect = 0;
		   password--;
		   disylay_mun(password,0,0,1);
		  
		}
		if(key_num == KEY_SURE)
		{
		   key_release();
		   g_iProtect = 0;
		   if(password == num)
		     {
				display_stringChar(0,1,arrOK);
				delay(1000);
				g_cFunc = 1;
				return 1;
			 }
			 else
			 {
				display_stringChar(0,1,arrNO);
				delay(1000);
				disylay_mun(password,0,0,1);
				if(g_cFunc == 13) 
				  {
				     g_cSecrit_Num++;
					   if(g_cSecrit_Num == 5)
					       g_cSecrit_Num = 4;
					 Dateeprom();
					 if(g_cSecrit_Num>=3)
					  {
					    Clean_Display(0,0,128,64,0);
	   					 display_stringChar(6,1,arr);
							while(1)
						{
						}
					  }
				  }
			 }
		}
		if(key_num == KEY_FUNC)
		{
		    key_release();
			return 0;
		}
		   key_delay();
			if(return_Main())
			 {
			    return 0;
			 }
	//	disylay_mun(100,2,0,2);
	}
}




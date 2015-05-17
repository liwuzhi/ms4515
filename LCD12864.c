
#include "lcd12864.h"
#include "ziku.h"


void Delay_1ms(uint x)
{
	unsigned char j;
	while(x--)
	{
		for(j=0;j<125;j++)
		{;}
	}
}

void Lcm_Delay(void)//液晶延时，防止单片机时钟过快，乱显
{
   char i;
   for(i=0;i<3;i++)
   {	
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	}
		

}
void Wr_Data_L(uchar wrdata) //左半屏写数据
{
	CS1=1;
	CS2=0;
	RS=1;
	RW=0;	
	LCMdata=wrdata;
	E=1;
	Lcm_Delay();//必须加延时，30M以上晶振须再加长延时
	E=0; 
	CS1=0;
	CS2=0;
}


void Wr_Data_R(uchar wrdata) //右半屏写数据
{
	CS1=0;
	CS2=1;
	RS=1;
	RW=0;
	LCMdata=wrdata;
	E=1;	
	Lcm_Delay();//必须加延时，30M以上晶振须再加长延时
	E=0; 
	CS1=0;
	CS2=0;
}


void Wr_Command_L(uchar wrcommand) //左半屏写指令
{
	Lcm_Delay();
	CS1=1;
	CS2=0;
	RS=0;
	RW=0;
	LCMdata=wrcommand;
	E=1;	
	Lcm_Delay();//必须加延时，30M以上晶振须再加长延时
	E=0;
	CS1=0;
	CS2=0;
}


void Wr_Command_R(uchar wrcommand) //右半屏写指令
{
	Lcm_Delay();
	CS1=0;
	CS2=1;
	RS=0;
	RW=0;	
	LCMdata=wrcommand;
	E=1;	
	Lcm_Delay();//必须加延时，30M以上晶振须再加长延时
	E=0;
	CS1=0;
	CS2=0;
}

/**********************************************************
pos_x是显示位置X坐标0~127
pos_y是显示所在行0~7
length是长度
width是宽度,调用图片宽度必须是8的倍数
graphic图片指针
reverse=0时正显,reverse=1时负显
***********************************************************/
void Display_Graphic(uchar pos_x,uchar pos_y,uchar length,uchar width,uchar *graphic,bit reverse)
{
	uchar page,address,disp_data,i;
	if(((pos_y*8+width)>64)||((pos_x+length)>128)||(width%8))
		return;	//超出显示范围，跳出

	page=X_ADDRESS+pos_y;			
	address=pos_x;
	for(i=0;i<(width/8);i++)
	{
		for(;(address-pos_x)<length;address++)
		{
			if(reverse)
				disp_data=~(*graphic++);
			else
				disp_data=*graphic++;		
			if(address<64)
			{
				Wr_Command_L(START_LINE);		
				Wr_Command_L(page);	
				Wr_Command_L(address+Y_ADDRESS);					
				Wr_Data_L(disp_data); 			
			}
			else
			{
				Wr_Command_R(START_LINE);			
				Wr_Command_R(page);		
				Wr_Command_R(address); //address+Y_ADDRESS-64	
				Wr_Data_R(disp_data); 
			}
		}
		address=pos_x;
		page++;
	}			
}

/**********************************************************
pos_x是显示位置X坐标0~127
pos_y是显示所在行0~7
length是长度
width是宽度,调用图片宽度必须是8的倍数
graphic图片指针
reverse=0时清屏,reverse=1时全显
***********************************************************/
void Clean_Display(uchar pos_x,uchar pos_y,uchar length,uchar width,bit reverse)
{
	uchar page,address,disp_data,i;
	if(((pos_y*8+width)>64)||((pos_x+length)>128)||(width%8))
		return;	//超出显示范围，跳出

	page=X_ADDRESS+pos_y;			
	address=pos_x;
	for(i=0;i<(width/8);i++)
	{
		for(;(address-pos_x)<length;address++)
		{
			if(reverse)
				disp_data=0xff;
			else
				disp_data=0x00;		
			if(address<64)
			{
				Wr_Command_L(START_LINE);		
				Wr_Command_L(page);	
				Wr_Command_L(address+Y_ADDRESS);					
				Wr_Data_L(disp_data); 			
			}
			else
			{
				Wr_Command_R(START_LINE);			
				Wr_Command_R(page);		
				Wr_Command_R(address); //address+Y_ADDRESS-64	
				Wr_Data_R(disp_data); 
			}
		}
		address=pos_x;
		page++;
	}			
}




void Display_Onechar(uchar pos_x,uchar pos_y,uchar Onechar,bit reverse)//显示一个字符
{
	uchar page,address,disp_data,i,k;
	if(((pos_y*8+16)>64)||((pos_x+8)>128))
		return; //超出显示范围，跳出

	page=X_ADDRESS+pos_y;			
	address=pos_x;

	for(i=0;i<2;i++)
	{
		k=0;		
		for(;(address-pos_x)<8;address++)
		{
			if(reverse)
				disp_data=~(nAsciiDot[(Onechar-0x20)*16+i*8+k]);
			else
				disp_data=nAsciiDot[(Onechar-0x20)*16+i*8+k];
			if(address<64)
			{
				Wr_Command_L(START_LINE);		
				Wr_Command_L(page); 
				Wr_Command_L(address+Y_ADDRESS);					
				Wr_Data_L(disp_data);			
			}
			else
			{
				Wr_Command_R(START_LINE);			
				Wr_Command_R(page); 	
				Wr_Command_R(address); 
				Wr_Data_R(disp_data); 
			}
			k++;
		}
		address=pos_x;
		page++;
	}	
}





void Lcm_Init(void)  //液晶初始化
{
	Delay_1ms(100);
	
	RST=0;
	Lcm_Delay();
	RST=1;
	
	Wr_Command_L(DISPLAY_OFF);  
	Wr_Command_R(DISPLAY_OFF);  //关显示

	Wr_Command_L(START_LINE); 
	Wr_Command_R(START_LINE);  //显示起始行

	Wr_Command_L(X_ADDRESS); 
	Wr_Command_R(X_ADDRESS);	//设置页地址

	Wr_Command_L(Y_ADDRESS); 
	Wr_Command_R(Y_ADDRESS);	//设置列地址

	Wr_Command_L(DISPLAY_ON); 
	Wr_Command_R(DISPLAY_ON);  //开显示

	Clean_Display(0,0,128,64,0);
}






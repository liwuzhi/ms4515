
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

void Lcm_Delay(void)//Һ����ʱ����ֹ��Ƭ��ʱ�ӹ��죬����
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
void Wr_Data_L(uchar wrdata) //�����д����
{
	CS1=1;
	CS2=0;
	RS=1;
	RW=0;	
	LCMdata=wrdata;
	E=1;
	Lcm_Delay();//�������ʱ��30M���Ͼ������ټӳ���ʱ
	E=0; 
	CS1=0;
	CS2=0;
}


void Wr_Data_R(uchar wrdata) //�Ұ���д����
{
	CS1=0;
	CS2=1;
	RS=1;
	RW=0;
	LCMdata=wrdata;
	E=1;	
	Lcm_Delay();//�������ʱ��30M���Ͼ������ټӳ���ʱ
	E=0; 
	CS1=0;
	CS2=0;
}


void Wr_Command_L(uchar wrcommand) //�����дָ��
{
	Lcm_Delay();
	CS1=1;
	CS2=0;
	RS=0;
	RW=0;
	LCMdata=wrcommand;
	E=1;	
	Lcm_Delay();//�������ʱ��30M���Ͼ������ټӳ���ʱ
	E=0;
	CS1=0;
	CS2=0;
}


void Wr_Command_R(uchar wrcommand) //�Ұ���дָ��
{
	Lcm_Delay();
	CS1=0;
	CS2=1;
	RS=0;
	RW=0;	
	LCMdata=wrcommand;
	E=1;	
	Lcm_Delay();//�������ʱ��30M���Ͼ������ټӳ���ʱ
	E=0;
	CS1=0;
	CS2=0;
}

/**********************************************************
pos_x����ʾλ��X����0~127
pos_y����ʾ������0~7
length�ǳ���
width�ǿ��,����ͼƬ��ȱ�����8�ı���
graphicͼƬָ��
reverse=0ʱ����,reverse=1ʱ����
***********************************************************/
void Display_Graphic(uchar pos_x,uchar pos_y,uchar length,uchar width,uchar *graphic,bit reverse)
{
	uchar page,address,disp_data,i;
	if(((pos_y*8+width)>64)||((pos_x+length)>128)||(width%8))
		return;	//������ʾ��Χ������

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
pos_x����ʾλ��X����0~127
pos_y����ʾ������0~7
length�ǳ���
width�ǿ��,����ͼƬ��ȱ�����8�ı���
graphicͼƬָ��
reverse=0ʱ����,reverse=1ʱȫ��
***********************************************************/
void Clean_Display(uchar pos_x,uchar pos_y,uchar length,uchar width,bit reverse)
{
	uchar page,address,disp_data,i;
	if(((pos_y*8+width)>64)||((pos_x+length)>128)||(width%8))
		return;	//������ʾ��Χ������

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




void Display_Onechar(uchar pos_x,uchar pos_y,uchar Onechar,bit reverse)//��ʾһ���ַ�
{
	uchar page,address,disp_data,i,k;
	if(((pos_y*8+16)>64)||((pos_x+8)>128))
		return; //������ʾ��Χ������

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





void Lcm_Init(void)  //Һ����ʼ��
{
	Delay_1ms(100);
	
	RST=0;
	Lcm_Delay();
	RST=1;
	
	Wr_Command_L(DISPLAY_OFF);  
	Wr_Command_R(DISPLAY_OFF);  //����ʾ

	Wr_Command_L(START_LINE); 
	Wr_Command_R(START_LINE);  //��ʾ��ʼ��

	Wr_Command_L(X_ADDRESS); 
	Wr_Command_R(X_ADDRESS);	//����ҳ��ַ

	Wr_Command_L(Y_ADDRESS); 
	Wr_Command_R(Y_ADDRESS);	//�����е�ַ

	Wr_Command_L(DISPLAY_ON); 
	Wr_Command_R(DISPLAY_ON);  //����ʾ

	Clean_Display(0,0,128,64,0);
}






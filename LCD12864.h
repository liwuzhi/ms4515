/*================================================
                         12864 demo ����  

/*  LCD�ͺţ�MJ12864J   ���� ������KS0108     
/*  MCU:AT89S52 , ����Ƶ�ʣ�12MHz                              
/*                                                                                               
/* ���ߣ� JingJun Lin                                               
/* ʱ�䣺 2011/03/12     

==================================================
������ͼ: 

 1 : VSS -----0V
 2 : VDD -----5V
 3 : V0-------�ӵ�λ���м�ˣ���λ������2�˽ӵ�VSS��VEE
 4 : RS ------P2.6
 5 : RW -----P2.5
 6 : E-- -----P2.4
 7 : DB0 -----P1.0
 8 : DB1-----P1.1
 9 : DB2-----P1.2
10 : DB3-----P1.3
11 : DB4-----P1.4
12 : DB5-----P1.5
13 : DB6-----P1.6
14 : DB7-----P1.7
15 : CS1 ----P2.3
16 : CS2-----P2.2
17 : RST ----P2.0   //Һ�����Դ���λ��·���˽�λ������
18 : VEE-----��20K�ĵ�λ����V0
19 : LED_A ----5V
20 : LED_K-----0V

================================================*/
#ifndef _LCD12864_
#define _LCD12864_
#include<reg52.h>
#include<intrins.h>

#define uchar unsigned char
#define uint unsigned int

#define LCMdata P2
sbit RS=P0^3; 
sbit RW=P1^4; 
sbit E=P1^5; 
sbit CS1=P0^2;
sbit CS2=P1^2;
sbit RST=P1^3;
sbit LCD =P3^0;

#define START_LINE	0xC0
#define X_ADDRESS	0xB8
#define Y_ADDRESS	0x40
#define DISPLAY_ON	0x3F
#define DISPLAY_OFF	0x3E

#define lcd_on()   LCD = 0
#define lcd_off()  LCD = 1
//#define x_1  0
//#define x_2  8
//#define x_3  16
//#define x_4  24
//#define x_5  32
//#define x_6  40
//#define x_7  48
//#define x_8  56
//#define x_9  64
//#define x_10 72
//#define x_11 80
//#define x_12 88
//#define x_13 96
//#define x_14 104
//#define x_15 112
//#define x_16 120
//
//#define y_1 0
//#define y_2 2
//#define y_3 4
//#define y_4 6
//
//#define wan_x  x_1
//#define qian_x x_2
//#define bai_x  x_3
//#define shi_x  x_4
//#define wan_y  y_2
//#define qian_y y_2
//#define bai_y  y_2
//#define shi_y  y_2
//
//#define dat_1 x_7
//#define dat_2 x_8
//#define dat_3 x_9
//#define dat_4 x_10
//#define dat_5 x_11
//#define dat_6 x_12
//
//#define date_1 x_11
//#define date_2 x_12
//#define date_3 x_13
//#define date_4 x_14
//#define date_5 x_15
//#define date_6 x_16
//
//#define unit_y y_2




//void Wr_Data_L(uchar wrdata); //�����д����
//void Wr_Data_R(uchar wrdata); //�Ұ���д����
//void Wr_Command_L(uchar wrcommand); //�����дָ��
//void Wr_Command_R(uchar wrcommand); //�Ұ���дָ��
void Display_Onechar(uchar pos_x,uchar pos_y,uchar Onechar,bit reverse);//��ʾ����������ֵ
void Display_Graphic(uchar pos_x,uchar pos_y,uchar length,uchar width,uchar *graphic,bit reverse);
void Clean_Display(uchar pos_x,uchar pos_y,uchar length,uchar width,bit reverse);
void Lcm_Init(void);//Һ����ʼ��
//void Lcm_Delay(void);
//void Delay_1ms(uint x);
#endif


//��������ȡģ,��λ����,���ݴ�����,���ϵ���
//16X16

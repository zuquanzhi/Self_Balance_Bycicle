#ifndef __OLED_H
#define __OLED_H
#include "oled_i2c.h"
#include "delay.h"
int OLED_Command(unsigned char Command);
int OLED_Data(unsigned char Data);
void OLED_Fill(unsigned char fill_Data);//全屏填充，可实现清屏或白屏(0x00  0xff)
void OLED_SetPos(unsigned char x, unsigned char y); //设置起始点坐标
void OLED_ON(void);
void OLED_OFF(void);	//让OLED休眠
void OLED_ShowSNum(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//显示一位数字
int Num_Digit(int num);//计算五位数以内数字位数
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);//显示BMP图

//以下常用
void OLED_Init(void);
//TextSize -- 字符大小(1:6*8 ; 2:8*16)
void OLED_ShowNum(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//在一行显示五位数以内数字  
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);//显示字符串
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);//显示汉字
void OLED_Clear(void);//清屏

//WGN
void OLED_ShowAngle(float pitch,float yaw);
void OLED_ShowPWM(int PWM);
void OLED_Shownum1(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);
void OLED_Shownum2(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);
void OLED_Shownum3(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);
#endif

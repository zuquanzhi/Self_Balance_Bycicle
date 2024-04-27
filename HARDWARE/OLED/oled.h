#ifndef __OLED_H
#define __OLED_H
#include "oled_i2c.h"
#include "delay.h"
int OLED_Command(unsigned char Command);
int OLED_Data(unsigned char Data);
void OLED_Fill(unsigned char fill_Data);//ȫ����䣬��ʵ�����������(0x00  0xff)
void OLED_SetPos(unsigned char x, unsigned char y); //������ʼ������
void OLED_ON(void);
void OLED_OFF(void);	//��OLED����
void OLED_ShowSNum(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//��ʾһλ����
int Num_Digit(int num);//������λ����������λ��
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);//��ʾBMPͼ

//���³���
void OLED_Init(void);
//TextSize -- �ַ���С(1:6*8 ; 2:8*16)
void OLED_ShowNum(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);//��һ����ʾ��λ����������  
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);//��ʾ�ַ���
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);//��ʾ����
void OLED_Clear(void);//����

//WGN
void OLED_ShowAngle(float pitch,float yaw);
void OLED_ShowPWM(int PWM);
void OLED_Shownum1(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);
void OLED_Shownum2(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);
void OLED_Shownum3(unsigned char x, unsigned char y, unsigned int num, unsigned char TextSize);
#endif

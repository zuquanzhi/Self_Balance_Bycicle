/******************************************************  
 ������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
 ƽ��С������Դ�棩
 ���ߣ�WangGuanNan
 QQ��1501451224
 //////////////////////////////////////////////////////
 ����ʱ�䣺2021/7/11
 �汾��V1.0 ��ƽ��
******************************************************/
#ifndef __PID_H
#define __PID_H

int vertical_PID_value(float measure,float calcu); //ֱ����
int velocity_PID_value(int velocity);              //�ٶȻ�
void I_xianfu(int max);                            //pwm�޷�
#endif
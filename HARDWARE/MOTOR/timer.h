#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

void TIM1_PWM_Init(u16 arr,u16 psc); //TIM1��pwmģʽ��ʼ��
void TIM3_encoder_init(void);        //TIM3�ı�����ģʽ��ʼ��
void TIM2_encoder_init(void);        //TIM2�ı�����ģʽ��ʼ��
#endif

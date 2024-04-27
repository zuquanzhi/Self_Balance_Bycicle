#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

void TIM1_PWM_Init(u16 arr,u16 psc); //TIM1的pwm模式初始化
void TIM3_encoder_init(void);        //TIM3的编码器模式初始化
void TIM2_encoder_init(void);        //TIM2的编码器模式初始化
#endif

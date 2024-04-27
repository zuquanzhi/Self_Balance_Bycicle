#include "mpuexti.h"
#include "sys.h"
#include "mpu6050.h"   
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "OLED.h"
#include "delay.h"
#include "pid.h"
#include "motor.h"
#include "timer.h"

extern float zhongzhi; //roll理论值（小车平衡时的角度）
extern int motor_flag; //电机使能标志
float pitch,roll,yaw;  //欧拉角
float measure,calcu;   //测量值和理论值                   
int velocity;          //速度测量值（编码器脉冲数，非真实速度）
int PWM;               //PWM值


void MPU_exti_init()
{
	EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
 	GPIO_InitTypeDef GPIO_InitStructure;
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);				  //使能复用功能时钟
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;								  //PA12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 					    //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
 
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource12); //将PA12映射到中断线12
	EXTI_InitStructure.EXTI_Line=EXTI_Line12;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;     //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	  	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 	//抢占优先级0 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			    //响应优先级0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						
	NVIC_Init(&NVIC_InitStructure);
}


// 外部中断线12服务程序，PID控制在此函数中
void EXTI15_10_IRQHandler(void)
{
	if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
	{ 	
			measure = roll;   //roll轴实际值                                  //roll测量值
			calcu = zhongzhi; //目标值，直立时的机械种植                                  //roll理论值
			
			velocity = ( read_encoder2() + read_encoder3() )/2; //速度测量值      
		
		
		
		  //PID计算：直立环+速度环（完整版本还要加转向环，转向环怎么写怎么调，请看群公告）
			PWM = vertical_PID_value(measure, calcu) + velocity_PID_value(velocity); //主要是直隶环
			PWM_Xianfu(7000,&PWM);      //PWM限幅
			
		
		
			if(motor_flag) SETPWM(PWM); //给电机PWM
			else           SETPWM(0);   //关闭电机		
	}
	
	EXTI_ClearITPendingBit(EXTI_Line12); //清除LINE0上的中断标志位  
}

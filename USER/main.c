/******************************************************  
 本程序只供学习使用，未经作者许可，不得用于其它任何用途
 平衡小车（开源版）
 作者：WangGuanNan（B站：_WNNN）
 QQ：1501451224
 //////////////////////////////////////////////////////
 创建时间：2021/7/11
 版本：V1.0 仅平衡
******************************************************/
#include <stm32f10x.h>
#include "delay.h"
#include "oled.h"
#include "sys.h"
#include "usart.h"
#include "mpu6050.h"   
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include "motor.h"

extern float pitch,roll,yaw;  //欧拉角测量值
float zhongzhi=0;             //roll理论值（小车平衡时的角度）
extern int velocity;          //速度测量值（编码器脉冲数，非真实速度）
extern float velocity_sum;    //速度积分
int motor_flag;               //电机使能标志：1使能  0失能

//直立环PD参数:
float Kp=-420,Ki=0,Kd=-2000;  //调完速度环后精调
//float Kp=-420,Ki=0,Kd=-960; //乘0.6
//float Kp=-700,Ki=0,Kd=-1600; 
//float Kp=0,Ki=0,Kd=0;

//速度环PI参数:
float VKp=+190,VKi=0.95;               


int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //2位抢占优先级，2位响应优先级
	delay_init();               										//延时函数初始化
	OLED_Init();                									  //oled初始化
  motor_init();               										//电机的 IO  pwm  编码器 初始化
	MPU_Init();		              										//MPU6050初始化	 
	DMP_Init();                										  //DMP初始化	
	MPU_exti_init();            										//mpu外部中断初始化（放最后）
	
/*******************************************************************************	
                            到此所有模块初始化完毕
********************************************************************************/ 
	
	while(1)
	{
		//【1】安全装置：
		if(roll<-30 || roll>30)   //小车可能已经倒了
		{
			motor_flag = 0;         //关闭电机
			velocity_sum = 0;       //速度积分清0
			TIM_SetCounter(TIM3,0); //编码器计数值清零
			TIM_SetCounter(TIM2,0); //编码器计数值清零
		}
		else motor_flag = 1;      //开启电机
		
		
		//【2】状态显示：
		OLED_ShowAngle(roll,yaw); //显示欧拉角
		OLED_ShowPWM(velocity);   //显示速度（非真实速度）
	}
}

// 小黑提醒：有问题先看群公告和精华消息，大部分问题我都汇总答疑过了。
//          注意直立环不要调错了，直立环不是要调平衡，而且只有直立环也不能平衡，就算能平衡也是没有什么抗干扰性的（除非小车结构非常好，本身就已经有平衡性）。
//           调参步骤可以看我B站视频，搜平衡小车前几个就是，还可以找群文件里的“平衡小车调参步骤”。  

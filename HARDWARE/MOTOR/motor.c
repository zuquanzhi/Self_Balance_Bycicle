#include "motor.h"
#include "delay.h"
#include "timer.h"
#include "oled.h"

void SETPWM(int PWM)
{
	if(PWM>0) //正转
	{
		left_positive();
		right_positive();
		TIM_SetCompare1(TIM1,7200-PWM); //这里为什么是7200-PWM，因为高级定时器的某些通道PWM输出反相，示波器测一下就知道了，群公告里也有写
		TIM_SetCompare4(TIM1,PWM);     
	}
	else      //反转
	{
		left_negative();
		right_negative();
		TIM_SetCompare1(TIM1,7200-(-PWM) ); 
		TIM_SetCompare4(TIM1,-PWM );      
	}	
}


void PWM_Xianfu(int max,int *PWM)
{
	if(*PWM>max)  *PWM = max;
	if(*PWM<-max) *PWM =-max;
}


void left_positive(void) //左轮正传
{
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
}

void left_negative(void) //左轮反转
{
	GPIO_SetBits(GPIOB,GPIO_Pin_15);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
}

void right_positive(void) //右轮正转
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
}

void right_negative(void) //右轮反转
{
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}


void motor_init()
{
	motor_gpio_init();         //gpio初始化
	TIM1_PWM_Init(7200-1,1-1); //TIM1的pwm模式初始化
	TIM3_encoder_init();       //TIM3的编码器模式初始化
	TIM2_encoder_init();       //TIM2的编码器模式初始化
}


//PWM：   左PA8
//        右PA11
//正反转： 左PB14、15
//        右PB13、12
void motor_gpio_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//PWM口初始化：
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11;  //TIM1_CH1  TIM1_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;        //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//正反转控制口初始化：
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_12; //右正反转
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15; //左正反转
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}


int read_encoder3(void)
{
	int speed;
	speed = (short)TIM_GetCounter(TIM3); //1.采集编码器的计数值并保存
	TIM_SetCounter(TIM3,0);              //2.将定时器的计数值清零
	
	return speed;
}

int read_encoder2(void)
{
	int speed;
	speed = (short)TIM_GetCounter(TIM2); //1.采集编码器的计数值并保存
	TIM_SetCounter(TIM2,0);              //2.将定时器的计数值清零
	
	return speed;
}

#include "motor.h"
#include "delay.h"
#include "timer.h"
#include "oled.h"

void SETPWM(int PWM)
{
	if(PWM>0) //��ת
	{
		left_positive();
		right_positive();
		TIM_SetCompare1(TIM1,7200-PWM); //����Ϊʲô��7200-PWM����Ϊ�߼���ʱ����ĳЩͨ��PWM������࣬ʾ������һ�¾�֪���ˣ�Ⱥ������Ҳ��д
		TIM_SetCompare4(TIM1,PWM);     
	}
	else      //��ת
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


void left_positive(void) //��������
{
	GPIO_SetBits(GPIOB,GPIO_Pin_14);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
}

void left_negative(void) //���ַ�ת
{
	GPIO_SetBits(GPIOB,GPIO_Pin_15);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
}

void right_positive(void) //������ת
{
	GPIO_SetBits(GPIOB,GPIO_Pin_12);
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
}

void right_negative(void) //���ַ�ת
{
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}


void motor_init()
{
	motor_gpio_init();         //gpio��ʼ��
	TIM1_PWM_Init(7200-1,1-1); //TIM1��pwmģʽ��ʼ��
	TIM3_encoder_init();       //TIM3�ı�����ģʽ��ʼ��
	TIM2_encoder_init();       //TIM2�ı�����ģʽ��ʼ��
}


//PWM��   ��PA8
//        ��PA11
//����ת�� ��PB14��15
//        ��PB13��12
void motor_gpio_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	//PWM�ڳ�ʼ����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11;  //TIM1_CH1  TIM1_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;        //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//����ת���ƿڳ�ʼ����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_12; //������ת
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15; //������ת
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}


int read_encoder3(void)
{
	int speed;
	speed = (short)TIM_GetCounter(TIM3); //1.�ɼ��������ļ���ֵ������
	TIM_SetCounter(TIM3,0);              //2.����ʱ���ļ���ֵ����
	
	return speed;
}

int read_encoder2(void)
{
	int speed;
	speed = (short)TIM_GetCounter(TIM2); //1.�ɼ��������ļ���ֵ������
	TIM_SetCounter(TIM2,0);              //2.����ʱ���ļ���ֵ����
	
	return speed;
}

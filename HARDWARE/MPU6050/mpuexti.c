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

extern float zhongzhi; //roll����ֵ��С��ƽ��ʱ�ĽǶȣ�
extern int motor_flag; //���ʹ�ܱ�־
float pitch,roll,yaw;  //ŷ����
float measure,calcu;   //����ֵ������ֵ                   
int velocity;          //�ٶȲ���ֵ��������������������ʵ�ٶȣ�
int PWM;               //PWMֵ


void MPU_exti_init()
{
	EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
 	GPIO_InitTypeDef GPIO_InitStructure;
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);				  //ʹ�ܸ��ù���ʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;								  //PA12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 					    //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
 
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource12); //��PA12ӳ�䵽�ж���12
	EXTI_InitStructure.EXTI_Line=EXTI_Line12;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;     //�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	  	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 	//��ռ���ȼ�0 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			    //��Ӧ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;						
	NVIC_Init(&NVIC_InitStructure);
}


// �ⲿ�ж���12�������PID�����ڴ˺�����
void EXTI15_10_IRQHandler(void)
{
	if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
	{ 	
			measure = roll;   //roll��ʵ��ֵ                                  //roll����ֵ
			calcu = zhongzhi; //Ŀ��ֵ��ֱ��ʱ�Ļ�е��ֲ                                  //roll����ֵ
			
			velocity = ( read_encoder2() + read_encoder3() )/2; //�ٶȲ���ֵ      
		
		
		
		  //PID���㣺ֱ����+�ٶȻ��������汾��Ҫ��ת�򻷣�ת����ôд��ô�����뿴Ⱥ���棩
			PWM = vertical_PID_value(measure, calcu) + velocity_PID_value(velocity); //��Ҫ��ֱ����
			PWM_Xianfu(7000,&PWM);      //PWM�޷�
			
		
		
			if(motor_flag) SETPWM(PWM); //�����PWM
			else           SETPWM(0);   //�رյ��		
	}
	
	EXTI_ClearITPendingBit(EXTI_Line12); //���LINE0�ϵ��жϱ�־λ  
}

/******************************************************  
 ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
 ƽ��С������Դ�棩
 ���ߣ�WangGuanNan
 QQ��1501451224
 //////////////////////////////////////////////////////
 ����ʱ�䣺2021/7/11
 �汾��V1.0 ��ƽ��
******************************************************/
#include "pid.h"

extern float Kp,Ki,Kd;   //ֱ��������
float err;               //�˴����
float last_err;          //�ϴ����
float err_sum=0;         //����ۼ�
float err_difference;    //���Ĳ�ֵ

extern float VKp,VKi;    //�ٶȻ�����
float filt_velocity;     //�˲�����ٶ�
float last_filt_velocity;//��һ�ε��˲�����ٶ�
float velocity_sum=0;    //�ٶȵ��ۼ�


//ֱ������
int vertical_PID_value(float measure,float calcu)
{

	err = measure - calcu;             //���
	err_sum+=err;                      //�����ۼ�
	err_difference = err - last_err;   //���Ĳ�ֵ
	last_err = err;                    //�˴�����¼Ϊ���ϴ���
	
	return Kp*err + Ki*err_sum + Kd*err_difference;
}


//�ٶȻ���������ٶȻ��Ǽ�д��ʽ�ģ�������ʽӦ�ú������ֱ����һ������������ڲ��������Ⱥ���棬���߿����Լ�������д��
int velocity_PID_value(int velocity)
{
	float a=0.3;                                           //�˲�ϵ������ӳ�˲��̶ȣ�
	filt_velocity = a*velocity + (1-a)*last_filt_velocity; //һ���ٶ��˲�
	velocity_sum +=  filt_velocity;                        //�ٶȵ��ۼ�
	I_xianfu(3000);                                        //�ۼ��޷�
	last_filt_velocity = filt_velocity;                    //�˴��ٶȼ�¼Ϊ���ϴ��ٶȡ�

	return VKp*filt_velocity + VKi*velocity_sum;
}


//I�޷���
void I_xianfu(int max)
{
	if(velocity_sum>max)  velocity_sum=max;
	if(velocity_sum<-max) velocity_sum=-max;
}

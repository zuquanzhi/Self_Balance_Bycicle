#ifndef __MOTOR_H
#define __MOTOR_H

void motor_init(void);
void motor_gpio_init(void);
void PWM_Xianfu(int max,int *PWM);
void SETPWM(int PWM);
int read_encoder3(void);
int read_encoder2(void);
void motor_enable(float pitch); //���ݽǶ��ж��Ƿ�ʹ�� or �رյ��
void left_positive(void);       //��������
void left_negative(void);       //���ַ�ת
void right_positive(void);      //������ת
void right_negative(void);      //���ַ�ת
#endif

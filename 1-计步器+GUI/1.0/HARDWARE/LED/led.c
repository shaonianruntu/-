#include"led.h"


void LED_GPIO_Configuration(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
	/*ʹ��GPIOA������ʱ��*/
    RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOA,ENABLE);
	/*ѡ����Ƶ�GPIOA������*/
 	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
	/*��������Ϊ����ģʽ���*/
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	/*�����������Ƶ��*/
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	/*���ÿ⣬��ʼ��GPIOA*/
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	/*����GPIOA��ĳһλ����ߵ�ƽ*/
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);   //ʹ��PD�˿�ʱ��
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	    		 //LED1-->PD.2 �˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	 GPIO_Init(GPIOD, &GPIO_InitStructure);	
	 GPIO_SetBits(GPIOD,GPIO_Pin_2); 


}




#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "systick.h"
#include "lcd.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 

  
int main(void)
{ 
	u8 t=0;						
	float pitch,roll,yaw; 		//ŷ����
	short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
	short gyrox,gyroy,gyroz;	//������ԭʼ����
	short tmp;					//��ʱ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(500000);		//��ʼ�����ڲ�����Ϊ500000
 	LCD_Init();					//LCD��ʼ��
	MPU_Init();					//��ʼ��MPU6050
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"MPU6050 TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/5/9");
	/* MPU6050 dmp ��ʼ�� */
	while(mpu_dmp_init())
	{
		LCD_ShowString(30,130,200,16,16,"MPU6050 Error");
		Delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		Delay_ms(200);
	}
	LCD_ShowString(30,130,200,16,16,"MPU6050 OK");
	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
 	LCD_ShowString(30,200,200,16,16," Temp:    . C");	
 	LCD_ShowString(30,220,200,16,16,"Pitch:    . C");	
 	LCD_ShowString(30,240,200,16,16," Roll:    . C");	 
 	LCD_ShowString(30,260,200,16,16," Yaw :    . C");	 
 	while(1)
	{
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
		{ 
			tmp = MPU_Get_Temperature();				//�õ��Ѿ�������100�����¶�ֵ
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
			if((t%10)==0)
			{ 
				if(tmp < 0)
				{
					LCD_ShowChar(30+48,200,'-',16,0);		//��ʾ����
					tmp = -tmp;								//תΪ����
				}else LCD_ShowChar(30+48,200,' ',16,0);		//ȥ������ 
				LCD_ShowNum(30+48+8,200,tmp/100,3,16);		//��ʾ��������	    
				LCD_ShowNum(30+48+40,200,tmp%10,1,16);		//��ʾС������ 
				/* ������ */
				tmp=pitch*10;								//�õ�������,������ֵ����10��
				if(tmp < 0)
				{
					LCD_ShowChar(30+48,220,'-',16,0);		//��ʾ����
					tmp = -tmp;		//תΪ����
				}else LCD_ShowChar(30+48,220,' ',16,0);		//ȥ������ 
				LCD_ShowNum(30+48+8,220,tmp/10,3,16);		//��ʾ��������	    
				LCD_ShowNum(30+48+40,220,tmp%10,1,16);		//��ʾС������ 
				/* ����� */
				tmp = roll*10;								//�õ�����ǣ�����������10��
				if(tmp < 0)	
				{
					LCD_ShowChar(30+48,240,'-',16,0);		//��ʾ����
					tmp = -tmp;		//תΪ����
				}else LCD_ShowChar(30+48,240,' ',16,0);		//ȥ������ 
				LCD_ShowNum(30+48+8,240,tmp/10,3,16);		//��ʾ��������	    
				LCD_ShowNum(30+48+40,240,tmp%10,1,16);		//��ʾС������ 
				/* ����� */
				tmp = yaw*10;
				if(tmp<0)
				{
					LCD_ShowChar(30+48,260,'-',16,0);		//��ʾ����
					tmp = -tmp;		//תΪ����
				}else LCD_ShowChar(30+48,260,' ',16,0);		//ȥ������ 
				LCD_ShowNum(30+48+8,260,tmp/10,3,16);		//��ʾ��������	    
				LCD_ShowNum(30+48+40,260,tmp%10,1,16);		//��ʾС������  
				
				t=0;
			}
		}
		t++; 
	} 	
}

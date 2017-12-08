#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "GUI.h"
#include "touch.h"
#include "timer.h"
  
 
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	TIM2_Int_Init(100-1,8400-1);	//�ж�10ms
	tp_dev.init();				//��������ʼ��

	GUI_Init();	

	
	GUI_SetBkColor(GUI_WHITE);
	GUI_Clear();
	
	GUI_CURSOR_Show();	//��ʾָ��
	Task_One();
	
	
    while(1){
		GUI_Exec();	//�������к�����������º���
	}
}	


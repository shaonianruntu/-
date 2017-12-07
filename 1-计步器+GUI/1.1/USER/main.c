#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "GUI.h"
#include "touch.h"
#include "timer.h"
#include "stepcounter.h"
 
extern void JBQ_Draw_Time(void);
extern void JBQ_Draw_TopThree(void);
extern void JBQ_Draw_Panel(void);
extern void ZNZ_Draw_Compass();
extern void GPS_Draw_Satellite();

int main(void)
{
//	int j=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
//	TIM2_Int_Init(100-1,8400-1);	//�ж�10ms

//	stepcounter_main();
	GUI_Init();		//LCD��ʼ��
	GUI_SetBkColor(0x282C30);
	GUI_Clear();
	tp_dev.init();				//��������ʼ��
	
	ZNZ_Draw_Compass();
	GPS_Draw_Satellite();
	
	JBQ_Draw_Time();
	JBQ_Draw_TopThree();
	JBQ_Draw_Panel();

	stepcounter_main();

	
//    while(1){
//	//	GUI_DispDecAt(j++,600,400,5);
//	//	if(j>=99999)j=0;
//		GUI_Exec();	//�������к�����������º���
//	}
}	


#include "systick.h"

static __IO u32 TimingCounter;

/**
  * @brief �δ��ʱ������
  */
void mySysTick_Init(void){
	
	g_SystickContextStruct.CallbackFunc = (void*)0;
	g_SystickContextStruct.Counter = 
	
	if(SysTick_Config(SystemCoreClock/1000000)){	//��ʱ����Ϊ1us
		while(1);	//�������
	}
}

void Delay_us(__IO u32 nTime){
	TimingCounter = nTime;
	while(TimingCounter != 0);
}



void TimingDelay_Decrement(void)
{
	if(TimingCounter != 0x00){
		TimingCounter -= 1;
	}	
}





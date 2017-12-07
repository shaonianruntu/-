#include "stepcounter.h"
#include "mpu6050.h"

/**
  *
  */
void StepCounter_Config(){
	Buffer_Init();				//��ʼ��������
	MPU_Init();					//��ʼ�����ٶȼ�
	
}
  
/**
  * @brief ��������ʼ��
  */
void Buffer_Init(){
	/*�������������ȫ��������*/
	for(gBuffer_Grouping = 0; gBuffer_Grouping < ACC_COUNT; gBuffer_Grouping++){
		gBuffer_IsWritable[gBuffer_Grouping] = true;
	}
	gBuffer_Grouping = 0; //��ǰ���ڴ����һ������
	gError_Code = ERROR_NULL;	//û�д���
}
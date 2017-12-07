#ifndef __STEPCOUNTER_H
#define __STEPCOUNTER_H

#include "mpu6050.h"
#include <stdbool.h>

/*��������������*/
#define BUFFER_GROUP_COUNT 			2			//����2��������
#define POINT_COUNT					100			//������������2*50	
#define POINT_PER_GROUP				(POINT_COUNT/BUFFER_GROUP_COUNT)	//ÿ���������Ĳ�������Ŀ
uint16_t gBuffer_Grouping;						//��ǰ���ڴ���Ļ���������
bool gBuffer_IsWritable[BUFFER_GROUP_COUNT];	//�û������Ƿ��д

#define ACC_COUNT					3			//���ٶ�ֵγ��

/*�����쳣�ź�*/
#define ERROR_NULL					0			//���������������ڴ���
#define ERROR_OVERFLOW				1			//���������ݲ������
uint8_t gError_Code					0			//������

/*�������ݷ�Χ*/
#define DETECTOR_MIN_PPValue		3000		//���ε���С���ֵ
#define DETECTOR_MAX_Value 			32767		//��ֵ���������
#define DETECTOR_MIN_Value 			(-32768)	//��ֵ���������







/*��¼����γ�ȵ�����*/
int16_t gDetector_Max_Value[ACC_COUNT];			//��ȡ����γ�ȵĲ���ֵ
int16_t gDetector_Min_Value[ACC_COUNT];			//��ȡ����γ�ȵĲ���ֵ
int16_t gDetector_Threshold[ACC_COUNT];			//��������γ�ȵ��ж���ֵ
int16_t gDetector_Threshold_Num	= ACC_COUNT;	//��ֵ�������




#endif
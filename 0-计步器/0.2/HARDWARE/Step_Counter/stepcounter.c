#include "stepcounter.h"


static uint32_t gTickCounterForMPU6050 = 0;	
//volatile bool bFlagForMPU6050 = false;

#define SAMPLE_POINT_COUNT			100 		//���������������� 2*50
#define SAMPLE_BUFFER_GROUP_COUNT	2			//��һ����������Ϊ2�������
#define SAMPLE_POINT_PER_GROUP 		(SAMPLE_POINT_COUNT/SAMPLE_BUFFER_GROUP_COUNT)	//ÿ������εĲ�����
#define SAMPLE_AVERAGE_COUNT		4
#define SAMPLE_ACC_COUNT            3			//���ٶȼƲ���γ����
#define SAMPLE_POINT_IN_TICKS       4			//

#define ERROR_EVERYTHING_IS_OK      0
#define ERROR_SAMPLE_OVERFLOW       1

#define DETECTOR_MIN_PPValue 		(3000)		//���ֵ��ֵ���Сֵ

#define DETECTOR_MAX_Value  (32767)				//�첨�����ֵ,16λ��
#define DETECTOR_MIN_Value  (-32768)			//�첨����Сֵ��16λ��

uint8_t gErrorCode = 0;

/* �������� */
int16_t gSampleAccValue[SAMPLE_ACC_COUNT][SAMPLE_POINT_COUNT];	//����������γ���ϵķ��ֵ
uint32_t gSampleIndex = 0;						//��ǰ���ڲ�����ʱ�����
uint32_t gSampleGroupIndex = 0;					//��ǰ���ڲ����Ļ���ζκ�
bool gSampleGroupWritable[SAMPLE_BUFFER_GROUP_COUNT];	//����ο�д�Լ�¼

/* ���ֵ */
int16_t gSampleValueMax[SAMPLE_ACC_COUNT];
int16_t gSampleValueMin[SAMPLE_ACC_COUNT];

/* �����������ֵ�� */
int16_t gSampleShresholdValueForDetector[SAMPLE_ACC_COUNT];
uint32_t gSampleShresholdIdxForDetector = SAMPLE_ACC_COUNT;	//�ϴη��ֵ���ڵ�γ��

/* This value would be the corssing point and comparied with every sample point . */
int16_t gSamplePrePPValue;
uint32_t gSamplePrePPIndex;
uint32_t gSampleMidPPIndex;

/* ��ֵ�˲� */
volatile uint32_t gFilterIndex[SAMPLE_ACC_COUNT] = {0};
volatile int16_t gFilterBuffer[SAMPLE_ACC_COUNT][SAMPLE_AVERAGE_COUNT] = {0};

/* main���̿���ʱ����� */
volatile uint32_t gCurTicker;

/* �Ʋ������ۼ� */
volatile uint32_t gStepCounter = 0; 

static void TickCallback(void);

int16_t sample_average_filter(uint32_t group, int16_t val);




/*********************************************/

short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����

int16_t max_diff;
int32_t sample_diff;
/************************************************/


void stepcounter_main(void){
	uint32_t i,j;
	
	/* ������Դ��ʼ�� */
	LCD_Init();		//LCD��ʼ��
	LED_Init();		//LED��ʼ��
	POINT_COLOR=RED;//��������Ϊ��ɫ 
	SYSTICK_Init();
	while(mpu_dmp_init())
	{
		LCD_ShowString(30,30,200,16,16,"MPU6050 Error");
		delay_ms(200);
		LCD_Fill(30,30,320,480,WHITE);
 		delay_ms(200);
	}
	/* TFT��ʾ��ʾ��Ϣ */
	LCD_ShowString(30,30,200,16,16,"************************");	
	LCD_ShowString(30,50,200,16,16,"Hello, Stepter.");
	LCD_ShowString(30,70,200,16,16,"************************");	
	
	/* ��ʼ������ */
	for(gSampleGroupIndex = 0; gSampleGroupIndex < SAMPLE_BUFFER_GROUP_COUNT; gSampleGroupIndex++){
		gSampleGroupWritable[gSampleGroupIndex] = true;			//������ݿ�д�룬�����ԭ��������
	}
	gSampleGroupIndex = 0;
	gErrorCode = ERROR_EVERYTHING_IS_OK;
	
	/* ��ʼ��������� */
	MPU_Init();		//��ʼ��MPU6050	
	
	SYSTICK_InstallCallback(TickCallback);
	gCurTicker = 0xFFFFFFFF;
	
	/* ��ʼ���� */
	while(1){
		/* ������ */
        if (ERROR_EVERYTHING_IS_OK != gErrorCode)
        {
            LCD_ShowString(30,90,200,16,16,"Error #");
			LCD_ShowNum(30+72,90,gErrorCode,1,16);
            break;
        }
//		/*��ʾ���µļƲ�ֵ*/
//		LCD_ShowString(30,90,200,16,16,"Steper:");
//		LCD_ShowNum(30+7*8,90,gStepCounter,5,16);
		
		/************************************************************************/
		/*                       ʵ����ӦСѭ��������                            */
		/************************************************************************/
		/* ����������Ϊ�գ��������ݴ��� */
		if(gSampleGroupWritable[gSampleGroupIndex]){	
			continue;
		}	

		/* �Ի������е����ݽ��д��� */
		/*
		1.ɨ�軺������ÿ�������������γ�ȣ����о�ֵ�˲���
		2.����һ���������еõ��ķ��ֵ����γ�Ƚ��бȽϣ��õ��Ʋ��������ۼӡ�
		3.���б�������������������ֵ�ļ��㣬�õ����ķ��ֵ����γ�ȡ�
		4.���������������ֵ��γ��ͬ��һ�����������бȽϣ���һ�£��򽻻��������˹���
		*/
		
		/* ������ƵĽ��̣�
        1. �Բ������ݽ��о�ֵ�˲���
        2. �Բ������ݽ��з�ֵ��⣬������һ�����жϲ����ļ����ֵ�������˲���
        3. ��ⲽ��������ģʽƥ�䡣
        */

        /* ����ʱ���⣬��Ϊmain��������������֮��Ŀ���ʱ��
        ���ֵԽ�󣬱�ʾ�ڲ�������һ��������������֮ǰ�����Բ������Ĵ������
        ����������£��û����ݴ���ʹ��0���δ���ô����ʱ���Ӧ�������һ������������֮���ʱ�䡣
        ��ʵ���ϣ��������ݻ��õ�һ��ʱ�䣬��ô����ʱ���Ӧ���ǻ���������ʱ������ȥ���������õ���ʱ�䡣
        */
		gCurTicker = 0xFFFFFFFF;
		
		/* ��ʼ�����ֵ��� */
		for(j=0;j<SAMPLE_ACC_COUNT;j++){
			gSampleValueMax[j] = DETECTOR_MIN_Value;
			gSampleValueMin[j] = DETECTOR_MAX_Value;
		}
		
		LED0 = 0;
		
		/************************************************************************/
		/*                       ����һ���������Ĳ�����                           */
		/************************************************************************/
		for(i = gSampleGroupIndex*SAMPLE_POINT_PER_GROUP; i < ((gSampleGroupIndex + 1)*SAMPLE_POINT_PER_GROUP); i++){	//��ǰ����Ļ����
			/* �ֱ���3��������Ĳ����� */
			for(j = 0; j < SAMPLE_ACC_COUNT; j++){
				/* ɨ�軺������ÿ�������������γ�ȣ����о�ֵ�˲� */
				gSampleAccValue[j][i] = sample_average_filter(j, gSampleAccValue[j][i]);
				
				/* ����һ���������еõ��ķ��ֵ����γ�Ƚ��бȽϣ��õ��Ʋ��������ۼ� */
				if(gSampleShresholdIdxForDetector == j){
					if((gSampleAccValue[j][i] >= gSampleShresholdValueForDetector[j]) 
					   && (gSampleAccValue[j][i-1] < gSampleShresholdValueForDetector[j])){
							/* Խ����ֵ���Ʋ�������1 */
							gStepCounter++;
						}
				}
				
				/* ����������Сֵ */
				if(gSampleAccValue[j][i] > gSampleValueMax[j]){
					gSampleValueMax[j] = gSampleAccValue[j][i];
				}
				if(gSampleAccValue[j][i] < gSampleValueMin[j]){
					gSampleValueMin[j] = gSampleAccValue[j][i];
				}
			}
		}
		
		/* ����Ѿ�������Ļ�������ת����һ�������� */
		gSampleGroupWritable[gSampleGroupIndex] = true;
		gSampleGroupIndex++;
		if(gSampleGroupIndex >= SAMPLE_BUFFER_GROUP_COUNT){
			gSampleGroupIndex = 0;
		}
		
		/************************************************************************/
		/*                	     		�����ж���ֵ	     	                    */
		/************************************************************************/
		/* 
		1.�õ��������ϵ��о���ֵ��gSampleShresholdValueForDetector[ii]
		2.�õ�����ᣬgSampleShresholdIdxForDetector
		*/
		gSampleShresholdIdxForDetector = SAMPLE_ACC_COUNT; //������Զ�����
		max_diff = DETECTOR_MIN_Value;	
		for(j = 0; j < SAMPLE_ACC_COUNT; j++){
			sample_diff = gSampleValueMax[j] - gSampleValueMin[j];	//���ֵ
			
			if(sample_diff >= DETECTOR_MIN_PPValue){
				gSampleShresholdValueForDetector[j] = gSampleValueMax[j] - (int16_t)(sample_diff / 4);	//��ֵΪ���ֵ��60%
				if(gSampleShresholdValueForDetector[j] > max_diff){
					max_diff = gSampleShresholdValueForDetector[j];
					gSampleShresholdIdxForDetector = j;
				}
			}
			else{
				gSampleShresholdValueForDetector[j] = DETECTOR_MAX_Value;
			}
		}
		
		/************************************************************************/
		/*                	     		��ʾ�м�ֵ 	     	                    */
		/************************************************************************/
		LCD_ShowNum(30+64,120,gSampleValueMin[0],5,16);	
		LCD_ShowNum(30+64+144,120,gSampleValueMax[0],5,16);	
		LCD_ShowNum(30+64+30,140,gSampleValueMax[0]-gSampleValueMin[0],5,16);
		
		LCD_ShowNum(30+64,160,gSampleValueMin[1],5,16);	
		LCD_ShowNum(30+64+144,160,gSampleValueMax[1],5,16);	
		LCD_ShowNum(30+64+30,180,gSampleValueMax[1]-gSampleValueMin[1],5,16);
		
		LCD_ShowNum(30+64,200,gSampleValueMin[2],5,16);	
		LCD_ShowNum(30+64+144,200,gSampleValueMax[2],5,16);	
		LCD_ShowNum(30+64+30,220,gSampleValueMax[2]-gSampleValueMin[2],5,16);
		
		LCD_ShowString(30,240,200,16,16,"DetectorValue:");
		LCD_ShowNum(30,200,gSampleShresholdValueForDetector[0],5,16);
		LCD_ShowNum(30,200,gSampleShresholdValueForDetector[1],5,16);
		LCD_ShowNum(30,200,gSampleShresholdValueForDetector[2],5,16);
		
		LCD_ShowString(30,260,200,16,16,"DetectorIdx:");
		LCD_ShowNum(30+12*16,260,gSampleShresholdIdxForDetector,5,16);
		
		LCD_ShowString(30,280,200,16,16,"************************");	
		LCD_ShowString(30,300,200,16,16,"gStepCounter: ");	
		LCD_ShowNum(30+14*16,300,gStepCounter,5,16);
		LCD_ShowString(30,320,200,16,16,"************************");	
		
		LCD_ShowString(30,340,200,16,16,"Free time:");
		LCD_ShowNum(30+10*16,340,(SAMPLE_POINT_PER_GROUP*SAMPLE_POINT_IN_TICKS) - (0xFFFFFFFF-gCurTicker),5,16);	
	}	
}
	
static void TickCallback(void){
	LED1 = !LED1;
    if (gCurTicker > 0){
        gCurTicker--;
    }
	if(gTickCounterForMPU6050 >= SAMPLE_POINT_IN_TICKS){ 		/* 50Hz */
		gTickCounterForMPU6050 = 0;
		/* �õ����ٶȴ��������� */
		MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	
		/* ������λ����λ */
		if(gSampleIndex >= SAMPLE_POINT_COUNT){
            gSampleIndex = 0;
        }
		/* ���һ�������� */
		if(gSampleGroupWritable[gSampleIndex/SAMPLE_POINT_PER_GROUP]){
			gSampleAccValue[0][gSampleIndex] = aacx;
			gSampleAccValue[1][gSampleIndex] = aacy;
			gSampleAccValue[2][gSampleIndex] = aacz;
			/* ��ǰ������Ǹû����������һ���㣬���֮��ر�дʹ�ܣ�ʹmain���̿��Զ����� */
            if (0 == (gSampleIndex+1)%SAMPLE_POINT_PER_GROUP ) 
            {
                gSampleGroupWritable[gSampleIndex / SAMPLE_POINT_PER_GROUP] = false; /* lock the buffer. */
            }
            gSampleIndex++;
		}
		else{
            //gErrorCode = ERROR_SAMPLE_OVERFLOW;
        }	
	}
	else{
        gTickCounterForMPU6050++;
    }
}

/* ��ֵ�˲� */
int16_t sample_average_filter(uint32_t group, int16_t val){
	int16_t sum;
	uint32_t i;
	
	/* ���������ݸ��� */
    if (gFilterIndex[group] >= SAMPLE_AVERAGE_COUNT){
        gFilterIndex[group] = 0;
    }
	gFilterBuffer[group][gFilterIndex[group]] = val;	//�ظ���¼4������������õ����γ����
    gFilterIndex[group]++;
	
	/* ��ֵ�ۼ� */
	sum = 0;
	for(i = 0; i < SAMPLE_AVERAGE_COUNT; i++){
		sum += gFilterBuffer[group][i];
	}
	return sum;
}

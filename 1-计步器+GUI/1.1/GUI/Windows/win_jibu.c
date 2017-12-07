#include <stddef.h>
#include "GUI.h"
#include "DIALOG.h"

#include "WM.h"
#include "BUTTON.h"
#include "CHECKBOX.h"
#include "DROPDOWN.h"
#include "EDIT.h"
#include "FRAMEWIN.h"
#include "LISTBOX.h"
#include "MULTIEDIT.h"
#include "RADIO.h"
#include "SLIDER.h"
#include "TEXT.h"
#include "PROGBAR.h"
#include "SCROLLBAR.h"
#include "LISTVIEW.h"

#include "math.h"
#include "stdio.h"


extern GUI_FONT GUI_FontHZ_NewSimSun_13;
extern GUI_FONT GUI_FontHZ_NewSimSun_15;
//extern GUI_FONT GUI_FontHZ_Consolas;

/**
  * @brief �����Ϸ�GPS���ݣ�����Ծʱ�䣩
  */
void JBQ_Draw_Time(void){
	char ac[5];




	GUI_SetColor(0xf3f3f3);
	GUI_SetFont(&GUI_FontHZ_NewSimSun_13);
	GUI_DispStringHCenterAt("��",111,16);
	GUI_DispStringHCenterAt("��",137,16);
	GUI_DispStringHCenterAt("��",163,16);

	GUI_SetFont(&GUI_Font13_ASCII);
	sprintf(ac,"%d",2016);
	GUI_DispStringHCenterAt(ac,91,15);
	sprintf(ac,"%d",11);
	GUI_DispStringHCenterAt(ac,124,15);
	sprintf(ac,"%d",21);
	GUI_DispStringHCenterAt(ac,150,15);

	sprintf(ac,"%d",20);
	GUI_DispStringHCenterAt(ac,107,0);
	GUI_DispStringHCenterAt(":",120,0);
	sprintf(ac,"%d",23);
	GUI_DispStringHCenterAt(ac,133,0);
	
}

void JBQ_Draw_TopThree(void){
	char ac[5];

	GUI_SetColor(0xf3f3f3);
	GUI_SetFont(&GUI_FontHZ_NewSimSun_15);
	GUI_DispStringHCenterAt("�ٶ�",40,40);
	GUI_DispStringHCenterAt("��Ծʱ��",120,40);
	GUI_DispStringHCenterAt("����",200,40);

	GUI_SetColor(0x12b9ff);
	GUI_SetFont(&GUI_Font32_ASCII);
	GUI_DispStringHCenterAt("h    m",128,60);
	//�ٶ�
	sprintf(ac,"%.1f",2.1);
	GUI_DispStringHCenterAt(ac,40,60);
	//��Ծʱ��
	sprintf(ac,"%d",1);
	GUI_DispStringHCenterAt(ac,88,60);
	sprintf(ac,"%d",41);
	GUI_DispStringHCenterAt(ac,128,60);
	//����
	sprintf(ac,"%.1f",7.5);
	GUI_DispStringHCenterAt(ac,200,60);
}

/**
  * @breif ���ƼƲ�������
  */
void JBQ_Draw_Panel(void){
	int i;
	float a;
	int x,y;
	char ac[5];
	
	for(i=0;i<=2;i++){
		a=(210-i*4)*3.1415926/180;
		
		GUI_SetPenSize(0);
		GUI_SetColor(0x3261e4);
		x = -70*cos(a) + 120;
		y = -70*sin(a) + 180;
		GUI_AA_DrawLine(x,y,-80*cos(a)+120,-80*sin(a)+180);
//		GUI_AA_DrawArc(120,200,80,80,-30,210);
	}
	
	for(i=3;i<=60;i++){
		a=(210-i*4)*3.1415926/180;
		
		GUI_SetPenSize(0);
		GUI_SetColor(0xaeaeae);
		x = -70*cos(a) + 120;
		y = -70*sin(a) + 180;
		GUI_AA_DrawLine(x,y,-80*cos(a)+120,-80*sin(a)+180);
//		GUI_AA_DrawArc(120,200,80,80,-30,210);
	}
	
//	GUI_SetColor(0x12b9ff);
//	GUI_SetFont(&GUI_FontD24x32);
//	sprintf(ac,"%d",10719);
//	GUI_DispStringHCenterAt(ac,120,160);

	GUI_SetColor(0xf3f3f3);
	GUI_SetFont(&GUI_FontHZ_NewSimSun_15);
	GUI_DispStringHCenterAt("���ղ���",120,130);
	
	GUI_SetColor(0x8e8e90);
	GUI_SetFont(&GUI_FontHZ_NewSimSun_13);
	GUI_DispStringHCenterAt("������ʵ����",120,205);

	GUI_SetColor(0x12b9ff);
	GUI_SetFont(&GUI_FontHZ_NewSimSun_15);
	GUI_DispStringHCenterAt("�����˶���¼��",120,230);

//	sprintf(ac,"%d",i*2);
//	GUI_DispStringHCenterAt(ac,,);
}

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

int base1[] = {80,80};	//����
int base2[] = {80,80};	//���ߵķ����ӳ���
int base3[] = {80,80};	//���ߵ���90��
int base4[] = {80,80};  //���ߵĸ�90��
int link13[] = {0,0,0,0};	//base1,3�Ķ˵�������
int link23[] = {0,0,0,0};	//base2,3�Ķ˵�������
int link14[] = {0,0,0,0};	//base1,4�Ķ˵�������
int link24[] = {0,0,0,0};	//base2,4�Ķ˵�������

/**
  * @breif ����ָ�������
  */
void ZNZ_Draw_Panel() {
//	int rad = 120;
	GUI_SetPenSize(0);
	GUI_SetColor(0xaeaeae);

	GUI_DrawCircle(120,120,100);
	GUI_DrawCircle(120,120,80);
}

void ZNZ_Draw_Compass() {
	int i;
//	int j=0;
	float a;
	int x,y;
//	int buff;
//	char ac[5];

	for(i=0;i<8;i++){
		a=(360-i*45)*3.1415926/180;
		x = 25*cos(a)+120;
		y = -25*sin(a)+285;
//		if(i%5==0){
			GUI_SetColor(0x12b9ff);
			GUI_SetPenSize(4);
			GUI_DrawPoint(x,y);
//		}
//		else{
//			GUI_SetColor(GUI_WHITE);
//			GUI_SetPenSize(3);
//			GUI_DrawPoint(x,y);
//		}
//		//����������ʾ
//		if(i%5==0){
//			x = 87*cos(a)+120;
//			y = -90*sin(a)+120;
//			buff = (++j)*30;
//			if(buff == 360)
//				buff = 0;
//			sprintf(ac,"%d",buff);
//			//���뷽ʽ����
//			if(buff>90 && buff<300){
//				GUI_SetTextAlign(GUI_TA_HCENTER);	//���ж���
//			}
//			else if(buff>0 && buff<120){
//				GUI_SetTextAlign(GUI_TA_RIGHT);		//�Ҷ���
//			}
//			else{
//				GUI_SetTextAlign(GUI_TA_VCENTER);	//ˮƽ����
//			}
//			GUI_SetColor(GUI_RED);
//			GUI_SetFont(&GUI_Font8_ASCII);
//			GUI_DispStringHCenterAt(ac,x,y);
//		}

	}

//	for(i=0;i<360;i++){
		i = 0;
		GUI_SetPenSize(1);
		
	//base1
		a = (90-i)*3.141592653/180;	//�����ƣ�˳ʱ�뷽��ת��
		x = 20*cos(a)+120;
		y = -20*sin(a)+285;
		//����֮ǰ��base1
//		GUI_SetColor(0x282C30);
//		GUI_DrawLine(120,120,base1[0],base1[1]);
		base1[0] = x;
		base1[1] = y;
		//��ʾ�µõ���base1
//		GUI_SetColor(GUI_RED);
//		GUI_DrawLine(120,120,base1[0],base1[1]);
	
	//base2
//		a = (270-i)*3.141592653/180;
//		x = 80*cos(a)+120;
//		y = -80*sin(a)+120;
//		GUI_SetColor(0x282C30);
//		GUI_DrawLine(120,120,base2[0],base2[1]);
		base2[0] = base1[0];
		base2[1] = base1[1]+16;
//		GUI_SetColor(GUI_RED);
//		GUI_DrawLine(120,120,base2[0],base2[1]);

	//base3
		a = (180-i)*3.141592653/180;
		x = 8*cos(a)+120;
		y = -8*sin(a)+285;
//		GUI_SetColor(0x282C30);
//		GUI_DrawLine(120,120,base3[0],base3[1]);
		base3[0] = x;
		base3[1] = y;
//		GUI_SetColor(GUI_RED);
//		GUI_DrawLine(120,120,base3[0],base3[1]);

	//base4
		a = (360-i)*3.141592653/180;
		x = 8*cos(a)+120;
		y = -8*sin(a)+285;
//		GUI_SetColor(0x282C30);
//		GUI_DrawLine(120,120,base4[0],base4[1]);
		base4[0] = x;
		base4[1] = y;
//		GUI_SetColor(GUI_RED);
//		GUI_DrawLine(120,120,base4[0],base4[1]);

	//link13
		GUI_SetColor(0x282C30);
		GUI_DrawLine(link13[0],link13[1],link13[2],link13[3]);
		link13[0] = base1[0];
		link13[1] = base1[1];
		link13[2] = base3[0];
		link13[3] = base3[1];
		GUI_SetColor(0xf3f3f3);
		GUI_DrawLine(link13[0],link13[1],link13[2],link13[3]);
	
	//link14
		GUI_SetColor(0x282C30);
		GUI_DrawLine(link14[0],link14[1],link14[2],link14[3]);
		link14[0] = base1[0];
		link14[1] = base1[1];
		link14[2] = base4[0];
		link14[3] = base4[1];
		GUI_SetColor(0xf3f3f3);
		GUI_DrawLine(link14[0],link14[1],link14[2],link14[3]);

	//link23
		GUI_SetColor(0x282C30);
		GUI_DrawLine(link23[0],link23[1],link23[2],link23[3]);
		link23[0] = base2[0];
		link23[1] = base2[1];
		link23[2] = base3[0];
		link23[3] = base3[1];
		GUI_SetColor(0xf3f3f3);
		GUI_DrawLine(link23[0],link23[1],link23[2],link23[3]);

	//link24
		GUI_SetColor(0x282C30);
		GUI_DrawLine(link24[0],link24[1],link24[2],link24[3]);
		link24[0] = base2[0];
		link24[1] = base2[1];
		link24[2] = base4[0];
		link24[3] = base4[1];
		GUI_SetColor(0xf3f3f3);
		GUI_DrawLine(link24[0],link24[1],link24[2],link24[3]);

	
//	}


}	
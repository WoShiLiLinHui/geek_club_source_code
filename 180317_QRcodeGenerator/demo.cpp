#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include "QR_Encode.h"

struct rectpoly
{
    int x1;
	int y1;
	int x2;
	int y2;
	int x3;
	int y3;
	int x4;
	int y4;
};

void main()  
{  
    // ������СΪ 600 * 600 �Ļ�ͼ����  
    initgraph(600, 600);
    // ����ԭ�� (0, 0) Ϊ��Ļ���루Y��Ĭ������Ϊ����
    setorigin(0, 0);  // ʹ�ð�ɫ��䱳��
    setbkcolor(0xFFFFFF); 
    cleardevice(); 
    setfillcolor(0x0);           // ���������ɫΪ��ɫ
	rectpoly a1;
	char url1[255]="http://www.csdn.net/";
	EncodeData(url1);
	int i,j;
	for(j=0;j<MAX_MODULESIZE;++j)
	{
		for(i=0;i<MAX_MODULESIZE;++i)
		{
			if(m_byModuleData[i][j]==0x01)
			{
				a1.x1=20*i;a1.y1=20*j;
				a1.x2=20*i+20;a1.y2=20*j;
				a1.x3=20*i+20;a1.y3=20*j+20;
				a1.x4=20*i;a1.y4=20*j+20;
				fillpoly(4, (int *)&a1);
			}
		}
	}
    // ��������˳�
    _getch();  
    closegraph(); 
}  
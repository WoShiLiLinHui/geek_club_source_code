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
    // 创建大小为 600 * 600 的绘图窗口  
    initgraph(600, 600);
    // 设置原点 (0, 0) 为屏幕中央（Y轴默认向下为正）
    setorigin(0, 0);  // 使用白色填充背景
    setbkcolor(0xFFFFFF); 
    cleardevice(); 
    setfillcolor(0x0);           // 设置填充颜色为黑色
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
    // 按任意键退出
    _getch();  
    closegraph(); 
}  
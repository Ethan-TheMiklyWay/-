/*********************************************************
		�������ƣ����ƽ��ʯͼ��
		�� �ܣ����Ƶ����� 
		���뻷����Visual C++ 6.0��EasyX_20190219(beta)
		�� �ߣ��ž���<2017304010413><1967527237@qq.com>
		����޸ģ�2019-2-28
*********************************************************/

#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include <iostream>
#include <cmath>
#include <windows.h>
using namespace std;
int main()
{
	int i,j;
    initgraph(640, 480);   // ������ͼ���ڣ���СΪ 640x480 ����
	int offsetx,offsety;
	

	//���ĵ��⿪ʼ
	
	offsetx=100;  //ͼ���ƫ����
	offsety=100;
	moveto(offsetx-50,offsety);
	setcolor(YELLOW);
	outtext("���ĵ���");
	setcolor(MAGENTA);

	int point1[]={100,0,128,0,48,80,150,80,170,100,0,100,100,0};
	int point2[]={0,100,20,120,220,120,128,28,113,43,170,100,0,100};
	int point3[]={76,80,128,28,220,120,228,100,128,0,48,80,76,80};
	for(i=0;i<7;i++){
		point1[i*2]+=offsetx;
		point2[i*2]+=offsetx;
		point3[i*2]+=offsetx;
		point1[i*2+1]+=offsety;
		point2[i*2+1]+=offsety;
		point3[i*2+1]+=offsety;
	}

	setcolor(RED);
	moveto(offsetx+100,offsety);
	for(i=0;i<7;i++){
		lineto(point1[i*2],point1[i*2+1]);
	}
	setfillcolor(RED);
	floodfill(offsetx+110, offsety+10, RED, 0);

	Sleep(400);
	setcolor(YELLOW);
	moveto(offsetx,offsety+100);
	for(i=0;i<7;i++){
		lineto(point2[i*2],point2[i*2+1]);
	}
	setfillcolor(YELLOW);
	floodfill(offsetx+20, offsety+110, YELLOW, 0);

	Sleep(400);
	setcolor(BLUE);
	moveto(offsetx+76,offsety+80);
	for(i=0;i<7;i++){
		lineto(point3[i*2],point3[i*2+1]);
	}
	setfillcolor(BLUE);
	floodfill(offsetx+70, offsety+79, BLUE, 0);
    _getch();              // �����������
    closegraph();          // �رջ�ͼ����
 
	return 0;
}

/*********************************************************
		�������ƣ����ƽ��ʯͼ��
		�� �ܣ�һ�ʻ��Ƶ�һ��ͼ��
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
	

	//��һ���⿪ʼ
    setcolor(YELLOW);
	offsetx=80;  //ͼ���ƫ����
	offsety=180;

	moveto(offsetx-60,offsety-150);
	outtext("��һ����");
	moveto(offsetx,offsety);
	setcolor(WHITE);
	for(i=offsetx;i<=offsetx+320;i=i+20){
		lineto(i,offsety-120);
		lineto(offsetx+320,offsety);
		lineto(i,offsety+120);
		lineto(offsetx,offsety);
		Sleep(50);
	}

    _getch();              // �����������
    closegraph();          // �رջ�ͼ����
 
	return 0;
}
/*********************************************************
		�������ƣ����ƽ��ʯͼ��
		�� �ܣ�������ʯ
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
	

	//�ڶ����⿪ʼ
	
	offsetx=150;  //ͼ���ƫ����
	offsety=150;
	moveto(offsetx-100,offsety-120);
	setcolor(YELLOW);
	outtext("�ڶ�����");
	setcolor(MAGENTA);
	int n=20;
	double t=3.14159*2/n;
	double r=100;
	double x[50],y[50];
	for(i=0;i<n;i++){ 
		x[i]=r*cos(i*t)+offsetx;
		y[i]=r*sin(i*t)+offsety; 
	}
	for(i=0;i<=n-2;i++)
		for(j=i+1;j<=n-1;j++)
			line(x[i],y[i],x[j],y[j]);	


    _getch();              // �����������
    closegraph();          // �رջ�ͼ����
 
	return 0;
}
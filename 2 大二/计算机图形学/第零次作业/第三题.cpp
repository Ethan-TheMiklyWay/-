/*********************************************************
		�������ƣ����ƽ��ʯͼ��
		���ܣ�һ�ʻ�����ʯ
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
	int n;
	cout<<"please input a n's value, must be an odd and no less that 5 and no more that 49"<<endl;
	n=9;
	while(true){
		cin>>n;
		if(n>=5 && n<=49 && n%2==1) break;
		cout<<"value error, please input n again"<<endl;
	}
    initgraph(640, 480);   // ������ͼ���ڣ���СΪ 640x480 ����
	int offsetx,offsety;
	
	
	offsetx=150;  //ͼ���ƫ����
	offsety=150;
	
	double t=3.14159*2/n;
	double r=100;
	double x[50],y[50];

	moveto(offsetx-100,offsety-120);
	setcolor(GREEN);
	outtext("��������");
	setcolor(MAGENTA);
	
	t=3.14159*2/n;
	moveto(offsetx+r,offsety);
	for(i=0;i<n;i++){ 
		x[i]=r*cos(i*t)+offsetx;
		y[i]=r*sin(i*t)+offsety; 
	}	
	int num=0;
	for(i=0;i<n;i++){
		for(j=1;j<=(n-1)/2;j++){
			lineto(x[num],y[num]);
			num=(num+j)%n;
			Sleep(100);
		}
	}
	lineto(x[0],y[0]);
    _getch();              // �����������
    closegraph();          // �رջ�ͼ����
 
	return 0;
}
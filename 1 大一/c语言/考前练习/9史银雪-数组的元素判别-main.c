#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int a[5],b,c,d,e[5];
	for(b=0;b<5;b++) scanf("%d",&a[b]);
	for(d=0,b=0;b<5;b++)
	{
		int w,x,y,z;
		c=a[b];
		z=c%10;c=(c-z)/10;
		y=c%10;c=(c-y)/10;
		x=c%10;c=(c-x)/10;
		w=c;
		if(z+x==w+y){ e[d]=a[b];d++;}
	}
	for(b=0;b<d;b++) {printf("%d",e[b]);if(b!=d-1) printf(" ");}
	return 0;
}


//����a�д��5����λʮ����������ͳ��ǧλ��ʮλ֮�����λ�͸�λ֮����ȵ����ݸ����������������������ݴ�������b�С�

#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int a,b,c,d,x,t[10];
	scanf("%d",&x);
	for(a=0;a<10;a++) t[a]=0;
	for(a=0,d=0;a<x;a++)
	{b=a*a%391;
	if(b==50) {t[d]=a;d++;}
	}
	for(a=0;a<d;a++) 
	{printf("%d",t[a]);
	if(a!=d-1) printf(" ");
	}
	
	return 0;
}

//x2����391����Ϊ50�����������������С�ڵ��������������ڵ�������x��

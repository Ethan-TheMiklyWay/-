#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	char m[30],n[20];
	int a[10],b[10],c[10];  //a��ÿ�����ʵ���ʼλ�ã�b�ǽ���λ�ã�c�ǳ��� 
	int x,y,z,A,k;
	gets(m);
	a[0]=0;
	for(x=0;x<10;x++) c[x]=0;
	for(x=0,A=0;m[x]!='\0';x++)
	{
		if(m[x]>='a'&&m[x]<='z') c[A]++;
		if(m[x]>='a'&&m[x]<='z' &&m[x+1]==' ') {b[A]=x;A++;}
		if(m[x]>='a'&&m[x]<='z' &&m[x-1]==' ') a[A]=x;
	}
	y=0;z=0;k=c[0];     //k������ʵĳ��ȣ�z������ʵ�λ�� ��x�ǵ������� 
	for(y=0;y<A;y++)
	if(c[y]>k) {k=c[y];z=y;}
	for(y=0;y<k;y++)
	n[y]=m[a[k]+y];
	n[y]='\0';
	
    printf("word=%s",n);
	
	return 0;
}


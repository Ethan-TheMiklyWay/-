#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int a,b,c,d,x,y,n,m;
	int z[10][10];
	printf("����������к��У�");
	scanf("%d %d",&x,&y);
	printf("���������Ԫ��ֵ��"); 
	for(a=0;a<x;a++)
	for(b=0;b<y;b++)
	scanf("%d",&z[a][b]);
	m=z[0][0];c=0;d=0;
	for(a=0;a<x;a++)
	for(b=0;b<y;b++)
	if(z[a][b]>m){m=z[a][b];c=a;d=b;}
	printf("�þ������Ԫ��ֵ��max=%d\n���Ԫ���к��кţ�row=%d��col=%d",z[c][d],c,d);
	return 0;
}
/*
����������к��У����������Ԫ��ֵ���þ������Ԫ��ֵ��max=10
���Ԫ���к��кţ�row=2��col=1
*/

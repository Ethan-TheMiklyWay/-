#include<stdio.h>
int main()
{
	int a,b,c;
	scanf("%d",&a);
	a=(a*3+3)*3;
	b=a%10;
	c=(a-b)/10;
	a=b+c;
	if(a==1) printf("ǰ������Ů��");
	if(a==2) printf("������ߵ���");
	if(a==3) printf("������������");
	if(a==4) printf("������");
	if(a==5) printf("���������");
	if(a==6) printf("��������Ů��");
	if(a==7) printf("��ĸ");
	if(a==8) printf("ͬѧ");
	if(a==9) printf("���������ʦ");
	if(a==10) printf("���");

	return 0;
}

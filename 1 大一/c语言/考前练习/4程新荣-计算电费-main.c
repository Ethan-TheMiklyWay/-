#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	double a,b,c,d;
	scanf("%lf",&a);
	if(a<=240) b=0.53*a;
	else if(a<=400) b=127.2+(a-240)*0.58;
	else b=220+(a-400)*0.83;
	printf("%.2f",b); 
	return 0;
}



/*
��һ��������ÿ�²�����240ǧ��ʱ�ĵ�������۱�׼ά���ּ۲��䣨0.53Ԫ/ǧ��ʱ����

�ڶ���������ÿ��241һ400ǧ��ʱ֮��ĵ�������۱�׼�ȵ�һ��������0.05Ԫ/ǧ��ʱ��

������������ÿ�³���400ǧ��ʱ�ĵ�������۱�׼�ȵ�һ��������0.3Ԫ/ǧ��ʱ��
*/

#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int a,b,c;
	for(a=1;;a++)
	{
		if(a%2==1) 
		if(a%3==2)
		if(a%5==4)
		if(a%6==5)
		if(a%7==0)
		break;
	}
	printf("%d",a);
	return 0;
}
/*
��һ�������ݣ���ÿ����2�ף����ʣ��1�ף���ÿ����3�ף����ʣ��2�ף���ÿ����5�ף����ʣ��4�ף���ÿ��
��6�ף������ʣ��5�ף�ֻ��ÿ����7�ף���������1�ײ�ʣ����д��������������������ж��ٽס�*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	double a,b,c,d;
	scanf("%lf",&a);
	b=fmod(a,1.0);
	if(b!=0) a=a-b+1;
	if(a<=10) a=30;
	else if(a<=50) a=(a-10)*3+30;
	else a=150+(a-50)*1;
	printf("%.0f",a);
	
	return 0;
}

//  30Ԫ           <=10Сʱ
//����=  ÿСʱ3Ԫ       10��50Сʱ

//       ÿСʱ2Ԫ       >=50Сʱ

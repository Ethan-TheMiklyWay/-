#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<conio.h> 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	srand(time(NULL));
	printf("����������ļ�������");
	int numb;
	scanf("%d",&numb);
	
	printf("�����ļ���С��λ(1ΪB��2ΪKB��3ΪMB��4ΪGB)��");
	int type;
	scanf("%d",&type);
	type = type>4 ? 4:type;
	type = type<1 ? 1:type;
	double multi = 1;
	while(type-->1){
		multi *= 1024;
	}
	printf("�����ļ���С(4~1024)��4�ı���(����ȡ��)��");
	int size;
	scanf("%d",&size);
	size = size>1024 ? 1024:size;
	size = size<4 ? 4:size;
	size = size / 4;
	double final = multi * double(size);
	
	system("mkdir \"bullshit package\"");
	while(numb-->0){
		char name[80]={0};
		char string[20]={0};
		strcpy(name,"bullshit package\\");
		itoa(numb,string,10);
		strcat(name,string);
		strcat(name,".bullshit");
		printf("gengrate: %s\n",name);
		
		FILE *fp = fopen(name, "w+");
		for(double i=0 ; i<final ; i++){
			int j = rand();
			fwrite(&j,4,1,fp);
		}
		fclose(fp);
	}
	printf("�������");
	getch();
	
	
	
	
	return 0;
}

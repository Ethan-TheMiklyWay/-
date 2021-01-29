#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>


//�򿪵Ƶ�����������490~505���ļ���
//�ȼ��� echo 490 > /sys/class/gpio/export 
void open_light(){
	int fd = open("/sys/class/gpio/export", O_RDWR);
	char n[16];
	if(fd==-1){
		printf("error open light\n");
		exit(EXIT_FAILURE);
	}
	int i;
	for(i=0;i<16;i++){
		//��490~505д�뵽export������ 
		sprintf(n,"%d",490+i);
		write(fd,n,sizeof(n));
	}
	close(fd);
}


//��490~505��ַ�ĵƵ�out��
//�ȼ��� echo out > /sys/class/gpio/gpio490/direction 
void out_light(){
	char cmd1[50];
	char name[] = "/sys/class/gpio/gpio";
	char n[20];
	int i;
	for(i=0;i<16;i++){
		//������صĵ�������·���ַ��� 
		strcpy(cmd1,name);
		sprintf(n,"%d",490+i);
		strcat(cmd1,n);
		strcat(cmd1,"/direction");
		
		//�򿪵������ļ� 
		int fd = open(cmd1,O_RDWR);
		if(fd==-1){
			printf("error open out\n");
			printf("%s",cmd1); 
			exit(EXIT_FAILURE);
		}	 
		
		//д��out 
		write(fd,"out",sizeof("out"));
		close(fd);
	}
}


//����ƿ��ƺ��� 
void light(char value[17]){
	int i;
	while(1){
		char name[] = "/sys/class/gpio/gpio";
		char cmd2[50];
		char n[20];
		for(i=0;i<16;i++){
			//������صĵ�������·���ַ��� 
			strcpy(cmd2,name);
			sprintf(n,"%d",490+i);
			strcat(cmd2,n);
			strcat(cmd2,"/value");
			
			//�򿪵������ļ� 
			int fd=open(cmd2,O_RDWR);
			if (fd < 1) {
				printf("error open light led\n");
				printf("%s",cmd2); 
				exit(EXIT_FAILURE);
			}
			
			//д������ָ�� 
			if(value[i]=='1'){
				write(fd,"1",sizeof("1"));
			}
			else{
				write(fd,"0",sizeof("0"));
			}
		}
		//˯��2�� 
		usleep(1500000);
		
		//�����Ƶ�˳�� 
		char tmp1=value[0];
		char tmp2=value[1];
		for(i=0;i<14;i++){
			value[i]=value[i+2];
		}
		value[14]=tmp1;
		value[15]=tmp2;
		value[16]='\0';
		
	}
}


//С���ţ�21 = 10101 
int main(void) {
	
	//�򿪵Ƶ�����������490~505���ļ����ȼ��� echo 490 > /sys/class/gpio/export 
	open_light();
	
	//��490~505��ַ�ĵƵ�out���ȼ��� echo out > /sys/class/gpio/gpio490/direction 
	out_light();
	
	//���Ϊ21����Ӧ�Ķ�����λ0b10101����ʼ�������� 
	char value[17]={'1','0','1','0','1','0','0','0','0','0','0','0','0','0','0','0','0'};
	//����ƿ��ƺ��� 
	light(value);
	
}






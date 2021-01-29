#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 


struct quad{ 
	char result[12]; 
	char ag1[12]; 
	char op[12]; 
	char ag2[12]; 
}; 		//��Ԫʽ�Ķ��� 
char prog[80];	//������ 
int p=0;		//������ prog��ָ�� 
char token[8];	//����
int m=0;		//���� token ��ָ�� 
char ch;		//��Ҫ�������ַ� 
int syn=0;		//���ʵ��ֱ��� 
int sum=0;		//�������� 
int n=0;		//������ 
int	kk=0;		//��������ʼ�ı�־ 
int	k=0; 
const char *rwtab[6]={"begin","if","then","while","do","end"}; //�ؼ��� 
void scaner();		//ɨ�躯�� 
char* factor();		//���� 
char* term();		//�� 
char* expression();	//���ʽ 
int yucu();			//��䴮 
int statement();	//��� 
void emit(char*result,char*ag1,char*op,char*ag2); 
char* newtemp();


void emit(char*result,char*ag1,char*op,char*ag2) { 
	//ʵ�� emit ����������
	printf("%s=%s%s%s\n",result,ag1,op,ag2); 
} 

char*newtemp() { 
	char*p=(char*)malloc(12); 
	char m[12]; 
	k++; 
	itoa(k,m,10); 
	strcpy(p+1,m);
	p[0]='t'; 
	return(p); 
}


void scaner() { 
	for(n=0;n<8;n++) { 
		token[n]=0;//��ʼ������ 
	} 
	ch=prog[p++]; 
	while(ch==' ') { 
		ch=prog[p++];//���˿ո� 
	} 
	if ((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')) { 
		m=0; 
		while ((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')||(ch>='0'&&ch<='9')) { 
			token[m++]=ch;//����ǰ�ַ����뵥�� 
			ch=prog[p++];//ȡ��һ�� 
		} 
		token[m++]='\0';//������ 
		p--;//ָ���λ 
		syn=10;// �ٶ��Ǳ��� 
		for(n=0;n<6;n++) { 
			if (strcmp(token,rwtab[n])==0) {
				syn=n+1;//�ؼ��֣�
				break;
			}
		}
	}
	else if(ch>='0'&&ch<='9') { 
		sum=0; 
		while(ch>='0'&&ch<='9') { 
			sum=sum*10+ch-'0';//�������� 
			ch=prog[p++]; 
		}
		p--;//ָ���λ 
		syn=11;//���� �֣�
	} 
	else switch(ch){ 
	case'>': 
		m=0; 
		token[m++]=ch; 
		ch=prog[p++]; 
		if(ch=='=') {
			syn=24;//��">="
			token[m++]=ch;//��"="���뵥��
		} 
		else {
			syn=23;//��">" 
			p--;//ָ���λ
		}
		break;
		
	case'<': 
		m=0; 
		token[m++]=ch; 
		ch=prog[p++]; 
		if(ch=='>') {
			syn=21;//��"<>"
			token[m++]=ch;//��">"���뵥 ��
		} 
		else if(ch=='=') {
			syn=22;//��"<="
			token[m++]=ch;//��"="���뵥 ��	
		} 
		else {
			syn=20;//��"<" 
			p--;//ָ���λ
		}
		break; 
	case':': 
		m=0; 
		token[m++]=ch; 
		ch=prog[p++];
		if(ch=='=') {
			syn=18; 
			token[m++]=ch;
		} 
		else {
			syn=17; 
			p--;
		}
		break;
	case'-': 
		syn=13; 
		token[0]=ch; 
		break;
	case'+': 
		syn=14; 
		token[0]=ch; 
		break; 
	case'*': 
		syn=15; 
		token[0]=ch; 
		break; 
	case'/': 
		syn=16; 
		token[0]=ch; 
		break; 
	case';': 
		syn=26; 
		token[0]=ch; 
		break; 
	case'(': 
		syn=28; 
		token[0]=ch; 
		break; 
	case')': 
		syn=27; 
		token[0]=ch; 
		break; 
	case'#': 
		syn=0; 
		token[0]=ch; 
		break; 
	default:
		syn=-1;
	} 
} 
	
		
int	lrparser() { 
	int schain=0; 
	kk=0; 
	if(syn==1) {//begin
	 	scaner(); 
		schain=yucu(); 
		if(syn==6) {//end
			scaner(); 
			if((syn==0)&&(kk==0)) 
				printf("success!\n");
		} 
		else {
			if(kk!=1) {
				printf("ȱ�� end!\n"); 
				kk=1;
			}	
		}
	}
	else {
		printf("ȱ�� begin!\n"); 
		kk=1;
	} 
	return(schain);
}

int yucu() { //��䴮
	int schain=0; 
	schain=statement(); 
	while(syn==26){ //�� 
		scaner(); 
		schain=statement(); 
	} 
	return(schain); 
}

int statement(){//���
	int schain=0; 
	char*eplace,*tt; 
	eplace=(char*)malloc(12); 
	tt=(char*)malloc(12); 
	switch(syn) { 
	case 10://��ʶ�� 
		strcpy(tt,token); 
		scaner(); 
		if(syn==18) {
			scaner(); 
			strcpy(eplace,expression()); 
			// ����һ������ַ���͵���Ԫʽ���� 
			emit(tt,eplace,"","");
			schain=0;
		} 
		else {
			printf("ȱ�ٸ�ֵ��!\n"); 
			kk=1;
		}
	break;
	}
	return(schain);
}

char*expression(void) { 
	char*tp,*ep2,*eplace,*tt; 
	tp=(char*)malloc(12); 
	ep2=(char*)malloc(12); 
	eplace=(char*)malloc(12); 
	tt=(char*)malloc(12); 
	strcpy(eplace,term()); 
	while(syn==13||syn==14) { 
		if(syn==13) 
			strcpy(tt,"-"); 
		else 
			strcpy(tt,"+"); 
		scaner();
		strcpy(ep2,term()); 
		//���� newtemp()����һ���µ���ʱ������,�����临�Ƶ� tp ָ��ĵ�Ԫ�� 
		strcpy(tp,newtemp());
		// ����һ������ַ���͵���Ԫʽ���� 
		emit(tp,eplace,tt,ep2);
		
		strcpy(eplace,tp); 

		
	} 
	return(eplace);
}	 

char*term(void) { 
	char*tp,*ep2,*eplace,*tt;   //tt��ʾ����һ����ǰ���ŵı��t1 t2 t3 
	tp=(char*)malloc(12); 
	ep2=(char*)malloc(12);  //���ʽ�Ҳ����� 
	eplace=(char*)malloc(12); 
	tt=(char*)malloc(12);   //��ʾ���ӵķ��� 
	strcpy(eplace,factor()); //���ʽ�������� 
	while((syn==15 )||(syn==16)) { 
		if(syn==15) 
			strcpy(tt,"*"); 
		else 
			strcpy(tt,"/"); 
		scaner(); 
		strcpy(ep2,factor()); 
		strcpy(tp,newtemp()); 
		// ����һ������ַ���͵���Ԫʽ���� 
		emit(tp,eplace,tt,ep2);
		strcpy(eplace,tp); 
	} 
	return(eplace); 
}

char*factor(void) { 
	char*fplace; 
	fplace=(char*)malloc(12); 
	strcpy(fplace,""); 
	if(syn==10) {
		strcpy(fplace,token);
		scaner();
	}
	else if(syn==11) { 
		itoa(sum,fplace,10);
		scaner();
	}
	else if(syn==28) { 
		scaner(); 
		fplace=expression(); 
		if(syn==27) 
			scaner();
		else {
			printf("���� \n"); 
			kk=1;
		}
	}
	else{
		printf("���� \n"); 
		kk=1;
	}
	return(fplace);
}



int main() { 
	system("color F0");
	printf("��������Գ���1,2,3��:\n"); 
	int i; 	
	scanf("%i",&i); 
	switch(i) { 
	case 1:
		strcpy(prog,"begin a:=2+3*4;x:=(a+b)/c end#");
		break; 
	case 2:
		strcpy(prog,"begin a:=(21+31)*41;x:=a+bf+c end#");
		break; 
	case 3:
		strcpy(prog,"begin a:=(21+31)*41;x:=a+bf+c #");
		break; 
	} 
	printf("\n����������Ϊ:\n"); 
	p=0; 
	scaner(); 
	lrparser(); 
	system("pause"); 
	return 0;
}
 
		
